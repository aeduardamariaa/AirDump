#ifndef EMBLATE_VECTOR_H
#define EMBLATE_VECTOR_H

#include "./Defines.h"
#include "../Core/Exception.h"

namespace Emblate
{
    /**
     * Container where the elements are stored contiguously, which means
     * that elements can be accessed not only through iterators, but
     * also using offsets to regular pointers to elements. This means
     * that a pointer to an element of a vector may be passed to any
     * function that expects a pointer to an element of an array.
     *
     * @tparam T The type of the elements.
     */
    template<class T>
    class Vector
    {
    public:
        Vector();
        Vector(size_t size);
        Vector(size_t size, const T& value);
        Vector(const T* array, size_t size);
        Vector(const Vector& other);

        ~Vector();

        Vector<T>& operator=(const Vector<T>& other);

        void reserve(size_t capacity);
        void shrink_to_fit();

        bool empty() const;
        size_t size() const;
        size_t capacity();

        T& at(size_t pos);
        const T& at(size_t pos) const;

        T& operator[](size_t pos);
        const T& operator[](size_t pos) const;

        T& front();
        const T& front() const;

        T& back();
        const T& back() const;

        T* data();
        const T* data() const;

        void clear();

        void push_back(T value);
        void pop_back();

        void swap(size_t pos1, size_t pos2);

    private:
        T* m_data;
        size_t m_size;
        size_t m_capacity;
    };

    /**
     * Default constructor. Constructs an empty container.
     *
     * @tparam T The type of the elements.
     */
    template<class T>
    Vector<T>::Vector()
            : m_data(), m_size(), m_capacity() {}

    /**
     * Constructs the container with given size _size_ and unitialized
     * elements.
     *
     * @tparam T The type of the elements.
     * @param size Initial size.
     */
    template<class T>
    Vector<T>::Vector(size_t size)
            : m_data(new T[size]), m_size(size), m_capacity(size)
    {
        for (size_t i = 0; i < m_capacity; i++)
        {
            m_data[i] = T();
        }
    }

    /**
     * Constructs the container with given size _size_ filled with
     * _value_.
     *
     * @tparam T The type of the elements.
     * @param size Initial size.
     * @param value Initial value.
     */
    template<class T>
    Vector<T>::Vector(size_t size, const T& value)
            : m_data(new T[size]), m_size(size), m_capacity(size)
    {
        for (size_t i = 0; i < m_capacity; i++)
        {
            m_data[i] = value;
        }
    }

    /**
     * Constructs the container by copying the elements of a plain
     * C-style array.
     *
     * @tparam T The type of the elements.
     * @param array Plain C-style array.
     * @param size Size of the base array.
     */
    template<class T>
    Vector<T>::Vector(const T* array, size_t size)
            : m_data(new T[size]), m_size(size), m_capacity(size)
    {
        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i] = array[i];
        }
    }

    /**
     * Copy constructor. Constructs the container with the copy of the
     * contents of other.
     *
     * @tparam T The type of the elements.
     * @param other Container to be copied.
     */
    template<class T>
    Vector<T>::Vector(const Vector<T>& other)
            : m_data(new T[other.m_size]), m_size(other.m_size),
              m_capacity(other.m_size)
    {
        for (size_t i = 0; i < other.m_size; i++)
        {
            m_data[i] = other.m_data[i];
        }
    }

    /**
     * Destructs the container object.
     *
     * @tparam T The type of the elements.
     */
    template<class T>
    Vector<T>::~Vector()
    {
        delete[] m_data;
    }

    /**
     * Copy assignment.
     *
     * @tparam T The type of the elements.
     * @param other Container to be copied.
     * @return Copied container.
     */
    template<class T>
    Vector<T>& Vector<T>::operator=(const Vector<T>& other)
    {
        // Self-assignment
        if (this == &other) { return *this; }

        // Memory reallocation
        if (other.m_size > m_capacity)
        {
            reserve(other.m_size);
        }

        // Copy assignment
        m_size = other.m_size;

        for (size_t i = 0; i < other.m_size; i++)
        {
            m_data[i] = other.m_data[i];
        }

        return *this;
    }

    /**
     * Increase the capacity of the container (the total number of
     * elements that the vector can hold without requiring reallocation)
     * to a value that's greater or equal to _capacity_.
     *
     * @tparam T The type of the elements.
     * @param capacity	New capacity of the container, in number of
     * elements.
     */
    template<class T>
    void Vector<T>::reserve(size_t capacity)
    {
        // This capacity is already sufficient
        if (capacity <= m_capacity) { return; }

        size_t new_capacity = (capacity + 15) & 0xfffffff0;

        T* tmp = new T[capacity];

        for (size_t i = 0; i < m_size; i++)
        {
            tmp[i] = m_data[i];
        }

        for (size_t i = m_size; i < capacity; i++)
        {
            tmp[i] = T();
        }

        delete[] m_data;

        m_data = tmp;
        m_capacity = capacity;
    }

    /**
     * Requests the removal of unused capacity.
     *
     * @tparam T The type of the elements.
     */
    template<class T>
    void Vector<T>::shrink_to_fit()
    {
        // Capacity is already minimal
        if (m_size == m_capacity) { return; }

        T* tmp = new T[m_size];

        for (size_t i = 0; i < m_size; i++)
        {
            tmp[i] = m_data[i];
        }

        delete[] m_data;

        m_data = tmp;
        m_capacity = m_size;
    }

    /**
     * Checks whether the container is empty.
     *
     * @tparam T The type of the elements.
     * @return True if the container is empty, false otherwise.
     */
    template<class T>
    bool Vector<T>::empty() const
    {
        return (m_size == 0);
    }

    /**
     * Returns the number of elements in the container.
     *
     * @tparam T The type of the elements.
     * @return The number of elements.
     */
    template<class T>
    size_t Vector<T>::size() const
    {
        return m_size;
    }

    /**
     * Returns the number of elements that the container has currently
     * allocated space for.
     *
     * @tparam T The type of the elements.
     * @return The number of elements that can be held in currently
     * allocated storage.
     */
    template<class T>
    size_t Vector<T>::capacity()
    {
        return m_capacity;
    }

    /**
     * Access specified element with bounds checking.
     *
     * @tparam T The type of the elements.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    template<class T>
    T& Vector<T>::at(size_t pos)
    {
        if (pos >= m_size) { throw out_of_range(); }
        return m_data[pos];
    }

    /**
     * Access specified element with bounds checking.
     *
     * @tparam T The type of the elements.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    template<class T>
    const T& Vector<T>::at(size_t pos) const
    {
        if (pos >= m_size) { throw out_of_range(); }
        return m_data[pos];
    }

    /**
     * Access specified element.
     *
     * @tparam T The type of the elements.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    template<class T>
    T& Vector<T>::operator[](size_t pos)
    {
        return m_data[pos % m_size];
    }

    /**
     * Access specified element.
     *
     * @tparam T The type of the elements.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    template<class T>
    const T& Vector<T>::operator[](size_t pos) const
    {
        return m_data[pos % m_size];
    }

    /**
     * Returns a reference to the first element in the container.
     *
     * @tparam T The type of the elements.
     * @return Reference to the first element.
     */
    template<class T>
    T& Vector<T>::front()
    {
        return m_data[0];
    }

    /**
     * Returns a reference to the first element in the container.
     *
     * @tparam T The type of the elements.
     * @return Reference to the first element.
     */
    template<class T>
    const T& Vector<T>::front() const
    {
        return m_data[0];
    }

    /**
     * Returns a reference to the last element in the container.
     *
     * @tparam T The type of the elements.
     * @return Reference to the last element.
     */
    template<class T>
    T& Vector<T>::back()
    {
        return m_data[m_size - 1];
    }

    /**
     * Returns a reference to the last element in the container.
     *
     * @tparam T The type of the elements.
     * @return Reference to the last element.
     */
    template<class T>
    const T& Vector<T>::back() const
    {
        return m_data[m_size - 1];
    }

    /**
     * Direct access to the underlying array serving as element storage.
     *
     * @tparam T The type of the elements.
     * @return Pointer to the underlying element storage. For non-empty
     * containers, the returned pointer compares equal to the address of
     * the first element.
     */
    template<class T>
    T* Vector<T>::data()
    {
        return m_data;
    }

    /**
     * Direct access to the underlying array serving as element storage.
     *
     * @tparam T The type of the elements.
     * @return Pointer to the underlying element storage. For non-empty
     * containers, the returned pointer compares equal to the address of
     * the first element.
     */
    template<class T>
    const T* Vector<T>::data() const
    {
        return m_data;
    }

    /**
     * Erases all elements from the container. After this call, size()
     * returns zero.
     *
     * @tparam T The type of the elements.
     */
    template<class T>
    void Vector<T>::clear()
    {
        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i] = T();
        }

        m_size = 0;
    }

    /**
     * Appends the given element value to the end of the container.
     *
     * @tparam T The type of the elements.
     * @param value Value of the element to append.
     */
    template<class T>
    void Vector<T>::push_back(T value)
    {
        if (m_capacity == 0) { reserve(16); }
        else if (m_size == m_capacity) { reserve(2 * m_capacity); }

        m_data[m_size] = value;
        m_size++;
    }

    /**
     * Removes the last element of the container.
     *
     * @tparam T The type of the elements.
     */
    template<class T>
    void Vector<T>::pop_back()
    {
        // TODO: Exception
        if (m_size == 0) { throw; }

        m_size--;
    }

    /**
     * Swaps two elements in the container.
     *
     * @tparam T The type of the elements.
     * @param pos1 Position of the first element to swap.
     * @param pos2 Position of the second element to swap.
     */
    template<class T>
    void Vector<T>::swap(size_t pos1, size_t pos2)
    {
        T tmp = m_data[pos1];
        m_data[pos1] = m_data[pos2];
        m_data[pos2] = tmp;
    }
}

#endif /* EMBLATE_VECTOR_H */
