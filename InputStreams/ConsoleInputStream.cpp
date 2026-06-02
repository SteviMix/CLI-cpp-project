//
// Created by Mihajlo Matovic on 3. 1. 2026..
//


#include <iostream>
#include "ConsoleInputStream.h"


bool ConsoleInputStream::readChar(char& c) {
    if (std::cin.get(c)) {
        return true;
    }
    return false;
}


bool ConsoleInputStream::readLine(std::string& line) {
    if (std::getline(std::cin, line)) {
        return true;
    }
    return false;
}

bool ConsoleInputStream:: eof() const {
    return std::cin.eof();
}
