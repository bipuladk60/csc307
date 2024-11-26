
/*

Name: Rupak Raut

NetID: w10153653

Program Description: The Expression class converts an infix expression (standard mathematical notation) to postfix notation (Reverse Polish Notation) and handles the precedence of operators. The ExpressionTree class builds a binary tree from a postfix expression and evaluates it, supporting variables and basic arithmetic operations (+, -, *, /, ^), with functionality to handle variable values through a map.

*/

#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <cctype>
#include <sstream>
#include <cmath>

using namespace std;

class ExpressionNode {
public:
    string token;
    float result;
    ExpressionNode* left_child;
    ExpressionNode* right_child;

    ExpressionNode(string tk) : token(tk), result(0), left_child(nullptr), right_child(nullptr) {}
};

class ExpressionTree {
private:
    ExpressionNode* root;
    string infix;
    string postfix;

    void clearTree(ExpressionNode* node) {
        if (node != nullptr) {
            clearTree(node->left_child);
            clearTree(node->right_child);
            delete node;
        }
    }

    void buildExpression() {
        stack<ExpressionNode*> stack;
        istringstream iss(postfix);
        string token;
        while (iss >> token) {
            if (isOperator(token[0]) && token.size() == 1) {
                if (stack.size() < 2) {
                
                    return;
                }
                ExpressionNode* right_child = stack.top(); stack.pop();
                ExpressionNode* left_child = stack.top(); stack.pop();
                ExpressionNode* node = new ExpressionNode(token);
                node->left_child = left_child;
                node->right_child = right_child;
                stack.push(node);
            } else {
                stack.push(new ExpressionNode(token));
            }
        }
        if (!stack.empty()) {
            root = stack.top();
            stack.pop();
        } else {
            return;
        }
    }

    bool isOperator(char c) {
        return string("+-*/^").find(c) != string::npos;
    }

    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
    }

    float evaluate_expression(float operand1, float operand2, char operation) {
        switch (operation) {
            case '+': return operand1 + operand2;
            case '-': return operand1 - operand2;
            case '*': return operand1 * operand2;
            case '/': return operand2 != 0 ? operand1 / operand2 : 0;
            case '^': return pow(operand1, operand2);
            default: return 0;
        }
    }

    float evaluate_node(ExpressionNode* node, const map<char, float>& values) {
        if (node == nullptr) return 0;
        if (!node->left_child && !node->right_child) {
            if (isdigit(node->token[0]) || isalpha(node->token[0])) {
                if (isalpha(node->token[0])) {
                    return values.at(node->token[0]);
                } else {
                    return stof(node->token);
                }
            }
        }
        float left = evaluate_node(node->left_child, values);
        float right = evaluate_node(node->right_child, values);
        return evaluate_expression(left, right, node->token[0]);
    }

public:
    ExpressionTree() : root(nullptr), infix(""), postfix("") {}

    void SetExpression(const string& exp) {
        infix = exp;
        stack<char> var_stack;
        ostringstream out;
        string token_buffer;

        auto flush_token = [&out, &token_buffer]() {
            if (!token_buffer.empty()) {
                out << token_buffer << ' ';
                token_buffer.clear();
            }
        };

        for (char token : infix) {
            if (isdigit(token) || isalpha(token)) {
                token_buffer.push_back(token);
            } else {
                flush_token();
                if (token == '(') {
                    var_stack.push(token);
                } else if (token == ')') {
                    while (!var_stack.empty() && var_stack.top() != '(') {
                        out << var_stack.top() << ' ';
                        var_stack.pop();
                    }
                    if (!var_stack.empty()) var_stack.pop();
                } else if (isOperator(token)) {
                    while (!var_stack.empty() && precedence(var_stack.top()) >= precedence(token)) {
                        out << var_stack.top() << ' ';
                        var_stack.pop();
                    }
                    var_stack.push(token);
                }
            }
        }
        flush_token();

        while (!var_stack.empty()) {
            out << var_stack.top() << ' ';
            var_stack.pop();
        }

        postfix = out.str();
        clearTree(root);
        buildExpression();
    }


    float EvaluateExpression(const map<char, float>& values) {
        return evaluate_node(root, values);
    }

    string GetInfix() { return infix; }
    string GetPostfix() { return postfix; }

    ~ExpressionTree() {
        clearTree(root);
    }
};
