//
// Created by Mihajlo Matovic on 2. 3. 2026..
//

#ifndef HEADCOMMAND_H
#define HEADCOMMAND_H

#include "../AbstractClasses/Command.h"

// Skips first n rows from the input stream.
class HeadCommand : public Command {
public:
    HeadCommand() = default;
    void execute(std::shared_ptr<InputStream> input,
                 std::shared_ptr<OutputStream> output,
                 std::shared_ptr<OutputStream> errorOutput) override;

    bool acceptsInput() const override;
    std::string getName() const override;
    void validate() override;
private:
    int lineCount;
};

#endif //HEADCOMMAND_H
