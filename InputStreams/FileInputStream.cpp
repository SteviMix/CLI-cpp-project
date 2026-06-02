//
// Created by Mihajlo Matovic on 10. 1. 2026..
//

#include "FileInputStream.h"
#include "../AbstractClasses/CommandError.h"

FileInputStream::FileInputStream(const std::string& filename, int pos) {
    file.open(filename);
    if (!file.is_open()) {
        throw CommandError(ErrorType::OS, "Could not open file: " + filename, pos);
    }
}


bool FileInputStream::readChar(char& c) {
    if (file.get(c)) {
        return true;
    }
    return false;
}

bool FileInputStream::readLine(std::string& line) {
    if (std::getline(file, line)) {
        return true;
    }
    return false;
}

bool FileInputStream::eof() const {
    return file.eof();
}

bool FileInputStream::isOpen() const {
    return file.is_open();
}
