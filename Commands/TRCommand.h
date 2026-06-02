//
// Created by Mihajlo Matovic on 2. 3. 2026..
//

#ifndef TRCOMMAND_H
#define TRCOMMAND_H

#include "../AbstractClasses/Command.h"

// Translates or deletes characters from the input stream.
class TRCommand : public Command {
public:
    TRCommand() = default;


    void execute(std::shared_ptr<InputStream> input,
                 std::shared_ptr<OutputStream> output,
                 std::shared_ptr<OutputStream> errorOutput) override;

    bool acceptsInput() const override;
    std::string getName() const override;
    void validate() override;

private:
    std::string what;
    std::string with;
    bool deleteMode = false;
};



#endif //TRCOMMAND_H
