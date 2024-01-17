#ifndef EMBLATE_STACK_H
#define EMBLATE_STACK_H

#include "./Defines.h"
#include "./List.h"
#include "../Core/Exception.h"

namespace Emblate
{
    /**
     * Container adaptor that gives the functionality of a stack.
     * Specifically, a LIFO (last-in, first-out) data structure.
     *
     * @tparam T The type of the elements.
     */
    template<class T, class Container = List<T>>
    class Stack
    {
    public:
        Stack();
        Stack(size_t size, const T& value);
        Stack(const T* array, size_t size, bool reverse = false);
        Stack(Stack& other);
        Stack(const Stack& other);

        ~Stack();

        Stack<T, Container>& operator=(const Stack<T, Container>& other);

        bool empty();
        size_t size();

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

        void push(T value);
        void pop();

    private:
        List<T> m_data;
    };

    /**
     * Default constructor. Construct an empty container.
     *
     * @tparam T The type of the elements.
     */
    template<class T, class Container>
    Stack<T, Container>::Stack()
            : m_data() {}

    /**
     * Constructs the container with given size _size_ filled with
     * _value_.
     *
     * @tparam T The type of the elements.
     * @param size Initial size.
     * @param value Initial value.
     */
    template<class T, class Container>
    Stack<T, Container>::Stack(size_t size, const T& value)
            : m_data(size, value) {}

    /**
     * Constructs the container by copying the elements of a plain
     * C-style array.
     *
     * @tparam T The type of the elements.
     * @param array Plain C-style array.
     * @param size Size of the base array.
     * @param reverse Reverse the order in which the elements appear.
     */
    template<class T, class Container>
    Stack<T, Container>::Stack(const T* array, size_t size, bool reverse)
            : m_data(array, size, reverse) {}

    /**
     * Copy constructor. Constructs the container with the copy of the
     * contents of other.
     *
     * @tparam T The type of the elements.
     * @param other Container to be copied.
     */
    template<class T, class Container>
    Stack<T, Container>::Stack(Stack<T, Container>& other)
            : m_data(other.m_data) {}

    /**
     * Copy constructor. Constructs the container with the copy of the
     * contents of other.
     *
     * @tparam T The type of the elements.
     * @param other Container to be copied.
     */
    template<class T, class Container>
    Stack<T, Container>::Stack(const Stack<T, Container>& other)
            : m_data(other.m_data) {}

    /**
     * Destructs the container object.
     *
     * @tparam T The type of the elements.
     */
    template<class T, class Container>
    Stack<T, Container>::~Stack()
    {
        m_data.~Container();
    }

    /**
     * Copy assignment.
     *
     * @tparam T The type of the elements.
     * @param other Container to be copied.
     * @return Copied container.
     */
    template<class T, class Container>
    Stack<T, Container>& Stack<T, Container>::operator=(const Stack<T, Container>& other)
    {
        // Self-assignment
        if (this == &other) return *this;

        // Copy assignment
        m_data = other.m_data;

        return *this;
    }

    /**
     * Checks whether the container is empty.
     *
     * @tparam T The type of the elements.
     * @return True if the container is empty, false otherwise.
     */
    template<class T, class Container>
    bool Stack<T, Container>::empty()
    {
        return m_data.empty();
    }

    /**
     * Returns the number of elements in the container.
     *
     * @tparam T The type of the elements.
     * @return The number of elements.
     */
    template<class T, class Container>
    size_t Stack<T, Container>::size()
    {
        return m_data.size();
    }

    /**
     * Access specified element with bounds checking.
     *
     * @tparam T The type of the elements.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    template<class T, class Container>
    T& Stack<T, Container>::at(size_t pos)
    {
        if (pos >= size()) { throw out_of_range(); }
        return m_data[pos];
    }

    /**
     * Access specified element with bounds checking.
     *
     * @tparam T The type of the elements.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    template<class T, class Container>
    const T& Stack<T, Container>::at(size_t pos) const
    {
        if (pos >= size()) { throw out_of_range(); }
        return m_data[pos];
    }

    /**
     * Access specified element with bounds checking.
     *
     * @tparam T The type of the elements.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    template<class T, class Container>
    T& Stack<T, Container>::operator[](size_t pos)
    {
        return m_data[pos];
    }

    /**
     * Access specified element with bounds checking.
     *
     * @tparam T The type of the elements.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    template<class T, class Container>
    const T& Stack<T, Container>::operator[](size_t pos) const
    {
        return m_data[pos];
    }

    /**
     * Returns a reference to the first element in the container.
     *
     * @tparam T The type of the elements.
     * @return Reference to the first element.
     */
    template<class T, class Container>
    T& Stack<T, Container>::front()
    {
        return m_data.front();
    }

    /**
     * Returns a reference to the first element in the container.
     *
     * @tparam T The type of the elements.
     * @return Reference to the first element.
     */
    template<class T, class Container>
    const T& Stack<T, Container>::front() const
    {
        return m_data.front();
    }

    /**
     * Returns a reference to the last element in the container.
     *
     * @tparam T The type of the elements.
     * @return Reference to the last element.
     */
    template<class T, class Container>
    T& Stack<T, Container>::back()
    {
        return m_data.back();
    }

    /**
     * Returns a reference to the last element in the container.
     *
     * @tparam T The type of the elements.
     * @return Reference to the last element.
     */
    template<class T, class Container>
    const T& Stack<T, Container>::back() const
    {
        return m_data.back();
    }

    /**
     * Returns a reference to the underlying container serving as
     * element storage.
     *
     * @tparam T The type of the elements.
     * @return Reference to the underlying container.
     */
    template<class T, class Container>
    T* Stack<T, Container>::data()
    {
        return m_data;
    }

    /**
     * Returns a reference to the underlying container serving as
     * element storage.
     *
     * @tparam T The type of the elements.
     * @return Reference to the underlying container.
     */
    template<class T, class Container>
    const T* Stack<T, Container>::data() const
    {
        return m_data;
    }

    /**
     * Erases all elements from the container. After this call, size()
     * returns zero.
     *
     * @tparam T The type of the elements.
     */
    template<class T, class Container>
    void Stack<T, Container>::clear()
    {
        m_data.clear();
    }

    /**
     * Appends the given element value to the end of the container.
     *
     * @tparam T The type of the elements.
     * @param value Value of the element to append.
     */
    template<class T, class Container>
    void Stack<T, Container>::push(T value)
    {
        m_data.push_back(value);
    }

    /**
     * Removes the last element of the container.
     *
     * @tparam T The type of the elements.
     */
    template<class T, class Container>
    void Stack<T, Container>::pop()
    {
        m_data.pop_back();
    }
}

#endif /* EMBLATE_STACK_H */
