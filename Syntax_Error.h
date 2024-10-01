//
// Created by Daniel on 10/1/24.
//

#ifndef INFIXEVAL_SYNTAX_ERROR_H
#define INFIXEVAL_SYNTAX_ERROR_H

#include <stdexcept>
#include <string>

class Syntax_Error : public std::invalid_argument {
public:
    Syntax_Error(std::string msg) : std::invalid_argument(msg) {}
};

#endif //INFIXEVAL_SYNTAX_ERROR_H
