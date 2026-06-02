//
// Created by Mihajlo Matovic on 2. 3. 2026..
//

#include "HeadCommand.h"

#include "HeadCommand.h"
#include "../AbstractClasses/CommandError.h"
#include "../InputStreams/StringInputStream.h"
#include "../InputStreams/FileInputStream.h"
#include "../AbstractClasses/OutputStream.h"

void HeadCommand::validate() {
    if (args.empty()) {
        throw CommandError(ErrorType::Syntax, "Missing arguments", getPosition() + 4);
    }

    std::string opt = args[0].string;
    if (opt.length() < 3 || opt.substr(0, 2) != "-n") {
        throw CommandError(ErrorType::Syntax, "Invalid option format. Expected -nCOUNT", args[0].position);
    }

    std::string countPart = opt.substr(2);
    if (countPart.length() > 5) {
        throw CommandError(ErrorType::Syntax, "Line count must have at most 5 digits", args[0].position + 2);
    }

    for (char c : countPart) {
        if (!isdigit(c)) {
            throw CommandError(ErrorType::Syntax, "Invalid line count value", args[0].position + 2);
        }
    }

    this->lineCount = std::stoi(countPart);

    args.erase(args.begin());

    if (args.size() > 1) {
        throw CommandError(ErrorType::Syntax, "Too many arguments", args[1].position);
    }
}

void HeadCommand::execute(
    std::shared_ptr<InputStream> input,
    std::shared_ptr<OutputStream> output,
    std::shared_ptr<OutputStream> errorOutput
) {
    std::shared_ptr<InputStream> src;
    // Creates the corresponding input stream.
    if (this->args.size() == 1) {
        if (this->args[0].inQuotes) {
            src = std::make_shared<StringInputStream>(args[0].string);
        }
        else {
            auto fileSrc = std::make_shared<FileInputStream>(args[0].string, args[0].position);
            src = fileSrc;
        }
    } else {
        src = input;
    }

    std::string line;
    std::vector<std::string> savedLines;

    // Buffers the first n lines and writes them to the output stream.
    while (src->readLine(line)) {
        if (savedLines.size() < this->lineCount) {
            savedLines.push_back(line);
        }
    }

    for (const auto& sacuvana : savedLines) {
        output->writeString(sacuvana + "\n");
    }
}



bool HeadCommand::acceptsInput() const {
    return true;
}

std::string HeadCommand::getName() const {
    return "HeadCommand";
}

