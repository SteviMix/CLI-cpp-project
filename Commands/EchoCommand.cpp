//
// Created by Mihajlo Matovic on 13. 12. 2025..
//

#include "EchoCommand.h"

#include <memory>

#include "ConsoleOutputStream.h"
#include "../AbstractClasses/InputStream.h"
#include "../AbstractClasses/OutputStream.h"
#include "../InputStreams/StringInputStream.h"
#include "../InputStreams/ConsoleInputStream.h"
#include "../InputStreams/FileInputStream.h"
#include "../AbstractClasses/CommandError.h"

void EchoCommand::validate() {
    if (this->args.size() > 1) {
        throw CommandError(ErrorType::Syntax, "Too many arguments, echo can have 0 or 1 arguments", getArguments()[1].position);
    }
}

void EchoCommand::execute(
    std::shared_ptr<InputStream> input,
    std::shared_ptr<OutputStream> output,
    std::shared_ptr<OutputStream> errorOutput
    ) {
    std::shared_ptr<InputStream> src;

    // Creates the corresponding input stream.
    if (this->args.empty()) {
        src = input;
    }
    else {
        if (args[0].inQuotes) {
            src = std::make_shared<StringInputStream>(args[0].string);
        }
        else {
            auto fileSrc = std::make_shared<FileInputStream>(args[0].string, args[0].position);
            src = fileSrc;
        }
    }

    // Writes the characters to the output stream.
    char c;
    std::ostringstream oss;
    while (src->readChar(c)) {
        oss<< c;
    }
    output->writeString(oss.str());
}

bool EchoCommand::inputViaArgs() const {
    return !args.empty();
}

std::string EchoCommand::getName() const {
    return "EchoCommand";
}
