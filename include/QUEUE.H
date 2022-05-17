#ifndef QUEUE_H
#define QUEUE_H

// FIFO - First_In_First_Out

#include "queue"
using std::queue;

template <class T>
class Queue
{
public:
    bool Enqueue(const T& data);
    bool Dequeue(T& data);
    bool Empty();
private:
    queue<T> m_queue;
};

template<class T>
bool Queue<T>::Empty()
{
    return m_queue.empty();
}

template <class T>
bool Queue<T>::Enqueue(const T& data)
{
    bool isValid = true;

    try
    {
        m_queue.push(data);
    }
    catch(...)
    {
        isValid = false;
    }

    return isValid;
}

template<class T>
bool Queue<T>::Dequeue(T& data)
{
    if (m_queue.size() > 0)
    {
        data = m_queue.front();
        m_queue.pop();

        return true;
    }
    else
        return false;
}



#endif // QUEUE_H
