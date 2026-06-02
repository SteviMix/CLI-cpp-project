//
// Created by Mihajlo Matovic on 12. 12. 2025..
//

#ifndef OUTPUTSTREAM_H
#define OUTPUTSTREAM_H
#include <string>


// Abstract class for all output streams.
class OutputStream {
public:
    virtual ~OutputStream() = default;

    // Writes a string in the output stream.
    virtual void writeString(const std::string& data) = 0;

    // Writes one character in the output stream.
    virtual void writeChar(char c) = 0;
};
#endif //OUTPUTSTREAM_H
