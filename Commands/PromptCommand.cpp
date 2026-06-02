//
// Created by Mihajlo Matovic on 1. 3. 2026..
//

#include "PromptCommand.h"

#include "Interpreter.h"
#include "../AbstractClasses/CommandError.h"

void PromptCommand::validate() {
    // Checks the arguments.
    if (args.empty()) {
        throw CommandError(ErrorType::Execution, "Missing prompt", getPosition()+6);
    }
    if (args.size() != 1) {
        throw CommandError(ErrorType::Execution, "Prompt command must have 1 argument", args[1].position);
    }
    if (!args[0].inQuotes) {
        throw CommandError(ErrorType::Execution, "Prompt command must have the new prompt in quotes", args[0].position);
    }
}

void PromptCommand::execute(
    std::shared_ptr<InputStream> input,
    std::shared_ptr<OutputStream> output,
    std::shared_ptr<OutputStream> errorOutput
    ) {
    Interpreter::getInstance().setPrompt(args[0].string);
}
bool PromptCommand::acceptsInput() const {
    return false;
}

std::string PromptCommand::getName() const {
    return "PromptCommand";
}

bool PromptCommand::hasOutput() const {
    return false;
}





