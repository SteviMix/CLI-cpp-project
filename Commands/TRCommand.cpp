//
// Created by Mihajlo Matovic on 2. 3. 2026..
//

#include "TRCommand.h"
#include "../AbstractClasses/CommandError.h"
#include "../InputStreams/StringInputStream.h"
#include "../InputStreams/FileInputStream.h"
#include "../AbstractClasses/OutputStream.h"

void TRCommand::validate() {
    // Ensure at least one argument exists
    if (args.empty()) {
        throw CommandError(ErrorType::Syntax, "Missing arguments for tr", getPosition() + 2);
    }

    int dashIndex = -1;

    // Detect the '-' flag position
    if (args[0].string == "-") {
        dashIndex = 0;
    } else if (args.size() > 1 && args[1].string == "-") {
        dashIndex = 1;
    } else {
        throw CommandError(ErrorType::Syntax, "Missing '-' before 'what' string", args[0].position);
    }

    // Extract the source string ('what') to be replaced/deleted
    int whatIndex = dashIndex + 1;
    if (whatIndex >= args.size()) {
        throw CommandError(ErrorType::Syntax, "Missing 'what' string after '-'", args[dashIndex].position + 1);
    }

    if (!args[whatIndex].inQuotes) {
        throw CommandError(ErrorType::Syntax, "'what' argument must be in quotes", args[whatIndex].position);
    }
    this->what = args[whatIndex].string;

    // Determine if we are in 'delete' mode or 'replace' mode based on 'with' argument
    int withIndex = whatIndex + 1;
    if (withIndex < args.size()) {
        if (!args[withIndex].inQuotes) {
            throw CommandError(ErrorType::Syntax, "'with' argument must be in quotes", args[withIndex].position);
        }
        this->with = args[withIndex].string;
        this->deleteMode = false;
    } else {
        this->deleteMode = true;
    }

    // Final check for unexpected arguments
    if (withIndex + 1 < args.size()) {
        throw CommandError(ErrorType::Syntax, "Too many arguments for tr", args[withIndex + 1].position);
    }

    // Clean up processed arguments to isolate the input source
    args.erase(args.begin() + dashIndex, args.end());
}

void TRCommand::execute(
    std::shared_ptr<InputStream> input,
    std::shared_ptr<OutputStream> output,
    std::shared_ptr<OutputStream> errorOutput
) {
    std::shared_ptr<InputStream> src;

    // Creating the corresponding input stream.
    if (!this->args.empty()) {
        if (this->args[0].inQuotes) {
            src = std::make_shared<StringInputStream>(args[0].string);
        } else {
            auto fileSrc = std::make_shared<FileInputStream>(args[0].string, args[0].position);
            src = fileSrc;
        }
    } else {
        src = input;
    }

    // Read the entire source content into a string
    std::string content;
    char c;
    while (src->readChar(c)) {
        content += c;
    }

    // Perform translation: either delete or replace substrings
    size_t pos = 0;
    while ((pos = content.find(what, pos)) != std::string::npos) {
        if (deleteMode) {
            content.erase(pos, what.length());
        } else {
            content.replace(pos, what.length(), with);
            pos += with.length();
        }
    }

    output->writeString(content);
}

bool TRCommand::acceptsInput() const {
    return args.empty();
}

std::string TRCommand::getName() const {
    return "TRCommand";
}
