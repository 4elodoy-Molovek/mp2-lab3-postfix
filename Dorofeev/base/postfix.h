#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <map>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include "stack.h"

using namespace std;

class TPostfix
{
    string infix;
    string postfix;
    map<char, double> variables;

    int GetPrecedence(const string& op);
    bool IsOperator(const string& token);
    bool IsFunction(const string& token);
    void ParseToken(const string& token, TStack<string>& stack);

public:
    TPostfix() : infix("a + b") {}
    void SetInfix(const string& expression) { infix = expression; }
    string GetInfix() const { return infix; }
    string GetPostfix() const { return postfix; }
    void PromptForVariables();
    string ToPostfix();
    double Calculate();
};

#endif
