//
// Created by Mihajlo Matovic on 10. 1. 2026..
//

#ifndef DATECOMMAND_H
#define DATECOMMAND_H

#include "../AbstractClasses/Command.h"


// Writes the system date to its output stream.
class DateCommand : public Command{
public:
    DateCommand() = default;

    void execute(
        std::shared_ptr<InputStream> input,
        std::shared_ptr<OutputStream> output,
        std::shared_ptr<OutputStream> errorOutput) override;

    bool acceptsInput() const override;
    std::string getName() const override;
    void validate() override;
};



#endif //DATECOMMAND_H
