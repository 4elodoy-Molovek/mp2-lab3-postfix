#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
    T* pMem;
    int size;
    int top;

public:
    TStack(int _size)
    {
        size = _size;
        top = -1;
        if ((size < 1) || (size > MaxStackSize))
            throw size;
        pMem = new T[size];
    }

    ~TStack()
    {
        delete[] pMem;
    }

    void Push(const T& val)
    {
        if (IsFull())
            throw "Stack overflow";
        pMem[++top] = val;
    }

    T Pop()
    {
        if (IsEmpty())
            throw "Stack underflow";
        return pMem[top--];
    }

    T Top() const
    {
        if (IsEmpty())
            throw "Stack is empty";
        return pMem[top];
    }

    bool IsEmpty() const
    {
        return top == -1;
    }

    bool IsFull() const
    {
        return top == size - 1;
    }
};

#endif

