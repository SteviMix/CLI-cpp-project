#include <iostream>


#include "EchoCommand.h"
#include "InputStreams/ConsoleInputStream.h"
#include "OutputStreams/ConsoleOutputStream.h"
#include "Main/Interpreter.h"


int main() {
    try {
        // Creating Console Input and Output  streams for the interpreter.
        auto input = std::make_shared<ConsoleInputStream>();
        auto output = std::make_shared<ConsoleOutputStream>();
        auto errorOutput = std::make_shared<ConsoleOutputStream>();

        // Creating and running the interpreter.
        Interpreter& Int = Interpreter::getInstance(std::move(input), std::move(output), std::move(errorOutput));
        Int.run();
    }
    // Catching errors.
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception" << std::endl;
    }
    return 0;
}