//
// Created by Mihajlo Matovic on 13. 12. 2025..
//

#ifndef ECHOCOMMAND_H
#define ECHOCOMMAND_H

#include "../Types.h"
#include "../AbstractClasses/Command.h"

// Writes characters from its input stream to its output stream.
class EchoCommand: public Command {
public:
    EchoCommand() = default;

    void execute(
        std::shared_ptr<InputStream> input,
        std::shared_ptr<OutputStream> output,
        std::shared_ptr<OutputStream> errorOutput) override;
    bool inputViaArgs() const override;
    std::string getName() const override;
    void validate() override;
};

#endif //ECHOCOMMAND_H