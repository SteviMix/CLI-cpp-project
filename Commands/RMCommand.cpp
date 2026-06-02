//
// Created by Mihajlo Matovic on 2. 3. 2026..
//

#include "RMCommand.h"
#include <cstdio>
#include "../AbstractClasses/CommandError.h"

void RMCommand::validate() {
    if (args.empty()) {
        throw CommandError(ErrorType::Syntax, "Missing filename", getPosition() + 3);
    }

    if (args.size() > 1) {
        throw CommandError(ErrorType::Syntax, "rm command must have exactly 1 argument", args[1].position);
    }
}

void RMCommand::execute(
    std::shared_ptr<InputStream> input,
    std::shared_ptr<OutputStream> output,
    std::shared_ptr<OutputStream> errorOutput
) {
    std::string filename = args[0].string;
    if (std::remove(filename.c_str()) != 0) {
        throw CommandError(ErrorType::OS, "Could not remove file ", args[0].position);
    }
}

bool RMCommand::acceptsInput() const {
    return false;
}

std::string RMCommand::getName() const {
    return "rm";
}

bool RMCommand::hasOutput() const {
    return false;
}