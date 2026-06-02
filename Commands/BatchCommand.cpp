//
// Created by Mihajlo Matovic on 2. 3. 2026..
//

#include "BatchCommand.h"
#include "../Main/Reader.h"
#include "../AbstractClasses/CommandError.h"
#include <fstream>
#include <string>
#include "../Main/Interpreter.h"
#include "../InputStreams/FileInputStream.h"

void BatchCommand::validate() {

    // Checks if the filename argument is missing.
    if (args.empty()) {
        throw CommandError(ErrorType::Syntax, "Missing filename for batch", getPosition() + 6);
    }

    // Checks if exactly one argument is fiven.
    if (args.size() > 1) {
        throw CommandError(ErrorType::Syntax, "Batch command accepts exactly 1 argument", args[1].position);
    }
}


struct OutputGuard {
    Interpreter& interp;
    std::shared_ptr<OutputStream> oldOut;

    // Saves the current output stream and sets the new one.
    OutputGuard(Interpreter& i, std::shared_ptr<OutputStream> nextOut)
        : interp(i), oldOut(i.getOutput()) {
        interp.setOutput(nextOut);
    }

    // Destructor automatically restores the original output stream during stack unwinding.
    ~OutputGuard() {
        interp.setOutput(oldOut);
    }
};


void BatchCommand::execute(
    std::shared_ptr<InputStream> input,
    std::shared_ptr<OutputStream> output,
    std::shared_ptr<OutputStream> errorOutput
) {

    std::string filename = args[0].string;
    auto batchInput = std::make_shared<FileInputStream>(filename, args[0].position);

    Reader reader(batchInput.get());

    // Activate the guard to manage the Interpreter's output state.
    OutputGuard guard(Interpreter::getInstance(), output);;

    // Executes all non-empty lines from the file.
    std::string line;
   while (reader.readLine(line)) {
        if (line.empty()) {
            continue;
        }
        Interpreter::getInstance().executeLine(line);
    }
}

bool BatchCommand::acceptsInput() const {
    return false;
}

std::string BatchCommand::getName() const {
    return "BatchCommand";
}
