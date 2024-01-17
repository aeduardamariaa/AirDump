#ifndef EMBLATE_SEARCH_H
#define EMBLATE_SEARCH_H

#include "./Math.h"
#include "../Core/Exception.h"
#include "../Container/Defines.h"
#include "../Container/Vector.h"

namespace Emblate
{
    /**
     * Search through a sorted array. It is implemented as a binary
     * search algorithm.
     *
     * @tparam T The type of the elements.
     * @param arr Array to search in.
     * @param val Value to search for.
     * @param lower_index Lower limit index.
     * @param upper_index Upper limit index.
     * @return Position in the array where the value is equal to _t_.
     */
    template<typename T>
    size_t binarySearch(const Vector<T>& arr, T val,
                        size_t lower_index, size_t upper_index)
    {
        if (lower_index > upper_index)
        {
            throw out_of_range();
        }

        if (arr.size() == 0)
        {
            throw invalid_argument();
        }

        while (upper_index - lower_index > 1)
        {
            size_t mid_index = lower_index + (upper_index - lower_index) / 2;
            T mid = arr[mid_index];

            if (val == mid) { return mid_index; }
            if (val > mid) { lower_index = mid_index; }
            else { upper_index = mid_index; }
        }

        return abs(val - arr[upper_index]) >= abs(val - arr[lower_index])
               ? lower_index
               : upper_index;
    }
}

#endif /* EMBLATE_SEARCH_H */
