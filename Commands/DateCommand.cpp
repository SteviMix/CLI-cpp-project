//
// Created by Mihajlo Matovic on 10. 1. 2026..
//

#include <ctime>

#include "DateCommand.h"
#include "../AbstractClasses/CommandError.h"
#include "../AbstractClasses/OutputStream.h"

void DateCommand::validate() {

    // Checks if any arguments are given, the command does not accept any.
    if (!args.empty()) {
        throw CommandError(ErrorType::Syntax, "Date command must have 0 arguments", getArguments()[0].position);
    }
}

void DateCommand::execute(
    std::shared_ptr<InputStream> input,
    std::shared_ptr<OutputStream> output,
    std::shared_ptr<OutputStream> errorOutput
    ) {

    // Gets the system date.
    std::time_t currentTime = std::time(nullptr);
    std::tm* date = std::localtime(&currentTime);

    // Writes the date to the output stream.
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", date);
    output->writeString(std::string(buffer));
}

bool DateCommand::acceptsInput() const {
    return false;
}

std::string DateCommand::getName() const {
    return "DateCommand";
}