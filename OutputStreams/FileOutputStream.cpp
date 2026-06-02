//
// Created by Mihajlo Matovic on 22. 1. 2026..
//

#include "FileOutputStream.h"
#include "../AbstractClasses/CommandError.h"

FileOutputStream::FileOutputStream(const std::string& filename, bool append, int pos) {
    // Determine the open mode (overwrite or append).
    std::ios_base::openmode mode = std::ios::out;
    if (append) {
        mode |= std::ios::app;
    } else {
        mode |= std::ios::trunc;
    }

    // Attempt to open the file.
    file.open(filename, mode);

    // Check if the file opened successfully.
    if (!file.is_open()) {
        throw CommandError(ErrorType::OS, "Could not open output file: " + filename, pos);
    }
}


void FileOutputStream::writeString(const std::string& data) {
    if (file.is_open()) {
        file << data;
    }
}

void FileOutputStream::writeChar(char c) {
    if (file.is_open()) {
        file.put(c);
    }
}