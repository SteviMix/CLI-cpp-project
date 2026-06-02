//
// Created by Mihajlo Matovic on 10. 1. 2026..
//

#include "WCCommand.h"

#include <iostream>
#include <string>
#include <cctype>

#include "../AbstractClasses/CommandError.h"
#include "../AbstractClasses/InputStream.h"
#include "../AbstractClasses/OutputStream.h"
#include "../InputStreams/StringInputStream.h"
#include "../InputStreams/FileInputStream.h"

void WCCommand::validate() {
    // Checks the number of arguments.
    if (args.empty()) {
        throw CommandError(ErrorType::Syntax, "Missing arguments", getPosition()+3);
    }
    if (args.size() > 2) {
        throw CommandError(ErrorType::Syntax, "Too many arguments", args[2].position);
    }
    // Checks if the flag is valid immediately.
    if (args[0].string != "-c" && args[0].string != "-w") {
        throw CommandError(ErrorType::Syntax, "Unknown argument: " + args[0].string, args[0].position);
    }
    selectedOption = args[0].string;
    args.erase(args.begin());
}

void WCCommand::execute(
    std::shared_ptr<InputStream> input,
    std::shared_ptr<OutputStream> output,
    std::shared_ptr<OutputStream> errorOutput
    ) {

    std::shared_ptr<InputStream> src;

    // Determine input source.
    if (this->args.size() == 1) {
        // Read from file or string literal.
        if (this->args[0].inQuotes) {
            src = std::make_shared<StringInputStream>(this->args[0].string);
        }
        else {
            auto fileSrc = std::make_shared<FileInputStream>(args[0].string, args[0].position);
            src = fileSrc;
        }
    } else {
        src = input;
    }

    // Execute logic based on the flag.
    std::size_t cnt = 0;
    if (selectedOption == "-c") {
        cnt = countChars(src);
    }
    else if (selectedOption == "-w") {
        cnt = countWords(src);
    }

    output->writeString(std::to_string(cnt));
}

std::size_t WCCommand::countWords(std::shared_ptr<InputStream> input) {
    char c;
    std::size_t cnt = 0;
    bool isWord = false;

    while (input->readChar(c)) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            if (isWord) {
                cnt++;
                isWord = false;
            }
        }
        else {
            isWord = true;
        }
    }
    if (isWord) {
        cnt++;
    }
    return cnt;
}

std::size_t WCCommand::countChars(std::shared_ptr<InputStream> input) {
    char c;
    std::size_t cnt = 0;
    while (input->readChar(c)) {
        cnt++;
    }
    return cnt;
}

bool WCCommand::inputViaArgs() const {
    return args.size() == 2;
}

std::string WCCommand::getName() const {
    return "WCCommand";
}