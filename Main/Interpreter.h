//
// Created by Mihajlo Matovic on 7. 1. 2026..
//

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <string>
#include "../AbstractClasses/InputStream.h"
#include "../AbstractClasses/OutputStream.h"
#include "../AbstractClasses/Command.h"
#include "../OutputStreams/StringOutputStream.h"
// Main class for running the interpreter.
class Interpreter {
public:
    ~Interpreter() = default;

    static Interpreter& getInstance(std::shared_ptr<InputStream> in = nullptr,
                                    std::shared_ptr<OutputStream> out = nullptr,
                                    std::shared_ptr<OutputStream> err = nullptr) {
        static Interpreter instance(std::move(in), std::move(out), std::move(err));
        return instance;
    }


    Interpreter(const Interpreter&) = delete;
    void operator=(const Interpreter&) = delete;
    // Class method that starts the execution of the interpreter.
    void run();
    void executeLine(const std::string& line);
    void setPrompt(const std::string& newPrompt) {prompt = newPrompt;}


    std::shared_ptr<OutputStream> getOutput() const { return output; }
    void setOutput(std::shared_ptr<OutputStream> newOutput) { output = newOutput; }

private:
    Interpreter(std::shared_ptr<InputStream> in,
                std::shared_ptr<OutputStream> out,
                std::shared_ptr<OutputStream> err)
            :   input(std::move(in))
            ,   output(std::move(out))
            ,   errorOutput(std::move(err)) {}

    std::string prompt = "$";

    std::shared_ptr<InputStream> input;
    std::shared_ptr<OutputStream> output;
    std::shared_ptr<OutputStream> errorOutput;

    // Validates the entire pipeline semantics before any execution begins.
    void validatePipeline(const std::vector<std::unique_ptr<Command>>& commands);

    // Validates the semantics of input and output redirections for a single command.
    void validateRedirectionSemantics(const std::unique_ptr<Command>& command);

    // Validates the semantics of the command's position within a pipeline.
    void validatePipeSemantics(const std::unique_ptr<Command>& command, bool isFirst, bool isLast);

    // Configures input and output streams and executes each command in the pipeline.
    void executePipeline(const std::vector<std::unique_ptr<Command>>& commands);

    // Prints the error message along with a pointer indicating the error position.
    void printErrorMarker(const CommandError& e, const std::string& line);

    // Sets up the appropriate input stream for a command based on pipes and redirections.
    std::shared_ptr<InputStream> setupInputStream(const std::unique_ptr<Command>& command, std::shared_ptr<InputStream>& nextInput);

    // Sets up the appropriate output stream for a command based on pipes and redirections.
    std::shared_ptr<OutputStream> setupOutputStream(const std::unique_ptr<Command>& command, bool isLast, std::shared_ptr<StringOutputStream>& pipeBuffer);
};



#endif //INTERPRETER_H
