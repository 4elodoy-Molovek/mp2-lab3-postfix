#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    string expression;
    TPostfix postfix;
    double result;

    cout << "Введите арифметическое выражение: ";
    getline(cin, expression);

    postfix.SetInfix(expression);
    postfix.PromptForVariables();
    cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;

    string postfixExpression = postfix.ToPostfix();
    cout << "Постфиксная форма: " << postfixExpression << endl;

    try
    {
        result = postfix.Calculate();
        cout << "Результат: " << result << endl;
    }
    catch (const runtime_error& e)
    {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
