//
// Created by Mihajlo Matovic on 30. 1. 2026..
//

#ifndef STRINGOUPUTSTREAM_H
#define STRINGOUPUTSTREAM_H

#include <string>
#include "OutputStream.h"

// Class for writing output to a string buffer (used for pipes).
class StringOutputStream : public OutputStream {
public:
    // Writes a string to the buffer.
    void writeString(const std::string& data) override;

    // Writes one character to the buffer.
    void writeChar(char c) override;

    // Returns the current content of the buffer.
    std::string getString() const;

private:
    std::string buffer;
};



#endif //STRINGOUPUTSTREAM_H
