//
// Created by Daniel on 9/26/24.
//

#ifndef INFIXEVAL_INFIX_EVALUATOR_H
#define INFIXEVAL_INFIX_EVALUATOR_H

#include <string>
#include <stack>
#include <stdexcept>
#include "Syntax_Error.h"
using std::string;

class Infix_Evaluator {
public:
    Infix_Evaluator() = default;

    int eval(string expression);

private:
    const string OPERATORS = "+-*/";
    const int PRECEDENCE[4] = {1, 1, 2, 2};

    //returns true if ch is an operator
    bool is_operator(char ch) const;
    //returns the precedence of the operator
    int precedence(char op) const;
    //removes spaces from the expression
    string remove_space(string &expression);
    // recursive function; evaluates the expression
    int helper_eval(string &expression, bool insidePar = false);
    // calculates the stacks
    int calculate_stacks(std::stack<int> &operand_stack, std::stack<char> &operator_stack);
};

#endif //INFIXEVAL_INFIX_EVALUATOR_H
