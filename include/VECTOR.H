#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>

//---------------------------------------------------------------------------------

/**
 * @class Vector
 * @brief A dynamic array that resizes itself depending on its size and capacity
 *
 * @author Caleb Goss
 * @version 02 - idk
 * @date 11/04/2022 - Realized the importance of documentation
 *
 * @version 03 - added Clear function
 * @date 14/04/2022
 *
 * @version 04 - fixed copy constructor
 * @version 05 - fixed clear function
 * @version 06 - made more debug friendly (not really)
 * @date 19/04/2022
 *
 * @version 07 - added documentation (lazy last-second effort :P)
 * @date 21/04/2022
 */
template <class T>
class Vector
{
public:
    /**
     *  @brief  Default constructor of Vector class.
     *
     *  Vector() is called upon Vector creation.
     */
    Vector();

    /**
     *  @brief The default destructor which will call the Clear function.
     *
     *  ~Vector() is called when a Vector is outside it's local scope.
     *
     *  ~Vector() is called when the program have finished execution.
     */
    ~Vector();

    /**
     *  @brief The copy constructor of a Vector.
     *
     *  The copy constructor is called when an object is intialized using another object of the same class.
     *
     *  @param newVec - reference to a constant Vector object
     */
    Vector(const Vector& newVec);

    /**
     *  @brief A boolean function that returns true if the Vector size equals 0
     *
     *  Useful for determining if a Vector is actually storing anything.
     *
     *  @return bool
     */
    bool IsEmpty() const;

    /**
     *  @brief A boolean function that returns true if the Vector size equals 0
     *
     *  @param element - a reference to a constant generic type T
     *
     *  @return void
     */
    void PushBack(const T& element);
    /**
     *  @brief The constant subscript operator overload
     *
     *  @param index - the position at which an element will be read from
     *
     *  @pre index must always be less than m_size
     *
     *  @return T - a reference to a constant generic type T
     */
    const T& operator[](size_t index) const;

    /**
     *  @brief The non-constant subscript operator overload
     *
     *  @param index - the position at which an element will be write into and read from
     *
     *  @pre index must always be less than m_size
     *
     *  @return T - a reference to a non-constant generic type T
     */
    T& operator[](size_t index);

    /**
     *  @brief The assignment operator overload for a Vector class
     *
     *  @param newVec - a constant Vector reference
     *
     *  @return Vector<T>& - reference to Vector object containing T elements
     */
    Vector<T>& operator=(const Vector<T>& newVec);

    /**
     *  @brief A function that returns the current size of the Vector
     *
     *  @return size_t
     */
    size_t Size() const;
private:
    /**
     *  @brief A method that resizes the Vector based on the paramater
     *
     *  The method is private because the user doesn't need to manually resize the Vector
     *
     *  @return void
     */
    void GenerateBlock(size_t cap);

    /**
     *  @brief a method that deletes each element of a vector, sets the data to a null pointer, sets size and capacity to 0
     *
     *  @return void
     */
    void Clear();
private:
    /// A pointer of generic type T which points to a null pointer by default
    T* m_data = nullptr;

    /// The size of the vector
    size_t m_size = 0;

    /// The maxmimum capacity of the vector
    size_t m_capacity = 0;
};

template <class T>
Vector<T>::Vector()
{
    GenerateBlock(2);
}

template <class T>
Vector<T>::~Vector()
{
    Clear();
}

template <class T>
Vector<T>::Vector(const Vector<T>& newVec)
{
    m_size = newVec.m_size;

    m_data = new T[newVec.m_size];
	
    for (unsigned i = 0; i < newVec.m_size; i++)
        m_data[i] = newVec.m_data[i];
}

template <class T>
bool Vector<T>::IsEmpty() const
{
    return (m_size == 0);
}

template <class T>
void Vector<T>::PushBack(const T& element)
{
    if (m_size >= m_capacity)
        GenerateBlock(m_capacity + m_capacity / 2);

    m_data[m_size] = element;
    m_size++;
}

template <class T>
void Vector<T>::Clear()
{
    // Deallocate memory for all elements of m_data
    delete [] m_data;

    // Set m_data to a null pointer for safety measure
    m_data = nullptr;

    m_size = 0;

    m_capacity = 0;
}

template <class T>
const T& Vector<T>::operator[](size_t index) const
{
    // size_t is never negative

    // Make sure index does not go outside the bounds of the array
    // Otherwise, throw an assertion error or something
    assert(index < m_size);

    // Return the element at index
    return m_data[index];
}

template <class T>
T& Vector<T>::operator[](size_t index)
{
    // size_t is never negative

    // Make sure index does not go outside the bounds of the array
    // Otherwise, throw an assertion error or something
    assert(index < m_size);

    // Return the element at index
    return m_data[index];
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& nv)
{
    // Prevent self-assignment
    if (this == &nv)
        return *this;

    // Deallocate pointer array
    delete [] m_data;

    m_capacity = nv.m_capacity;

    m_size = nv.m_size;

    m_data = new T[m_capacity];

    for (unsigned i = 0; i < nv.m_size; i++)
        m_data[i] = nv.m_data[i];

    return *this; // Return the object that has been re-assigned
}

template <class T>
size_t Vector<T>::Size() const
{
    return m_size;
}

template <class T>
void Vector<T>::GenerateBlock(size_t cap)
{
    // create an array of type T called block
    // set that array to a new array of T with cap amount of elements within the array
    T* block = new T[cap];

    if (cap < m_size)
        m_size = cap;

    for (size_t i = 0; i < m_size; i++)
        block[i] = m_data[i];

    // Deallocate memory for all elements of the current vector
    delete[] m_data;
	
    m_data = block;
	
    m_capacity = cap;
}

#endif // VECTOR_H
