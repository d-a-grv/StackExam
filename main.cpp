#include <iostream>
#include <string>
#include "Infix_Evaluator.h"

using namespace std;
int main() {
    Infix_Evaluator infix_evaluator;
    cout << infix_evaluator.eval("4 * (5 + 4 / 2) - 2") << endl;

    cout << infix_evaluator.eval("(5+ 2)* 3") << endl;

    cout << infix_evaluator.eval("5 * 4 / 3") << endl;

    cout << infix_evaluator.eval("5 + 2 -6") << endl;

    cout << infix_evaluator.eval("5 + 2 * 3") << endl;

    cout << infix_evaluator.eval("3 * 2 + 5") << endl;

    try {
        infix_evaluator.eval("5 + 2 -");
        cout << "no exception" << endl;
    } catch (std::invalid_argument& e) {
        cout << "exception thrown" << endl;
    }

    return 0;
}
