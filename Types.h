//
// Created by Mihajlo Matovic on 7. 1. 2026..
//

#ifndef TYPES_H
#define TYPES_H

#include <string>


// Structure for Tokens that are produced by the reader.
// It contains Token value(string) and if it is in quoutes.
struct Token {
    std::string string;
    bool inQuotes = false;
    int position = 0;
};

// Enumerates error types.
enum class ErrorType {
    None,           // No error.
    Lexical,        // Lexical errors
    UnknownCommand, // Command does not exist.
    Syntax,         // Syntax error.
    Semantic,       // Semantic error.
    Execution,      // Specific command error.
    OS              // System error.
};

#endif //TYPES_H
