//
// Created by Daniel on 9/30/24.
//

#ifndef INFIXEVAL_NEWCXXTEST_H
#define INFIXEVAL_NEWCXXTEST_H

#include <cxxtest/TestSuite.h>
#include "Infix_Evaluator.h"
#include <stdexcept>

class newCxxTest : public CxxTest::TestSuite {
public:
    void testFunctions() {
        Infix_Evaluator infix_evaluator;
        TS_ASSERT_EQUALS(infix_evaluator.eval("4 * (5 + 4 / 2) - 2"), 26);
        TS_ASSERT_EQUALS(infix_evaluator.eval("(5+ 2)* 3"), 21);
        //TS_ASSERT_EQUALS(infix_evaluator.eval("5 * 4 / 3"), 5);
        TS_ASSERT_EQUALS(infix_evaluator.eval("5 + 2 -6"), 1);
        TS_ASSERT_EQUALS(infix_evaluator.eval("5 + 2 * 3"), 11);
        TS_ASSERT_EQUALS(infix_evaluator.eval("3 * 2 + 5"), 11);
        TS_ASSERT_EQUALS(infix_evaluator.eval("6"), 6);

        TS_ASSERT_THROWS_ANYTHING(infix_evaluator.eval("5 + 2 -"));

        try {
            infix_evaluator.eval("5 + 2 -");
            TS_FAIL("Expected exception");
        } catch (std::invalid_argument& e) {
            TS_ASSERT_EQUALS(e.what(), "Invalid expression");
        }

        try {
            infix_evaluator.eval("5 + 2 - 3)");
            TS_FAIL("Expected exception");
        } catch (std::invalid_argument &e) {
            TS_ASSERT_EQUALS(e.what(), "Unmatched close parenthesis");
        }

        try {
            infix_evaluator.eval("5 + 2 - (3");
            TS_FAIL("Expected exception");
        } catch (std::invalid_argument &e) {
            TS_ASSERT_EQUALS(e.what(), "Unmatched open parenthesis");
        }
    }
};

#endif //INFIXEVAL_NEWCXXTEST_H
