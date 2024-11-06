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

int TPostfix::GetPrecedence(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool TPostfix::IsOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

string TPostfix::ToPostfix()
{
    postfix.clear();
    TStack<char> stack(MaxStackSize);
    string number;

    for (char ch : infix)
    {
        if (isspace(ch))
            continue;

        if (isdigit(ch))
        {
            number += ch;  // Собираем число, чтобы обработать многозначные числа
        }
        else
        {
            if (!number.empty())
            {
                postfix += number + ' ';  // Добавляем число с пробелом
                number.clear();
            }
            if (ch == '(')
            {
                stack.Push(ch);
            }
            else if (ch == ')')
            {
                while (!stack.IsEmpty() && stack.Top() != '(')
                {
                    postfix += stack.Pop();
                    postfix += ' ';
                }
                stack.Pop();  // Убираем '(' из стека
            }
            else if (IsOperator(ch))
            {
                while (!stack.IsEmpty() && GetPrecedence(stack.Top()) >= GetPrecedence(ch))
                {
                    postfix += stack.Pop();
                    postfix += ' ';
                }
                stack.Push(ch);
            }
        }
    }

    if (!number.empty())
    {
        postfix += number + ' ';
        number.clear();
    }

    while (!stack.IsEmpty())
    {
        postfix += stack.Pop();
        postfix += ' ';
    }

    return postfix;
}


double TPostfix::Calculate()
{
    TStack<double> stack(MaxStackSize);
    istringstream tokens(postfix);
    string token;

    while (tokens >> token)
    {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) // Число
        {
            double val = stod(token);
            stack.Push(val);
        }
        else if (IsOperator(token[0]))
        {
            double right = stack.Pop();
            double left = stack.Pop();

            switch (token[0])
            {
            case '+': stack.Push(left + right); break;
            case '-': stack.Push(left - right); break;
            case '*': stack.Push(left * right); break;
            case '/':
                if (right == 0) throw runtime_error("Division by zero");
                stack.Push(left / right);
                break;
            }
        }
    }

    return stack.Pop();
}