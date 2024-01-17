#ifndef EMBLATE_QUEUE_H
#define EMBLATE_QUEUE_H

#include "./Defines.h"
#include "./List.h"
#include "../Core/Exception.h"

namespace Emblate
{
    /**
     * Container adaptor that gives the functionality of a queue.
     * Specifically, a FIFO (first-in, first-out) data structure.
     *
     * @tparam T The type of the elements.
     * @tparam Container The type of the underlying container to use to store the elements. The container must provide the following functions with the usual semantics:
     *     - size()
     *     - clear()
     *     - back()
     *     - front()
     *     - push_back()
     *     - pop_front()
     */
    template<class T, class Container = List<T>>
    class Queue
    {
    public:
        Queue();
        Queue(size_t size, const T& value);
        Queue(const T* array, size_t size, bool reverse = false);
        Queue(Queue& other);

        ~Queue();

        Queue<T, Container>& operator=(const Queue<T, Container>& other);

        bool empty();

        size_t size();

        void clear();

        T* data();

        T& at(size_t pos);

        T& operator[](size_t pos);

        T& front();

        T& back();

        void push(T value);

        void pop();

        void slide(T value);

        void slide_limited(T value, size_t maxsize);

    private:
        Container m_data;
    };

    /**
     * Default constructor. Constructs an empty container.
     *
     * @tparam T The type of the elements.
     */
    template<class T, class Container>
    Queue<T, Container>::Queue()
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
    Queue<T, Container>::Queue(size_t size, const T& value)
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
    Queue<T, Container>::Queue(const T* array, size_t size, bool reverse)
            : m_data(array, size, reverse) {}

    /**
     * Copy constructor. Constructs the container with the copy of the
     * contents of other.
     *
     * @tparam T The type of the elements.
     * @param other Container to be copied.
     */
    template<class T, class Container>
    Queue<T, Container>::Queue(Queue<T, Container>& other)
            : m_data(other.m_data) {}

    /**
     * Destructs the container object.
     *
     * @tparam T The type of the elements.
     */
    template<class T, class Container>
    Queue<T, Container>::~Queue()
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
    Queue<T, Container>& Queue<T, Container>::operator=(const Queue<T, Container>& other)
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
    bool Queue<T, Container>::empty()
    {
        return size() == 0;
    }

    /**
     * Returns the number of elements in the container.
     *
     * @tparam T The type of the elements.
     * @return The number of elements.
     */
    template<class T, class Container>
    size_t Queue<T, Container>::size()
    {
        return m_data.size();
    }

    /**
     * Returns a reference to the underlying container serving as
     * element storage.
     *
     * @tparam T The type of the elements.
     * @return Reference to the underlying container.
     */
    template<class T, class Container>
    T* Queue<T, Container>::data()
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
    void Queue<T, Container>::clear()
    {
        m_data.clear();
    }

    /**
     * Access specified element with bounds checking.
     *
     * @tparam T The type of the elements.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    template<class T, class Container>
    T& Queue<T, Container>::at(size_t pos)
    {
        if (pos >= size()) { throw out_of_range(); }
        return m_data[pos];
    }

    /**
     * Access specified element.
     *
     * @tparam T The type of the elements.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    template<class T, class Container>
    T& Queue<T, Container>::operator[](size_t pos)
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
    T& Queue<T, Container>::front()
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
    T& Queue<T, Container>::back()
    {
        return m_data.back();
    }

    /**
     * Prepends the given element value to the beginning of the
     * container.
     *
     * @tparam T The type of the elements.
     * @param value Value of the element to prepend.
     */
    template<class T, class Container>
    void Queue<T, Container>::push(T value)
    {
        m_data.push_back(value);
    }

    /**
     * Removes the last element of the container.
     *
     * @tparam T The type of the elements.
     */
    template<class T, class Container>
    void Queue<T, Container>::pop()
    {
        m_data.pop_front();
    }

    /**
     * Simultaneously push and pop an element.
     *
     * @tparam T The type of the elements.
     * @param value Value of the element to push.
     */
    template<class T, class Container>
    void Queue<T, Container>::slide(T value)
    {
        slide_limited(value, 1);
    }

    /**
     * Simultaneously push and pop an element if the size of the
     * container is greater then _maxsize_.
     *
     * @tparam T The type of the elements.
     * @param value Value of the element to push.
     * @param maxsize Maximum size allowed for the Queue.
     */
    template<class T, class Container>
    void Queue<T, Container>::slide_limited(T value, size_t maxsize)
    {
        if (size() >= maxsize) { pop(); }

        push(value);
    }
}

#endif /* EMBLATE_QUEUE_H */
