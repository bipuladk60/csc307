/*
Name: Bipul Adhikari
NetID: w10171505
Description: This program is a simple expression evaluator that can handle infix expressions and evaluate them using a binary tree. It can handle variables and basic arithmetic operations (+, -, *, /, ^). It can also handle variable values through a map.
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

class ExpressionNode
{
public:
    string token;
    float value;
    ExpressionNode* left;
    ExpressionNode* right;

    ExpressionNode(string tk) : token(tk), value(0), left(nullptr), right(nullptr) {}
};

class ExpressionTree
{
private:
    ExpressionNode* root;
    string infix;
    string postfix;

    void clearTree(ExpressionNode* node)
    {
        if (node != nullptr)
        {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }

    

    bool isOperator(char c)
    {
        const char operators[] = {'+', '-', '*', '/', '^'};
        for (char op : operators) {
            if (c == op) return true;
        }
        return false;
    }

    void buildExpression()
    {
        stack<ExpressionNode*> stack;
        istringstream iss(postfix);
        string token;
        while (iss >> token) {
            if (isOperator(token[0]) && token.size() == 1)
            {
                if (stack.size() < 2)
                {
                    return;
                }
                ExpressionNode* right_child = stack.top(); stack.pop();
                ExpressionNode* left_child = stack.top(); stack.pop();
                ExpressionNode* node = new ExpressionNode(token);
                node->left = left_child;
                node->right = right_child;
                stack.push(node);
            }
            else
            {
                stack.push(new ExpressionNode(token));
            }
        }
        if (!stack.empty())
        {
            root = stack.top();
            stack.pop();
        } else
        {
            return;
        }
    }

    float evaluate_expression(float a, float b, char op)
    {
        if (op == '+') return a + b;
        else if (op == '-') return a - b;
        else if (op == '*') return a * b;
        else if (op == '/') return b != 0 ? a / b : 0;
        else if (op == '^') return pow(a, b);
        return 0;
    }

    int precedence(char op)
    {
        switch(op) {
            case '^': return 3;
            case '*':
            case '/': return 2;
            case '+':
            case '-': return 1;
            default: return 0;
        }
    }


    float evaluate_node(ExpressionNode* node, const map<char, float>& values)
    {
        if (node == nullptr) return 0;
        if (!node->left && !node->right)
        {
            if (isdigit(node->token[0]) || isalpha(node->token[0]))
            {
                if (isalpha(node->token[0]))
                {
                    return values.at(node->token[0]);
                }
                else
                {
                    return stof(node->token);
                }
            }
        }
        float left = evaluate_node(node->left, values);
        float right = evaluate_node(node->right, values);
        return evaluate_expression(left, right, node->token[0]);
    }

public:
    ExpressionTree() : root(nullptr), infix(""), postfix("") {}

    void SetExpression(const string& exp)
    {
        infix = exp;
        stack<char> var_stack;
        ostringstream out;
        string token_buffer;

        auto flush_token = [&out, &token_buffer]()
        {
            if (!token_buffer.empty()) {
                out << token_buffer << ' ';
                token_buffer.clear();
            }
        };

        for (char token : infix)
        {
            if (isdigit(token) || isalpha(token))
            {
                token_buffer.push_back(token);
            } 
            else
            {
                flush_token();
                if (token == '(')
                {
                    var_stack.push(token);
                } else if (token == ')')
                {
                    while (!var_stack.empty() && var_stack.top() != '(')
                    {
                        out << var_stack.top() << ' ';
                        var_stack.pop();
                    }
                    if (!var_stack.empty()) var_stack.pop();
                } 
                else if (isOperator(token))
                {
                    while (!var_stack.empty() && precedence(var_stack.top()) >= precedence(token))
                    {
                        out << var_stack.top() << ' ';
                        var_stack.pop();
                    }
                    var_stack.push(token);
                }
            }
        }
        flush_token();

        while (!var_stack.empty())
        {
            out << var_stack.top() << ' ';
            var_stack.pop();
        }

        postfix = out.str();
        clearTree(root);
        buildExpression();
    }


    float EvaluateExpression(const map<char, float>& values)
    {
        return evaluate_node(root, values);
    }

    string GetInfix() { return infix; }
    string GetPostfix() { return postfix; }

    ~ExpressionTree()
    {
        clearTree(root);
    }
};
