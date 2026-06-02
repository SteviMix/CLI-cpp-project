//
// Created by Mihajlo Matovic on 10. 1. 2026..
//

#include "StringInputStream.h"


StringInputStream::StringInputStream(std::string data)
    : data_(data)
    , pos_(0){}


bool StringInputStream::readChar(char& c) {
    if (pos_ >= data_.size()) {
        return false;
    }
    c = data_[pos_++];
    return true;
}

bool StringInputStream::readLine(std::string& line) {
    if (pos_ >= data_.size()) {
        return false;
    }
    line.clear();
    while (pos_ < data_.size()) {
        char c = data_[pos_++];
        if (c == '\n') {
            break;
        }
        line.push_back(c);
    }
    return true;
}

[[nodiscard]] bool StringInputStream::eof() const{
    return pos_ >= data_.size();
}
