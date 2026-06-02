//
// Created by Mihajlo Matovic on 1. 3. 2026..
//

#ifndef PROMPTCOMMAND_H
#define PROMPTCOMMAND_H

#include "../AbstractClasses/Command.h"

// Sets a new prompt for the Interpreter.
class PromptCommand : public Command {
public:
    PromptCommand() = default;

    void execute(
        std::shared_ptr<InputStream> input,
        std::shared_ptr<OutputStream> output,
        std::shared_ptr<OutputStream> errorOutput) override;

    bool acceptsInput() const override;
    std::string getName() const override;
    void validate() override;
    bool hasOutput() const override;
};



#endif //PROMPTCOMMAND_H
