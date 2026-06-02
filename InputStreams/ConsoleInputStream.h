//
// Created by Mihajlo Matovic on 3. 1. 2026..
//

#ifndef CONSOLEINPUTSTREAM_H
#define CONSOLEINPUTSTREAM_H

#include <string>
#include <sstream>
#include "../AbstractClasses/InputStream.h"

// Class for console input stream
class ConsoleInputStream : public InputStream {
public:
    ConsoleInputStream () = default;

    // Override of base class methods.
    bool readChar(char& c) override;
    bool readLine(std::string& line) override;
    [[nodiscard]] bool eof() const override;
};



#endif //CONSOLEINPUTSTREAM_H
