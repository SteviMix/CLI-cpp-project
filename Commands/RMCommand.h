//
// Created by Mihajlo Matovic on 2. 3. 2026..
//

#ifndef RMCOMMAND_H
#define RMCOMMAND_H

#include "../AbstractClasses/Command.h"

// Deletes a file from the working directory.
class RMCommand : public Command {
public:
    RMCommand() = default;

    void execute(std::shared_ptr<InputStream> input,
                 std::shared_ptr<OutputStream> output,
                 std::shared_ptr<OutputStream> errorOutput) override;

    bool acceptsInput() const override;
    std::string getName() const override;
    bool hasOutput() const override;
    void validate() override;
};



#endif //RMCOMMAND_H
