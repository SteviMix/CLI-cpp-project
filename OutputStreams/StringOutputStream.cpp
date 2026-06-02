//
// Created by Mihajlo Matovic on 30. 1. 2026..
//

#include "StringOutputStream.h"


void StringOutputStream::writeString(const std::string& data) {
    buffer += data;
}

void StringOutputStream::writeChar(char c) {
    buffer += c;
}

std::string StringOutputStream::getString() const {
    return buffer;
}