//
// Created by Mihajlo Matovic on 3. 1. 2026..
//

#include "ConsoleOutputStream.h"

#include <iostream>


void ConsoleOutputStream::writeChar(char c) {
    std::cout << c;
}

void ConsoleOutputStream::writeString(const std::string& str) {
    std::cout << str;
}
