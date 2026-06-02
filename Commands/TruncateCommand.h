//
// Created by Mihajlo Matovic on 2. 3. 2026..
//

#ifndef TRUNCATECOMMAND_H
#define TRUNCATECOMMAND_H

#include "../AbstractClasses/Command.h"

// Clears the content of a specified file in the working directory.
class TruncateCommand : public Command {
public:
    TruncateCommand() = default;



    void execute(std::shared_ptr<InputStream> input,
                 std::shared_ptr<OutputStream> output,
                 std::shared_ptr<OutputStream> errorOutput) override;

    bool acceptsInput() const override;
    std::string getName() const override;
    void validate() override;
    bool hasOutput() const override;
};



#endif //TRUNCATECOMMAND_H
