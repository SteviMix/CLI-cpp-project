//
// Created by Mihajlo Matovic on 2. 3. 2026..
//

#include "TruncateCommand.h"
#include "../OutputStreams/FileOutputStream.h"
#include "../AbstractClasses/CommandError.h"
#include <filesystem>

#include "FileInputStream.h"

// Checks if only one argument is given.
void TruncateCommand::validate() {

    if (args.empty()) {
        throw CommandError(ErrorType::Syntax, "Missing filename for truncate", getPosition() + 9);
    }

    if (args.size() > 1) {
        throw CommandError(ErrorType::Syntax, "Truncate command accepts only one argument", args[1].position);
    }
}

void TruncateCommand::execute(std::shared_ptr<InputStream> input,
                             std::shared_ptr<OutputStream> output,
                             std::shared_ptr<OutputStream> errorOutput) {

    std::string filename = args[0].string;

    auto checkFile = std::make_shared<FileInputStream>(filename, args[0].position);

    // The file is opened in truncation mode and immediately closed.
    FileOutputStream fileStream(filename, false,args[0].position);
}


bool TruncateCommand::acceptsInput() const {
    return false;
}

std::string TruncateCommand::getName() const {
    return "TruncateCommand";
}

bool TruncateCommand::hasOutput() const {
    return false;
}