//
// Created by Mihajlo Matovic on 12. 12. 2025..
//

#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H
#include <string>

// Abstract base class for all input streams.
class InputStream {
public:
    virtual ~InputStream() = default;

    // Reads one character from the stream.
    virtual bool readChar(char& c) = 0;

    // Reads one line until '\n' from the stream.
    virtual bool readLine(std::string& line) = 0;

    // Checks if the end of the stream has been reached.
    [[nodiscard]] virtual bool eof() const = 0;


};
#endif //INPUTSTREAM_H
