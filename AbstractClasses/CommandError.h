//
// Created by Mihajlo Matovic on 13. 12. 2025..
//

#ifndef COMMANDERROR_H
#define COMMANDERROR_H
#include <string>
#include <stdexcept>
#include "../Types.h"

// Custom exception class for Interpreter.
class CommandError : public std::runtime_error{
public:
    // Constructor. Accepts specific error type and error description.
    CommandError(ErrorType errorType, const std::string &errorMessage, int position = -1)
        : std::runtime_error(errorMessage), m_type(errorType), m_position(position) {}

    ErrorType getType() const { return m_type; }

    int getPosition() const { return m_position; }

private:
    ErrorType m_type;
    int m_position;
};
#endif //COMMANDERROR_H
