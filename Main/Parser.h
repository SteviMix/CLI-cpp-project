//
// Created by Mihajlo Matovic on 3. 1. 2026..
//

#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include "../Types.h"
#include "../AbstractClasses/Command.h"
// The Parser class interprets raw command lines.

class Parser {
public:
    // Parses a full command line into a sequence of commands (pipeline).
    // Throws CommandError on syntax or lexical errors.
    std::vector<std::unique_ptr<Command>> parse(const std::string& line);

private:

    // Splits the entire command line by the pipe '|' operator, respecting quotes.
    std::vector<std::string> splitByPipe(const std::string& line);

    // Parses a single pipe segment, extracting the command, arguments, and redirections.
    std::unique_ptr<Command> parseSegment(const std::string& segment, size_t globalPos);

    // Breaks a segment into tokens
    std::vector<Token> tokenize(const std::string& line, size_t currentPos);

    // Creates a command with the given name.
    std::unique_ptr<Command> createCommand(const Token& cmdToken);
};



#endif //PARSER_H
