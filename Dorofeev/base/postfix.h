#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <stack>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include "stack.h"

using namespace std;

class TPostfix
{
	string infix;
	string postfix;

	int GetPrecedence(char op);
	bool IsOperator(char ch);

public:
	TPostfix() : infix("a + b") {}
	void SetInfix(const string& expression) { infix = expression; }
	string GetInfix() const { return infix; }
	string GetPostfix() const { return postfix; }
	string ToPostfix();
	double Calculate();
};

#endif

