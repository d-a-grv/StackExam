//
// Created by Daniel on 9/26/24.
//

#include "Infix_Evaluator.h"

int Infix_Evaluator::eval(string expression) {
    expression = remove_space(expression);

    if (expression.empty()) {
        return 0;
    }
    if (expression.length() == 1) {
        if (isdigit(expression[0])) {
            return stoi(expression);
        } else {
            throw std::invalid_argument("Invalid expression");
        }
    }
    if (expression.length() == 2) { throw std::invalid_argument("Invalid expression");}

    try {
        return helper_eval(expression, false);
    } catch (std::invalid_argument &e) {
        throw std::invalid_argument(e.what());
    }
    //return helper_eval(expression, false);
}

bool Infix_Evaluator::is_operator(char ch) const {
    return OPERATORS.find(ch) != string::npos;
}

int Infix_Evaluator::precedence(char op) const {
    return PRECEDENCE[OPERATORS.find(op)];
}

string Infix_Evaluator::remove_space(string &expression) {
    string new_expression;
    for (char ch : expression) {
        if (ch != ' ') {
            new_expression += ch;
        }
    }
    return new_expression;
}

int Infix_Evaluator::helper_eval(string &expression, bool insidePar) {
    std::stack<char> operator_stack;
    std::stack<int> operand_stack;

    while (!expression.empty()) {
        char curr = expression[0];

        //checks if the el is an operator
        //checks if the operator stack is empty or the precedence of el is higher than the top of the stack
        if (is_operator(curr) &&
            (operator_stack.empty() || precedence(curr) > precedence(operator_stack.top()))) {
            operator_stack.push(curr);
        } else if (isdigit(curr)) { //if curr el is an operand push it to the operand stack
            operand_stack.push(stoi(std::string(1, curr)));
        } else if (curr == '(') { // if we come across parentheses, we evaluate the expression inside the parentheses
            if (expression.size() == 1) {
                throw std::invalid_argument("Invalid format");
            } else if (expression[1] == ')') { //if the expression is () then error
                throw std::invalid_argument("Empty parenthesis");
            }

            //remove the open parenthesis
            expression = expression.substr(1, expression.size());
            operand_stack.push(helper_eval(expression, true)); //evaluate the expression inside the parentheses

            //if it's the end of expression and we're still inside the parenthesis, error
            if (expression.empty()) {
                throw std::invalid_argument("Unmatched open parenthesis");
            }
        } else if (curr == ')') {
            if (insidePar) { //if we are at the end of parenthesis, return the result
                return calculate_stacks(operand_stack, operator_stack);
            } else { //if the curr el is a close parenthesis, and we are not inside a parenthesis, error
                throw std::invalid_argument("Unmatched close parenthesis");
            }
        //checks if el is operator and its precedence is less than the top of the stack
        } else if (is_operator(curr) && precedence(operator_stack.top()) >= precedence(curr)) {
            //calculate the stacks of operators with higher precedence than the curr el
            //function modifies the stacks, so we don't need to push the curr el

            if (operand_stack.size() < operator_stack.size() + 1) {
                throw std::invalid_argument("Invalid expression");
            }
            calculate_stacks(operand_stack, operator_stack);
            operator_stack.push(curr);
        } else { //if the el is not a valid operator or operand, error
            throw std::invalid_argument("Invalid expression");
        }

        //remove the el from the expression
        expression = expression.substr(1, expression.size());
    }

    if (operand_stack.size() < operator_stack.size() + 1) {
        throw std::invalid_argument("Invalid expression");
    }
    return calculate_stacks(operand_stack, operator_stack);
}

int Infix_Evaluator::calculate_stacks(std::stack<int> &operand_stack, std::stack<char> &operator_stack) {
//    if (operand_stack.size() < operator_stack.size() + 1) {
//        throw Syntax_Error("Invalid expression");
//    }

    while (!operator_stack.empty()) {
        int rhs = operand_stack.top();
        operand_stack.pop();
        int lhs = operand_stack.top();
        operand_stack.pop();
        char op = operator_stack.top();
        operator_stack.pop();
        int result = 0;
        switch (op) {
            case '+': result = lhs + rhs;
                break;
            case '-': result = lhs - rhs;
                break;
            case '*': result = lhs * rhs;
                break;
            case '/': result = lhs / rhs;
                break;
        }
        operand_stack.push(result);
    }
    return operand_stack.top();
}
