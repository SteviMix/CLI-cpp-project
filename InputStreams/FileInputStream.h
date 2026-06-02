//
// Created by Mihajlo Matovic on 10. 1. 2026..
//

#ifndef FILEINPUTSTREAM_H
#define FILEINPUTSTREAM_H

#include "fstream"

#include "../AbstractClasses/InputStream.h"

// Class for input stream from a file.
class FileInputStream : public InputStream {
public:

    // Constructor. Creat file stream object with the given filename.
    explicit FileInputStream(const std::string& filename, int pos);

    // Overriding base class methods.
    bool readChar(char& c) override;
    bool readLine(std::string& line) override;
    [[nodiscard]] bool eof() const override;

    // Class method that checks if the file is open.
    bool isOpen() const;
private:
    std::ifstream file;
};



#endif //FILEINPUTSTREAM_H
