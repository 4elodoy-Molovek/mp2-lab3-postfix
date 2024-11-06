//#include <sstream>
//#include "postfix.h"
//
//int TPostfix::GetPrecedence(char op) 
//{
//    if (op == '+' || op == '-') return 1;
//    if (op == '*' || op == '/') return 2;
//    return 0;
//}
//
//bool TPostfix::IsOperator(char ch) 
//{
//    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
//}
//
//string TPostfix::ToPostfix() 
//{
//    postfix.clear();
//    TStack<char> stack(MaxStackSize);
//
//    for (char ch : infix) 
//    {
//        if (isspace(ch)) continue;
//
//        if (isalnum(ch)) // Operand
//        {  
//            postfix += ch;
//        }
//        else if (ch == '(') 
//        {
//            stack.Push(ch);
//        }
//        else if (ch == ')') 
//        {
//            while (!stack.IsEmpty() && stack.Top() != '(')
//                postfix += stack.Pop();
//            stack.Pop();  // Pop '('
//        }
//        else if (IsOperator(ch)) 
//        {
//            while (!stack.IsEmpty() && GetPrecedence(stack.Top()) >= GetPrecedence(ch))
//                postfix += stack.Pop();
//            stack.Push(ch);
//        }
//    }
//
//    while (!stack.IsEmpty())
//        postfix += stack.Pop();
//
//    return postfix;
//}
//
//double TPostfix::Calculate() 
//{
//    TStack<double> stack(MaxStackSize);
//
//    for (char ch : postfix) 
//    {
//        if (isalnum(ch)) // Operand
//        {  
//            double val = ch - '0';  // Assume single-digit operands for simplicity
//            stack.Push(val);
//        }
//        else if (IsOperator(ch)) 
//        {
//            double right = stack.Pop();
//            double left = stack.Pop();
//
//            switch (ch) 
//            {
//            case '+': stack.Push(left + right); break;
//            case '-': stack.Push(left - right); break;
//            case '*': stack.Push(left * right); break;
//            case '/':
//                if (right == 0) throw runtime_error("Division by zero");
//                stack.Push(left / right);
//                break;
//            }
//        }
//    }
//
//    return stack.Pop();
//}
