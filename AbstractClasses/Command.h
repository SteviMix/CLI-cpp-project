//
// Created by Mihajlo Matovic on 12. 12. 2025..
//

#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include <memory>
#include "../Types.h"

// Forward declarations.
class InputStream;
class OutputStream;
class CommandError;
// Abstract base class for all commands.
// Every command reads from InputStream, writes in OutputStream and handles errors.
class Command {
public:

    Command() = default;

    virtual ~Command() = default;

    // Accepts input, output and errorOutput streams and executes the function. Throws CommandError on failure.
    virtual void execute(
        std::shared_ptr<InputStream> input,
        std::shared_ptr<OutputStream> output,
        std::shared_ptr<OutputStream> errorOutput
        ) = 0;
    // Validating the arguments for command execution. Throws CommandError if arguments are not valid.
    virtual void validate() = 0;

    // Command can have an input stream? Default true.
    virtual bool acceptsInput() const {
        return true;
    }
    // Command generated the input stream using the arguments? Default false.
    virtual bool inputViaArgs() const {
        return false;
    }

    // Command can have an output stream? Default true.
    virtual bool hasOutput() const {
        return true;
    }

    // Setters and getters.
    void setArguments(const std::vector<Token>& args) {
        this->args = args;
    }

    void setOutputRedirection(const Token& t, bool append) {
        this->redirectionOutputToken = t;
        this->appendMode = append;
    }

    std::string getRedirectionOutputFile() const {
        return redirectionOutputToken.string;
    }

    bool isAppendMode() const {
        return appendMode;
    }

    void setInputRedirection(const Token& t) {
        this->redirectionInputToken = t;
    }

    std::string getRedirectionInputFile() const {
        return redirectionInputToken.string;
    }

    const std::vector<Token>& getArguments() const {
        return args;
    }

    virtual std::string getName() const = 0;

    void setPosition(int pos) {
        commandPosition = pos;
    }

    int getPosition() const {
        return commandPosition;
    }
    int getOutputRedirPosition() const { return redirectionOutputToken.position; }
    int getInputRedirPosition() const { return redirectionInputToken.position; }
protected:

    // Command arguments, used for execution.
    std::vector<Token> args;

private:
    // Input and output redirections.
    Token redirectionOutputToken = {"", false, -1};
    Token redirectionInputToken = {"", false, -1};

    // If appendMode is false then w on output redirection, else tr.
    bool appendMode = false;

    // Position of a command in starting line.
    int commandPosition = -1;
};




#endif //COMMAND_H
