//
// Created by Mihajlo Matovic on 10. 1. 2026..
//

#ifndef TOUCHCOMMAND_H
#define TOUCHCOMMAND_H

#include "../AbstractClasses/Command.h"

// Creates a new empty file.
class TouchCommand : public Command {
public:
    TouchCommand() = default;

    void execute(
        std::shared_ptr<InputStream> input,
        std::shared_ptr<OutputStream> output,
        std::shared_ptr<OutputStream> errorOutput) override;

    bool acceptsInput() const override;
    std::string getName() const override;
    bool hasOutput() const override;
    void validate() override;
};

#endif //TOUCHCOMMAND_H