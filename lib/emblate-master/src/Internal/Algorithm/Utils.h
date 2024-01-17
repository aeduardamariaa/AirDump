#ifndef EMBLATE_UTILS_H
#define EMBLATE_UTILS_H

#include "../Container//Defines.h"

namespace Emblate
{
    /**
     * Swap two elements in-place.
     *
     * @tparam T The type of the elements.
     * @param elem1 First element to be swaped.
     * @param elem2 Second element to be swaped.
     */
    template<typename T>
    void swap(T& elem1, T& elem2)
    {
        elem1 += elem2;
        elem2 = elem1 - elem2;
        elem1 -= elem2;
    }

    /**
     * Compares two null-terminated byte strings lexicographically.
     *
     * @param str1 First null-terminated byte string to compare.
     * @param str2 Second null-terminated byte string to compare.
     * @return True if both strings are equal. False otherwise.
     */
    template<typename String = const char*>
    bool strCmp(String str1, String str2)
    {
        while (*str1 && (*str1 == *str2))
        {
            str1++;
            str2++;
        }

        return *(String)str1 == *(String)str2;
    }
}

#endif /* EMBLATE_UTILS_H */
