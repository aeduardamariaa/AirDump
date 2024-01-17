#ifndef EMBLATE_LIST_H
#define EMBLATE_LIST_H

#include "./Defines.h"
#include "../Core/Exception.h"

namespace Emblate
{
    /**
     * Node to a doubly-linked list.
     *
     * @tparam Elem The type of the elements.
     */
    template<class Elem>
    struct Node
    {
        /**
         * Costructor.
         *
         * @param value_ Value to assign to the node.
         * @param prev_ Previous node pointer.
         * @param next_ Next node pointer.
         */
        explicit Node(const Elem& value_ = Elem(), Node* prev_ = 0,
                      Node* next_ = 0)
                : prev(prev_), next(next_), value(value_) {}

        Node* prev;
        Node* next;
        Elem value;
    };

    /**
     *  Container that supports constant time insertion and removal of
     *  elements from anywhere in the container. Fast random access is
     *  not supported. It is implemented as a doubly-linked list.
     *
     * @tparam T The type of the elements.
     */
    template<class T>
    class List
    {
    public:
        List();
        List(size_t size, const T& value);
        List(const T* array, size_t size, bool reverse = false);
        List(const List<T>& other);

        ~List();

        List<T>& operator=(const List<T>& other);

        class iterator;

        /** Iterator to front (first) element.
         *
         * @return Iterator to front (first) element.
         */
        iterator begin()
        {
            return iterator(m_front_link->next);
        }

        /**
         * Iterator to back (last) element.
         *
         * @return Iterator to back (last) element.
         */
        iterator end()
        {
            return iterator(m_back_link->prev);
        }

        virtual bool empty();
        virtual size_t size();

        virtual T& at(size_t pos);
        virtual const T& at(size_t pos) const;

        T& operator[](size_t pos);
        const T& operator[](size_t pos) const;

        virtual T& front();
        virtual const T& front() const;

        virtual T& back();
        virtual const T& back() const;

        virtual void clear();

        virtual void push_front(T value);
        virtual void push_back(T value);

        void pop_front();
        void pop_back();

    private:
        Node<T>* m_front_link;
        Node<T>* m_back_link;
        size_t m_size;
    };

    /**
     * Default constructor. Constructs an empty container.
     *
     * @tparam T The type of the elements.
     */
    template<class T>
    List<T>::List()
            : m_front_link(new Node<T>(T(), 0, 0)),
              m_back_link(new Node<T>(T(), m_front_link, 0))
    {
        m_front_link->next = m_back_link;
        m_size = 0;
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
    List<T>::List(size_t size, const T& value)
            : m_front_link(new Node<T>(T(), 0, 0)),
              m_back_link(new Node<T>(T(), m_front_link, 0))
    {
        m_front_link->next = m_back_link;
        m_size = 0;

        for (size_t i = 0; i < size; i++)
        {
            push_back(value);
        }
    }

    /**
     * Constructs the container by copying the elements of a plain
     * C-style array.
     *
     * @tparam T The type of the elements.
     * @param array Plain C-style array.
     * @param size Size of the base array.
     * @param reverse Reverse the order in which the elements appear.
     */
    template<class T>
    List<T>::List(const T* array, size_t size, bool reverse)
            : m_front_link(new Node<T>(T(), 0, 0)),
              m_back_link(new Node<T>(T(), m_front_link, 0))
    {
        m_front_link->next = m_back_link;
        m_size = 0;

        // Keep conditional statements out of the loop for optimization
        if (reverse)
        {
            for (size_t i = 0; i < size; i++)
            {
                push_front(array[i]);
            }
        }
        else
        {
            for (size_t i = 0; i < size; i++)
            {
                push_back(array[i]);
            }
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
    List<T>::List(const List<T>& other)
            : m_front_link(new Node<T>(T(), 0, 0)),
              m_back_link(new Node<T>(T(), m_front_link, 0))
    {
        m_front_link->next = m_back_link;
        m_size = 0;

        for (auto* elem = other.m_front_link->next;
             elem != other.m_back_link;
             elem = elem->next)
        {
            push_back(elem->value);
        }
    }

    /**
     * Destructs the container object.
     *
     * @tparam T The type of the elements.
     */
    template<class T>
    List<T>::~List()
    {
        while (size() > 0) { pop_back(); }
    }

    /**
     * Copy assignment.
     *
     * @tparam T The type of the elements.
     * @param other Container to be copied.
     * @return Copied container.
     */
    template<class T>
    List<T>& List<T>::operator=(const List<T>& other)
    {
        // Self-assignment
        if (this == &other) return *this;

        // Copy assignment
        clear();

        for (auto* elem = other.m_front_link->next;
             elem != other.m_back_link;
             elem = elem->next)
        {
            push_back(elem->value);
        }

        return *this;
    }

    // TODO: Documentation
    template<class Elem>
    class List<Elem>::iterator
    {
    public:
        explicit iterator(Node<Elem>* p)
                : m_curr(p) {}

        iterator& operator++()
        {
            m_curr = m_curr->next;
            return *this;
        }

        iterator& operator--()
        {
            m_curr = m_curr->prev;
            return *this;
        }

        Elem& operator*()
        {
            return m_curr->value;
        }

        bool operator==(const iterator& link_) const
        {
            return m_curr == link_.m_curr;
        }

        bool operator!=(const iterator& link_) const
        {
            return m_curr != link_.m_curr;
        }

    private:
        Node<Elem>* m_curr;
    };

    /**
     * Checks whether the container is empty.
     *
     * @tparam T The type of the elements.
     * @return True if the container is empty, false otherwise.
     */
    template<class T>
    bool List<T>::empty()
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
    size_t List<T>::size()
    {
        return m_size;
    }

    /**
     * Access specified element with bounds checking.
     *
     * @tparam T The type of the elements.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    template<class T>
    T& List<T>::at(size_t pos)
    {
        if (pos >= m_size) { throw out_of_range(); }

        Node<T>* elem;

        if (pos < m_size / 2)
        {
            elem = m_front_link->next;
            for (size_t _ = 0; _ < pos; _++)
            {
                elem = elem->next;
            }
        }
        else
        {
            elem = m_back_link->prev;
            for (size_t _ = m_size - 1; _ > pos; _--)
            {
                elem = elem->prev;
            }
        }

        return elem->value;
    }

    /**
     * Access specified element with bounds checking.
     *
     * @tparam T The type of the elements.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    template<class T>
    const T& List<T>::at(size_t pos) const
    {
        if (pos >= m_size) { throw out_of_range(); }

        Node<T>* elem;

        if (pos < m_size / 2)
        {
            elem = m_front_link->next;
            for (size_t _ = 0; _ < pos; _++)
            {
                elem = elem->next;
            }
        }
        else
        {
            elem = m_back_link->prev;
            for (size_t _ = m_size - 1; _ > pos; _--)
            {
                elem = elem->prev;
            }
        }

        return elem->value;
    }

    /**
     * Access specified element.
     *
     * @tparam T The type of the elements.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    template<class T>
    T& List<T>::operator[](size_t pos)
    {
        size_t index = pos % static_cast<size_t>(m_size);

        if (index < 0) { index += m_size; }

        return at(index);
    }

    /**
     * Access specified element.
     *
     * @tparam T The type of the elements.
     * @param pos Position of the element to return.
     * @return Reference to the requested element.
     */
    template<class T>
    const T& List<T>::operator[](size_t pos) const
    {
        size_t index = pos % static_cast<size_t>(m_size);

        if (index < 0) { index += m_size; }

        return at(index);
    }

    /**
     * Returns a reference to the first element in the container.
     *
     * @tparam T The type of the elements.
     * @return Reference to the first element.
     */
    template<class T>
    T& List<T>::front()
    {
        if (m_size == 0) { throw out_of_range(); }
        return m_front_link->next->value;
    }

    /**
     * Returns a reference to the first element in the container.
     *
     * @tparam T The type of the elements.
     * @return Reference to the first element.
     */
    template<class T>
    const T& List<T>::front() const
    {
        if (m_size == 0) { throw out_of_range(); }
        return m_front_link->next->value;
    }

    /**
     * Returns a reference to the last element in the container.
     *
     * @tparam T The type of the elements.
     * @return Reference to the last element.
     */
    template<class T>
    T& List<T>::back()
    {
        if (m_size == 0) { throw out_of_range(); }
        return m_back_link->prev->value;
    }

    /**
     * Returns a reference to the last element in the container.
     *
     * @tparam T The type of the elements.
     * @return Reference to the last element.
     */
    template<class T>
    const T& List<T>::back() const
    {
        if (m_size == 0) { throw out_of_range(); }
        return m_back_link->prev->value;
    }

    /**
     * Erases all elements from the container. After this call, size() returns zero.
     *
     * @tparam T The type of the elements.
     */
    template<class T>
    void List<T>::clear()
    {
        while (size() > 0) { pop_back(); }
    }

    /**
     * Prepends the given element value to the beginning of the container.
     *
     * @tparam T The type of the elements.
     * @param value Value of the element to prepend.
     */
    template<class T>
    void List<T>::push_front(const T value)
    {
        auto* new_link = new Node<T>;
        new_link->value = value;
        new_link->prev = m_front_link;
        new_link->next = m_front_link->next;

        m_front_link->next->prev = new_link;
        m_front_link->next = new_link;

        m_size++;
    }

    /**
     * Appends the given element value to the end of the container.
     *
     * @tparam T The type of the elements.
     * @param value Value of the element to append.
     */
    template<class T>
    void List<T>::push_back(const T value)
    {
        Node<T>* newLink = new Node<T>;
        newLink->value = value;
        newLink->prev = m_back_link->prev;
        newLink->next = m_back_link;

        m_back_link->prev->next = newLink;
        m_back_link->prev = newLink;

        m_size++;
    }

    /**
     * Removes the first element of the container.
     *
     * @tparam T The type of the elements.
     */
    template<class T>
    void List<T>::pop_front()
    {
        if (empty()) { return; }

        Node<T>* tmp = m_front_link->next;
        tmp->next->prev = m_front_link;
        m_front_link->next = tmp->next;
        m_size--;

        delete tmp;
    }

    /**
     * Removes the last element of the container.
     *
     * @tparam T The type of the elements.
     */
    template<class T>
    void List<T>::pop_back()
    {
        if (empty()) { return; }

        Node<T>* tmp = m_back_link->prev;
        tmp->prev->next = m_back_link;
        m_back_link->prev = tmp->prev;
        m_size--;

        delete tmp;
    }
}

#endif /* EMBLATE_LIST_H */
