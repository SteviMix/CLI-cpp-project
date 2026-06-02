//
// Created by Mihajlo Matovic on 7. 1. 2026..
//

#include <string>
#include <iostream>
#include <cstdio>
#include <vector>

#include "Interpreter.h"
#include "Parser.h"
#include "Reader.h"
#include "../AbstractClasses/CommandError.h"
#include "../InputStreams/FileInputStream.h"
#include "../OutputStreams/FileOutputStream.h"
#include "../InputStreams/StringInputStream.h"
#include "../OutputStreams/StringOutputStream.h"

void Interpreter::run() {
    constexpr size_t MAX_LINE_LENGTH = 512;
    Reader reader(input.get());
    while (true) {
        output->writeString(prompt + " ");

        std::string line;

        if (!reader.readLine(line)) {
            break;
        }

        if (line.empty()) continue;

        executeLine(line);
    }
}
void Interpreter::executeLine(const std::string& line) {
    Parser parser;

    try {
        std::vector<std::unique_ptr<Command>> commands = parser.parse(line);

        if (commands.empty()) {
            return;
        }

        // Pass 1: Semantic validation (Fail Fast)
        validatePipeline(commands);

        // Pass 2: Stream setup and execution
        executePipeline(commands);

        output->writeString("\n");
    }
    catch (const CommandError& e) {
        printErrorMarker(e, line);
    }
    catch (...) {
        errorOutput->writeString("Unknown error\n");
    }

    if (std::cin.eof()) {
        std::cin.clear();
        clearerr(stdin);
    }
}


void Interpreter::validatePipeline(const std::vector<std::unique_ptr<Command>>& commands) {
    for (size_t i = 0; i < commands.size(); ++i) {
        const auto& command = commands[i];
        bool isFirst = (i == 0);
        bool isLast = (i == commands.size() - 1);

        command->validate();

        validateRedirectionSemantics(command);

        validatePipeSemantics(command, isFirst, isLast);
    }
}


void Interpreter::validateRedirectionSemantics(const std::unique_ptr<Command>& command) {
    if (!command->getRedirectionInputFile().empty() && !command->acceptsInput()) {
        throw CommandError(ErrorType::Semantic,
            "Invalid redirection: Command '" + command->getName() + "' does not accept input.",
            command->getInputRedirPosition());
    }

    if (!command->getRedirectionOutputFile().empty() && !command->hasOutput()) {
        throw CommandError(ErrorType::Semantic,
            "Invalid redirection: Command '" + command->getName() + "' does not produce output.",
            command->getOutputRedirPosition());
    }
}


void Interpreter::validatePipeSemantics(const std::unique_ptr<Command>& command, bool isFirst, bool isLast) {
    if (!isFirst) {
        if (!command->acceptsInput()) {
            throw CommandError(ErrorType::Semantic,
                "Invalid pipe: Command '" + command->getName() + "' does not accept input.", command->getPosition());
        }
        if (!command->getRedirectionInputFile().empty()) {
            throw CommandError(ErrorType::Semantic,
                "Ambiguous input: Input redirection (<) cannot be used inside a pipe.", command->getInputRedirPosition());
        }
        if (command->inputViaArgs()) {
            throw CommandError(ErrorType::Semantic,
                "Ambiguous input: Command creates input from arguments, but is connected to pipe.", command->getArguments()[0].position);
        }
    }

    if (!isLast) {
        if (!command->hasOutput()) {
            throw CommandError(ErrorType::Semantic,
                "Invalid pipe: Command '" + command->getName() + "' does not produce output.", command->getPosition());
        }
        if (!command->getRedirectionOutputFile().empty()) {
            throw CommandError(ErrorType::Semantic,
                "Ambiguous output: Output redirection (>) cannot be used inside a pipe.", command->getOutputRedirPosition());
        }
    }
}


void Interpreter::executePipeline(const std::vector<std::unique_ptr<Command>>& commands) {
    std::shared_ptr<InputStream> nextInput = nullptr;

    for (size_t i = 0; i < commands.size(); ++i) {
        const auto& command = commands[i];
        bool isLast = (i == commands.size() - 1);

        std::shared_ptr<StringOutputStream> pipeBuffer = nullptr;


        auto currentInput = setupInputStream(command, nextInput);
        auto currentOutput = setupOutputStream(command, isLast, pipeBuffer);


        command->execute(currentInput, currentOutput, errorOutput);


        if (pipeBuffer != nullptr) {
            std::string pipeData = pipeBuffer->getString();
            nextInput = std::make_shared<StringInputStream>(pipeData);
        }
    }
}


std::shared_ptr<InputStream> Interpreter::setupInputStream(const std::unique_ptr<Command>& command, std::shared_ptr<InputStream>& nextInput) {
    // Read from the previous pipe
    if (nextInput != nullptr) {
        auto inputToUse = nextInput;
        nextInput = nullptr; // Consume the pipe
        return inputToUse;
    }

    // Read from a redirected file (<)
    if (!command->getRedirectionInputFile().empty()) {
        auto fileInput = std::make_shared<FileInputStream>(command->getRedirectionInputFile(), command->getInputRedirPosition());
        if (!fileInput->isOpen()) {
            throw CommandError(ErrorType::OS, "Input file could not be opened: " + command->getRedirectionInputFile(), command->getInputRedirPosition());
        }
        return fileInput;
    }

    // Read from the default interpreter input
    return this->input;
}

std::shared_ptr<OutputStream> Interpreter::setupOutputStream(const std::unique_ptr<Command>& command, bool isLast, std::shared_ptr<StringOutputStream>& pipeBuffer) {
    // Write to a redirected file (>)
    if (!command->getRedirectionOutputFile().empty()) {
        auto fileOutput = std::make_shared<FileOutputStream>(
            command->getRedirectionOutputFile(),
            command->isAppendMode(),
            command->getOutputRedirPosition()
        );
        if (!fileOutput->isOpen()) {
            throw CommandError(ErrorType::OS, "Output file could not be opened: " + command->getRedirectionOutputFile(), command->getOutputRedirPosition());
        }
        return fileOutput;
    }

    // Write to a pipe buffer for the next command (|)
    if (!isLast) {
        pipeBuffer = std::make_shared<StringOutputStream>();
        return pipeBuffer;
    }

    // Write to the default interpreter output
    return this->output;
}

void Interpreter::printErrorMarker(const CommandError& e, const std::string& line) {
    errorOutput->writeString(std::string(e.what()) + "\n");
    int pos = e.getPosition();
    if (pos >= 0) {
        errorOutput->writeString(line + "\n");
        std::string pointerStr;
        for (int i = 0; i < pos; ++i) {
            if (line[i] == '\t') {
                pointerStr += '\t';
            } else {
                pointerStr += ' ';
            }
        }
        pointerStr += "^";
        errorOutput->writeString(pointerStr + "\n");
    }
}