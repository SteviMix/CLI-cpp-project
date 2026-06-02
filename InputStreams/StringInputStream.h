//
// Created by Mihajlo Matovic on 10. 1. 2026..
//

#ifndef STRINGINPUTSTREAM_H
#define STRINGINPUTSTREAM_H

#include "ConsoleInputStream.h"

// Class for input stream from a string.
class StringInputStream : public InputStream {
public:

    // Constructor. Creates the String stream from the given string.
    explicit StringInputStream(std::string data);

    // Overriding base class methods.
    bool readChar(char& c) override;
    bool readLine(std::string& line) override;
    [[nodiscard]] bool eof() const override;

private:
    std::string data_;
    int pos_ = 0;
};



#endif //STRINGINPUTSTREAM_H
