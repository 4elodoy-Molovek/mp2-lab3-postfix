#include "postfix.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <cctype>

int TPostfix::GetPrecedence(const string& op)
{
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    if (IsFunction(op)) return 4;
    return 0;
}

bool TPostfix::IsOperator(const string& token)
{
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

bool TPostfix::IsFunction(const string& token)
{
    return token == "sin" || token == "cos" || token == "tan" || token == "cot";
}

void TPostfix::PromptForVariables()
{
    size_t i = 0;
    while (i < infix.size())
    {
        if (isalpha(infix[i]))
        {
            // Проверка на функцию, если обнаружена строка, начинающаяся с буквы
            string possibleFunction;
            size_t j = i;
            while (j < infix.size() && isalpha(infix[j]))
            {
                possibleFunction += infix[j];
                ++j;
            }

            if (IsFunction(possibleFunction))
            {
                i = j; // Пропускаем название функции
            }
            else
            {
                // Это не функция, значит, переменная
                char variable = infix[i];
                if (variables.find(variable) == variables.end())
                {
                    double val;
                    cout << "Введите значение для " << variable << ": ";
                    cin >> val;
                    variables[variable] = val;
                }
                ++i;
            }
        }
        else
        {
            ++i;
        }
    }
}


string TPostfix::ToPostfix()
{
    postfix.clear();
    TStack<string> stack(MaxStackSize);
    stringstream tokens;
    size_t i = 0;

    while (i < infix.size())
    {
        if (isspace(infix[i]))
        {
            ++i;
            continue;
        }

        if (isdigit(infix[i]) || (infix[i] == '.' && isdigit(infix[i + 1]))) // Число
        {
            string num;
            while (i < infix.size() && (isdigit(infix[i]) || infix[i] == '.'))
                num += infix[i++];
            tokens << num << " ";
        }
        else if (isalpha(infix[i])) // Функция или переменная
        {
            string func;
            while (i < infix.size() && isalpha(infix[i]))
                func += infix[i++];
            if (IsFunction(func))
                stack.Push(func);
            else
                tokens << func << " ";
        }
        else if (infix[i] == '(')
        {
            stack.Push(string(1, infix[i]));  // Добавляем '(' в стек
            ++i;
        }
        else if (infix[i] == ')')
        {
            while (!stack.IsEmpty() && stack.Top() != "(")
                tokens << stack.Pop() << " "; // Переносим операторы в постфиксную запись
            stack.Pop();  // Удаляем '('
            if (!stack.IsEmpty() && IsFunction(stack.Top()))
                tokens << stack.Pop() << " "; // Обрабатываем функцию, если есть
            ++i;
        }
        else if (IsOperator(string(1, infix[i])))
        {
            string op(1, infix[i]);
            while (!stack.IsEmpty() && GetPrecedence(stack.Top()) >= GetPrecedence(op))
                tokens << stack.Pop() << " ";
            stack.Push(op);
            ++i;
        }
    }

    while (!stack.IsEmpty())
        tokens << stack.Pop() << " ";

    postfix = tokens.str();
    return postfix;
}

double TPostfix::Calculate()
{
    TStack<double> stack(MaxStackSize);
    istringstream tokens(postfix);
    string token;

    while (tokens >> token)
    {
        if (isdigit(token[0]) || (token[0] == '.' && token.size() > 1)) // Число
        {
            stack.Push(stod(token));
        }
        else if (isalpha(token[0]) && !IsFunction(token)) // Переменная
        {
            stack.Push(variables[token[0]]);
        }
        else if (IsOperator(token))
        {
            double right = stack.Pop();
            double left = stack.Pop();
            if (token == "+") stack.Push(left + right);
            else if (token == "-") stack.Push(left - right);
            else if (token == "*") stack.Push(left * right);
            else if (token == "/")
            {
                if (right == 0) throw runtime_error("Деление на ноль");
                stack.Push(left / right);
            }
            else if (token == "^") stack.Push(pow(left, right));
        }
        else if (IsFunction(token))
        {
            double value = stack.Pop();
            if (token == "sin") stack.Push(sin(value));
            else if (token == "cos") stack.Push(cos(value));
            else if (token == "tan") stack.Push(tan(value));
            else if (token == "cot") stack.Push(1 / tan(value));
        }
    }

    return stack.Pop();
}
