#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <stdexcept>

//---------------------------------------------------------------------------------

using std::vector;

template <class T>
class Vector
{
public:
    bool PushBack(const T& element);

    bool PopBack(T& element) const;

    const T& operator[](size_t index) const;

    T& operator[](size_t index);

    bool Empty() const;

    size_t Size() const;
private:
    vector<T> m_vector;
};

template <class T>
bool Vector<T>::PushBack(const T& element)
{
    try
    {
        m_vector.push_back(element);
    }
    catch (...)
    {
        return false;
    }

    return true;
}

template <class T>
bool Vector<T>::PopBack(T& element) const
{
    if (m_vector.size() > 0)
    {
        element = m_vector.back();
        m_vector.pop_back();
        return true;
    }
    else
        return false;
}

template <class T>
const T& Vector<T>::operator[](size_t index) const
{
    if (index < m_vector.size())
        return m_vector[index];
    else
        throw std::invalid_argument("Underflow!");
}

template <class T>
T& Vector<T>::operator[](size_t index)
{
    if (index < m_vector.size())
        return m_vector[index];
    else
        throw std::invalid_argument("Underflow!");
}

template <class T>
bool Vector<T>::Empty() const
{
    return m_vector.empty();
}

template <class T>
size_t Vector<T>::Size() const
{
    return m_vector.size();
}
#endif // VECTOR_H
