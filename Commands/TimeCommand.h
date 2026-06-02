//
// Created by Mihajlo Matovic on 10. 1. 2026..
//

#ifndef TIMECOMMAND_H
#define TIMECOMMAND_H

#include "../AbstractClasses/Command.h"

// Writes the system time to its output stream.
class TimeCommand : public Command {
public:
    TimeCommand() = default;

    void execute(
        std::shared_ptr<InputStream> input,
        std::shared_ptr<OutputStream> output,
        std::shared_ptr<OutputStream> errorOutput) override;

    bool acceptsInput() const override;
    std::string getName() const override;
    void validate() override;
};

#endif //TIMECOMMAND_H