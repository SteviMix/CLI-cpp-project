//
// Created by Mihajlo Matovic on 22. 1. 2026..
//

#ifndef FILEOUTPUTSTREAM_H
#define FILEOUTPUTSTREAM_H

#include <fstream>
#include <string>
#include "../AbstractClasses/OutputStream.h"

// Class for writing output to a file.
class FileOutputStream : public OutputStream {
public:
    // Constructor. Opens the file in truncate or append mode.
    FileOutputStream(const std::string& filename, bool append, int pos);

    // Writes a string to the file.
    void writeString(const std::string& data) override;

    // Writes one character to the file.
    void writeChar(char c) override;

    bool isOpen() {
        return file.is_open();
    }

private:
    std::ofstream file;
};

#endif //FILEOUTPUTSTREAM_H