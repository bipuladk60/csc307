/*
Name: Bipul Adhikari
NetID: w10171505
Description: This program is a simple expression evaluator that can handle infix expressions and evaluate them using a binary tree. It can handle variables and basic arithmetic operations (+, -, *, /, ^). It can also handle variable values through a map.
*/

#include <iostream>
#include <map>
#include "bipul_adhikari_expression_evaluator.hpp"

using namespace std;

void print_evaluation(ExpressionTree& expr, const string& infix, const map<char, float>& vars) {
    expr.SetExpression(infix);
    cout << "Infix: " << expr.GetInfix() << endl
         << "Postfix: " << expr.GetPostfix() << endl
         << "Result: " << expr.EvaluateExpression(vars) << endl
         << endl;
}

int main() {
    ExpressionTree expr;

    map<char, float> test1 = {
        {'A', 2.0}, 
        {'B', 3.0}, 
        {'C', 10.0}, 
        {'D', 6.0}, 
        {'X', 5.0}
    };
    print_evaluation(expr, "A*(B+C*D)+X", test1);

    map<char, float> test2 = {
        {'A', 10.3}, 
        {'B', 56.3}, 
        {'C', 12.3}
    };
    print_evaluation(expr, "(A+20)/(B*8)+C", test2);

    print_evaluation(expr, "56*B+2", {{'B', 12.0}});
    print_evaluation(expr, "A*2^C+6", {{'A', 3.0}, {'C', 1.5}});

    return 0;
}
