//
// Created by Mihajlo Matovic on 3. 1. 2026..
//

#include "Parser.h"

#include <sstream>
#include <algorithm>
#include <memory>

#include "../AbstractClasses/CommandError.h"
#include "../Commands/EchoCommand.h"
#include "../Commands/DateCommand.h"
#include "../Commands/TimeCommand.h"
#include "../Commands/TouchCommand.h"
#include "../Commands/WCCommand.h"
#include "../Commands/PromptCommand.h"
#include "../Commands/TruncateCommand.h"
#include "../Commands/RMCommand.h"
#include "../Commands/HeadCommand.h"
#include "../Commands/TRCommand.h"
#include "../Commands/BatchCommand.h"


std::vector<std::unique_ptr<Command>> Parser::parse(const std::string& line) {
    std::vector<std::unique_ptr<Command>> commands;


    std::vector<std::string> segments = splitByPipe(line);

    int currentPosInLine = 0;

    for (const auto& seg : segments) {
        size_t actualPos = line.find(seg, currentPosInLine);

        auto cmd = parseSegment(seg, actualPos);
        if (cmd) {
            commands.push_back(std::move(cmd));
        }
        currentPosInLine = actualPos + seg.length();
    }

    return commands;
}

std::vector<Token> Parser::tokenize(const std::string& text,size_t startPos) {
    std::vector<Token> tokens;
    std::string buffer;
    bool inQuotes = false;
    size_t tokenStart = 0; // Tracks start index of current token

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];

        // Handle Quotes (consume everything inside)
        if (inQuotes) {
            if (c == '"') {
                // End of quotes
                tokens.push_back({buffer, true, static_cast<int>(tokenStart+startPos)});
                buffer.clear();
                inQuotes = false;
            } else {
                buffer += c;
            }
            continue;
        }


        // Handle Start of Quotes
        if (c == '"') {
            if (!buffer.empty()) {
                // Save whatever was before quotes (e.g. abc"def")
                tokens.push_back({buffer, false, static_cast<int>(tokenStart+startPos)});
                buffer.clear();
            }
            inQuotes = true;
            tokenStart = i; // Token starts at the quote
        }

        //Handle Spaces (Delimiter)
        else if (std::isspace(c)) {
            if (!buffer.empty()) {
                tokens.push_back({buffer, false, static_cast<int>(tokenStart+startPos)});
                buffer.clear();
            }
            tokenStart = i + 1;
        }

        //Handle Redirection Operators (Delimiter)
        else if (c == '<' || c == '>') {
            // Save current word if exists
            if (!buffer.empty()) {
                tokens.push_back({buffer, false, static_cast<int>(tokenStart+startPos)});
                buffer.clear();
            }

            // Check for >>
            if (c == '>' && i + 1 < text.length() && text[i+1] == '>') {
                tokens.push_back({">>", false, static_cast<int>(i+startPos)});
                i++; // Skip second '>'
                tokenStart = i + 1;
            }
            else {
                // Single > or <
                std::string op(1, c);
                tokens.push_back({op, false, static_cast<int>(i+startPos)});
                tokenStart = i + 1;
            }
        }
        // 5. Regular Character
        else {
            if (buffer.empty()) {
                tokenStart = i;
            }
            buffer += c;
        }
    }

    if (!buffer.empty()) {
        tokens.push_back({buffer, false, static_cast<int>(tokenStart+startPos)});
    }

    return tokens;
}
std::vector<std::string> Parser::splitByPipe(const std::string& line) {
    std::vector<std::string> segments;
    std::string currentSegment;
    bool inQuotes = false;
    int quoteStartPos = -1;

    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '"') {
            if (!inQuotes) {
                quoteStartPos = i;
            }
            inQuotes = !inQuotes;
            currentSegment += c;
        }
        else if (c == '|' && !inQuotes) {
            if (!currentSegment.empty()) {
                segments.push_back(currentSegment);
                currentSegment.clear();
            }
            else {
                throw CommandError(ErrorType::Lexical, "Syntax Error: empty command before pipe", static_cast<int>(i));
            }
        }
        else {
            currentSegment += c;
        }
    }

    if (inQuotes) {
        throw CommandError(ErrorType::Lexical, "Syntax Error: Unclosed quote detected.", quoteStartPos);
    }

    bool isOnlyWhitespace = std::all_of(currentSegment.begin(), currentSegment.end(),
                                        [](unsigned char c){ return std::isspace(c); });

    if (!currentSegment.empty() && !isOnlyWhitespace) {
        segments.push_back(currentSegment);
    }
    else if (!segments.empty()) {
        throw CommandError(ErrorType::Lexical, "Syntax Error: No last command in pipe.", line.size() - 1);
    }

    return segments;
}

std::unique_ptr<Command> Parser::parseSegment(const std::string& segment, size_t globalPos) {

    std::vector<Token> tokens = tokenize(segment, globalPos);
    if (tokens.empty()) return nullptr;

    const Token& cmdToken = tokens[0];
    auto cmd = createCommand(cmdToken);
    cmd->setPosition(cmdToken.position);

    std::vector<Token> rawArgs;
    if (tokens.size() > 1) {
        rawArgs.assign(tokens.begin() + 1, tokens.end());
    }

    std::vector<Token> cleanArgs;
    Token redirOutToken = {"", false, -1};
    Token redirInToken = {"", false, -1};
    bool append = false;

    for (size_t i = 0; i < rawArgs.size(); ++i) {
        const auto& t = rawArgs[i];

        if (!t.inQuotes && (t.string == ">" || t.string == ">>")) {
            if (redirOutToken.string.empty()) {
                if (i + 1 < rawArgs.size()) {
                    const Token& fileToken = rawArgs[i+1];
                    if (fileToken.string == ">" || fileToken.string == ">>" || fileToken.string == "<") {
                        throw CommandError(ErrorType::Syntax, "Output redirection file missing", t.position);
                    }
                    redirOutToken = fileToken;
                    append = (t.string == ">>");
                    i++;
                } else {
                    throw CommandError(ErrorType::Syntax, "Output redirection file missing", t.position);
                }
            } else {
                throw CommandError(ErrorType::Lexical, "Multiple output redirections detected", t.position);
            }
        }
        else if (!t.inQuotes && t.string == "<") {
            if (redirInToken.string.empty()) {
                if (i + 1 < rawArgs.size()) {
                    const Token& fileToken = rawArgs[i+1];
                    if (fileToken.string == ">" || fileToken.string == ">>" || fileToken.string == "<") {
                        throw CommandError(ErrorType::Syntax, "Input redirection file missing", t.position);
                    }
                    redirInToken = fileToken;
                    i++;
                } else {
                    throw CommandError(ErrorType::Syntax, "Input redirection file missing", t.position);
                }
            } else {
                throw CommandError(ErrorType::Lexical, "Multiple input redirections detected", t.position);
            }
        }
        else {
            if (redirOutToken.string.empty()) {
                cleanArgs.push_back(t);
            } else {
                throw CommandError(ErrorType::Lexical, "Can't have arguments after output redirection", t.position);
            }
        }
    }

    cmd->setArguments(cleanArgs);

    if (!redirOutToken.string.empty()) {
        cmd->setOutputRedirection(redirOutToken, append);
    }
    if (!redirInToken.string.empty()) {
        cmd->setInputRedirection(redirInToken);
    }

    return cmd;
}

std::unique_ptr<Command> Parser::createCommand(const Token& cmdToken) {
    const std::string& cmdName = cmdToken.string;
    if (cmdName == "echo") {
        return std::make_unique<EchoCommand>();
    }
    else if (cmdName == "date") {
        return std::make_unique<DateCommand>();
    }
    else if (cmdName == "time") {
        return std::make_unique<TimeCommand>();
    }
    else if (cmdName == "touch") {
        return std::make_unique<TouchCommand>();
    }
    else if (cmdName == "wc") {
        return std::make_unique<WCCommand>();
    }
    else if (cmdName == "prompt") {
        return std::make_unique<PromptCommand>();
    }
    else if (cmdName == "truncate") {
        return std::make_unique<TruncateCommand>();
    }
    else if (cmdName == "rm") {
        return std::make_unique<RMCommand>();
    }
    else if (cmdName == "head") {
        return std::make_unique<HeadCommand>();
    }
    else if (cmdName == "tr") {
        return std::make_unique<TRCommand>();
    }
    else if (cmdName == "batch") {
        return std::make_unique<BatchCommand>();
    }
    else {
        throw CommandError(ErrorType::UnknownCommand, "Unknown command: " + cmdName, cmdToken.position);
    }
}