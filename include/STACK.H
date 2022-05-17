#ifndef STACK_H
#define STACK_H

// LIFO - LAST_IN_FIRST_OUT

#include <stack>
using std::stack;

template <class T>
class Stack
{
public:
    bool Push(const T& data);
    bool Pop(T& data);
    bool Empty();
private:
    stack<T> m_stack;
};

template <class T>
bool Stack<T>::Empty()
{
    return m_stack.empty();
}

template <class T>
bool Stack<T>::Push(const T& data)
{
    bool isValid = true;

    try
    {
        m_stack.push(data);
    }
    catch (...)
    {
        isValid = false;
    }

    return isValid;
}

template <class T>
bool Stack<T>::Pop(T& data)
{
    if (m_stack.size() > 0)
    {
        data = m_stack.top();
        m_stack.pop();

        return true;
    }
    else
        return false;
}

#endif // STACK_H
