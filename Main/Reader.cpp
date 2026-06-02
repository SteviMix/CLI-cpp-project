//
// Created by Mihajlo Matovic on 3. 1. 2026..
//

#include "Reader.h"

Reader::Reader(InputStream *in) : input(in) {}

bool Reader::readLine(std::string& line) {
    line.clear();
    char c;
    int count = 0;
    bool readAnything = false;

    while (input->readChar(c)) {
        if (c == '\n') {
            return true;
        }

        readAnything = true;

        if (count < maxLineLength) {
            line += c;
            count++;
        }
    }
    return readAnything;
}

