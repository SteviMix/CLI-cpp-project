//
// Created by Mihajlo Matovic on 2. 3. 2026..
//

#ifndef BATCHCOMMAND_H
#define BATCHCOMMAND_H

#include "../AbstractClasses/Command.h"


// Reads and executes a sequence of commands from a specified text file.
// Acts as a script runner within the interpreter, handling its own output redirection.
class BatchCommand : public Command {
public:
    BatchCommand() = default;

    void execute(std::shared_ptr<InputStream> input,
                 std::shared_ptr<OutputStream> output,
                 std::shared_ptr<OutputStream> errorOutput) override;

    bool acceptsInput() const override;
    std::string getName() const override;
    void validate() override;
};



#endif //BATCHCOMMAND_H
