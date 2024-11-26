/*

Name: Rupak Raut

NetID: w10153653

Program Description: This is the testcase for testing out the ExpressionTree class.

*/

#include <iostream>
#include <map>
#include "rupak_raut_expression_evaluator.hpp"

using namespace std;

void evaluate_and_print(ExpressionTree &tree, const string &expression, const map<char, float> &values) {
    tree.SetExpression(expression);
    cout << "Infix: " << tree.GetInfix() << endl;
    cout << "Postfix: " << tree.GetPostfix() << endl;
    cout << "Result: " << tree.EvaluateExpression(values) << endl << endl;
}

int main() {
    
    ExpressionTree expression_tree;

    evaluate_and_print(expression_tree, "A*(B+C*D)+X", {{'A', 2.0}, {'B', 3.0}, {'C', 10.0}, {'D', 6.0}, {'X', 5.0}});
    evaluate_and_print(expression_tree, "(A+20)/(B*8)+C", {{'A', 10.3}, {'B', 56.3}, {'C', 12.3}});
    evaluate_and_print(expression_tree, "56*B+2", {{'B', 12.0}});
    evaluate_and_print(expression_tree, "A*2^C+6", {{'A', 3.0}, {'C', 1.5}});

    return 0;
}
