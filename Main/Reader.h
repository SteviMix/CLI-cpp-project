//
// Created by Mihajlo Matovic on 3. 1. 2026..
//

#ifndef READER_H
#define READER_H

#include <string>

#include "../AbstractClasses/InputStream.h"

// Class for reading the input.
class Reader {
public:
    // Constructor. Creates a reader for the given input stream.
    explicit Reader(InputStream *in);

    // Method for reading a line from the input stream.
    bool readLine(std::string& line);

private:
    static constexpr int maxLineLength = 512;

    InputStream *input;
};



#endif //READER_H
