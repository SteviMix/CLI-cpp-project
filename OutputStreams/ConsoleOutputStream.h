//
// Created by Mihajlo Matovic on 3. 1. 2026..
//

#ifndef CONSOLEOUTPUTSTREAM_H
#define CONSOLEOUTPUTSTREAM_H

#include <string>

#include "../AbstractClasses/OutputStream.h"

// Class for console output stream.
class ConsoleOutputStream : public OutputStream {
public:
    ConsoleOutputStream() = default;

    // Overrideing base class methods.
    void writeChar(char c) override;
    void writeString(const std::string& str) override;
};



#endif //CONSOLEOUTPUTSTREAM_H
