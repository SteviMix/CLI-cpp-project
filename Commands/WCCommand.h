//
// Created by Mihajlo Matovic on 10. 1. 2026..
//

#ifndef WCCOMMAND_H
#define WCCOMMAND_H

#include "../AbstractClasses/Command.h"

// Class for the WC command.
// Writes the number of words or characters from the input stream depending on the option.
class WCCommand : public Command {
public:
    WCCommand() = default;

    void execute(
        std::shared_ptr<InputStream> input,
        std::shared_ptr<OutputStream> output,
        std::shared_ptr<OutputStream> errorOutput) override;

    bool inputViaArgs() const override;
    std::string getName() const override;
    void validate() override;
private:
    std::string selectedOption;

    // Helper function used by WCCommand to count words or chars from the Input stream.
    std::size_t countWords(std::shared_ptr<InputStream> input);
    std::size_t countChars(std::shared_ptr<InputStream> input);
};

#endif //WCCOMMAND_H