//
// Created by Mihajlo Matovic on 10. 1. 2026..
//

#include "TouchCommand.h"

#include <fstream>
#include "../AbstractClasses/CommandError.h"
#include "../OutputStreams/FileOutputStream.h"
void TouchCommand::validate() {
    // Checks the arguments.
    if (args.empty()) {
        throw CommandError(ErrorType::Execution, "Missing filename", getPosition()+5);
    }
    if (args.size() != 1) {
        throw CommandError(ErrorType::Execution, "Touch command must have 1 argument", getArguments()[1].position);
    }
}

void TouchCommand::execute(
    std::shared_ptr<InputStream> input,
    std::shared_ptr<OutputStream> output,
    std::shared_ptr<OutputStream> errorOutput
    ) {

    // Opens the file with the given filename.
    std::string filename = this->args[0].string;

    std::ifstream file_check(filename);
    if (file_check.is_open()) {
        file_check.close();
        throw CommandError(ErrorType::Execution, "File already exists", args[0].position);
    }

    FileOutputStream file(filename, false, args[0].position);
}

bool TouchCommand::acceptsInput() const {
    return false;
}

std::string TouchCommand::getName() const {
    return "TouchCommand";
}

bool TouchCommand::hasOutput() const {
    return false;
}