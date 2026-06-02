//
// Created by Mihajlo Matovic on 10. 1. 2026..
//

#include "TimeCommand.h"
#include <ctime>
#include "../AbstractClasses/CommandError.h"
#include "../AbstractClasses/OutputStream.h"

void TimeCommand::validate() {
    if (!args.empty()) {
        throw CommandError(ErrorType::Syntax, "Time command must have 0 arguments", getArguments()[0].position);
    }
}

void TimeCommand::execute(
    std::shared_ptr<InputStream> input,
    std::shared_ptr<OutputStream> output,
    std::shared_ptr<OutputStream> errorOutput
    ) {

    // Gets the system time.
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&currentTime);

    // Writes the time to the output stream.
    char buffer[10];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", timeInfo);
    output->writeString(std::string(buffer));
}

bool TimeCommand::acceptsInput() const {
    return false;
}

std::string TimeCommand::getName() const {
    return "TimeCommand";
}