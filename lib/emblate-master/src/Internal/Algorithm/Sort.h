#ifndef EMBLATE_SORT_H
#define EMBLATE_SORT_H

#include "./Math.h"
#include "./Utils.h"
#include "../Container/Vector.h"

namespace Emblate
{
    /**
     * In-place heapSort. It is implemented using bottom-up search.
     *
     * @tparam T The type of the elements.
     */
    template<typename T>
    class HeapSort
    {
    public:
        explicit HeapSort(Vector<T>& a);
        size_t iParent(size_t pos);
        size_t iLeftChild(size_t pos);
        size_t iRightChild(size_t pos);
        size_t leafSearch(size_t start, size_t end);
        void siftDown(size_t start, size_t end);
        void heapify();
        void sort();

    private:
        Vector<T>& m_a;
    };

    /**
     * Constructs a object to be sorted.
     *
     * @tparam T The type of the elements.
     * @param a Array to be sorted.
     */
    template<typename T>
    HeapSort<T>::HeapSort(Vector<T>& a)
            : m_a(a) {}

    /**
     * Get the index of the parent node of a heap.
     *
     * @tparam T The type of the elements.
     * @param pos Index of current node.
     * @return Index of the parent node.
     */
    template<typename T>
    inline size_t HeapSort<T>::iParent(size_t pos)
    {
        return floor((pos - 1) / 2);
    }

    /**
     * Get the index of the left child node of a heap.
     *
     * @tparam T The type of the elements.
     * @param pos Index of current node.
     * @return Index of the left child node.
     */
    template<typename T>
    inline size_t HeapSort<T>::iLeftChild(size_t pos)
    {
        return 2 * pos + 1;
    }

    /**
     * Gets the index of the right child node of a heap.
     *
     * @tparam T The type of the elements.
     * @param pos Index of current node.
     * @return Index of the right child node.
     */
    template<typename T>
    inline size_t HeapSort<T>::iRightChild(size_t pos)
    {
        return 2 * pos + 2;
    }

    /**
     * Gets the position where to insert _a[end]_.
     *
     * Finds the path of largest children to the leaf level of the tree
     * (as if it were inserting −∞) using only one comparison per level.
     * Then, from this leaf, it searches upward (using one comparison
     * per level) for the correct position in that path to insert a[end].
     *
     * @tparam T The type of the elements.
     * @param start Index of the node to start the search from.
     * @param end Index of the node to end the search.
     * @return Position in that path to insert _a[end]_.
     */
    template<typename T>
    inline size_t HeapSort<T>::leafSearch(size_t start, size_t end)
    {
        size_t j = start;
        while (iRightChild(j) <= end)
        {
            if (m_a[iRightChild(j)] > m_a[iLeftChild(j)])
            {
                j = iRightChild(j);
            }
            else
            {
                j = iLeftChild(j);
            }
        }

        if (iLeftChild(j) <= end) { j = iLeftChild(j); }

        return j;
    }

    /**
     * Sifts the new first element to its appropriate index in the heap.
     *
     * @tparam T The type of the elements.
     * @param start Index of the node to start the search from.
     * @param end Index of the node to end the search.
     */
    template<typename T>
    void HeapSort<T>::siftDown(size_t start, size_t end)
    {
        size_t j = leafSearch(start, end);

        while (m_a[start] > m_a[j]) { j = iParent(j); }

        T tmp = m_a[j];
        m_a[j] = m_a[start];
        while (j > start)
        {
            swap(m_a[iParent(j)], tmp);
            j = iParent(j);
        }
    }

    /**
     * Builds a heap from an array by  sifting downward to establish the
     * heap property in O(n) operations.
     *
     * @tparam T The type of the elements.
     */
    template<typename T>
    void HeapSort<T>::heapify()
    {
        for (size_t start = m_a.size(); start > 0; start--)
        {
            siftDown(start - 1, m_a.size() - 1);
        }
    }

    /**
     * Sort an array using the bottom-up heapSort algorithm.
     *
     * @tparam T The type of the elements.
     */
    template<typename T>
    void HeapSort<T>::sort()
    {
        heapify();

        for (size_t end = m_a.size() - 1; end > 0; end--)
        {
            m_a.swap(end, 0);
            siftDown(0, end - 1);
        }
    }
}

#endif /* EMBLATE_SORT_H */
