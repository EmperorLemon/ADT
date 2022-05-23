#ifndef CUSTOM_VECTOR_H
#define CUSTOM_VECTOR_H

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
    bool Empty() const;

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
    const T& operator[](int index) const;

    /**
     *  @brief The non-constant subscript operator overload
     *
     *  @param index - the position at which an element will be write into and read from
     *
     *  @pre index must always be less than m_size
     *
     *  @return T - a reference to a non-constant generic type T
     */
    T& operator[](int index);

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
    int Size() const;
private:
    /**
     *  @brief A useful method that resizes the Vector based on the paramater
     *
     *  The method is private because the user doesn't need to manually resize the Vector
     *
     *  @return void
     */
    void GenerateBlock(int cap);

    /**
     *  @brief a method that deletes each element of a vector, sets the data to a null pointer, sets size and capacity to 0
     *
     *  @return void
     */
    void Clear();
private:
    /// A pointer of generic type T which points to a null pointer by default
    /** @warning I'm scared of pointers*/
    T* m_data = nullptr;

    /// The size of the vector
    int m_size = 0;

    /// The maxmimum capacity of the vector
    int m_capacity = 0;
};

template <class T>
Vector<T>::Vector()
{
    // Generate 2 blocks of memory upon object creation
    GenerateBlock(2);
}

template <class T>
Vector<T>::~Vector()
{
    // Remove all elements of a Vector
    Clear();
}

template <class T>
Vector<T>::Vector(const Vector<T>& newVec)
{
    // set the current vector's size to the new vector's size
    m_size = newVec.m_size;

    // set m_data to a new array of T with the new vector's size as the amount of elements within that array
    // I was never too great at explaining things in verbose detail, especially if that thing is very abstract
    m_data = new T[newVec.m_size];

    // set each element of m_data to each element of the new vectors data
    for (unsigned i = 0; i < newVec.m_size; i++)
        m_data[i] = newVec.m_data[i];
}

template <class T>
bool Vector<T>::Empty() const
{
    // return true if size equals 0
    return (m_size == 0);
    // return false if size does not equal 0
}

template <class T>
void Vector<T>::PushBack(const T& element)
{
    // if the current size is greater-than or equal to the capacity
    if (m_size >= m_capacity)
        GenerateBlock(m_capacity + m_capacity / 2); // then generate a block of memory that is 1.5 times its capacity

    m_data[m_size] = element; // data at index m_size is set to object reference
    m_size++; // increment size by 1
}

template <class T>
void Vector<T>::Clear()
{
    // Deallocate memory for all elements of m_data
    delete [] m_data;

    // Set m_data to a null pointer for safety measure
    m_data = nullptr;

    // Set the size to 0
    m_size = 0;

    // Set the capacity to 0
    m_capacity = 0;
}

template <class T>
const T& Vector<T>::operator[](int index) const
{
    // Return the element at index
    return m_data[index];
}

template <class T>
T& Vector<T>::operator[](int index)
{

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

    // Set the current vector's capacity to the new vector's capacity
    m_capacity = nv.m_capacity;

    // Set the current vector's size to the new vector's size
    m_size = nv.m_size;

    // Allocate memory for new vector's data array containing m_capacity number of elements
    m_data = new T[m_capacity];

    // Assign current data to new data
    for (int i = 0; i < nv.m_size; i++)
        m_data[i] = nv.m_data[i];

    return *this; // Return the object that has been re-assigned
}

template <class T>
int Vector<T>::Size() const
{
    // Return the current size of the vector
    return m_size;
}

template <class T>
void Vector<T>::GenerateBlock(int cap)
{
    // create an array of type T called block
    // set that array to a new array of T with cap amount of elements within the array
    T* block = new T[cap];

    // If the cap is less than the current size
    if (cap < m_size)
        m_size = cap; // Then the current size equals the cap

    // Set each element of block to each element of the vector's data
    for (int i = 0; i < m_size; i++)
        block[i] = m_data[i];

    // Deallocate memory for all elements of the current vector
    delete[] m_data;
    // Set the data to the block of data
    m_data = block;
    // Set the capacity to the cap
    m_capacity = cap;
}

#endif // VECTOR_H
