#ifndef EMBLATE_MATH_H
#define EMBLATE_MATH_H

#include "../Container/Defines.h"

namespace Emblate
{
    /**
     * Computes the absolute value of the element.
     *
     * @tparam T The type of the elements.
     * @param val Value to compute the absolute value.
     * @return Absolute value of the element.
     */
    template<typename T>
    T abs(T val)
    {
        return val >= 0 ? val : -val;
    }

    /**
     * Computes the largest integer value not greater than _val_.
     *
     * @tparam T The type of the elements.
     * @param val Value to compute the absolute value.
     * @return Largest integer value not greater than _val_.
     */
    // TODO: Do not use type cast.
    template<typename T>
    inline T floor(T val)
    {
        auto aux = static_cast<int>(val);

        if ((val < 0) && (val - aux < 0))
        {
            return static_cast<T>(aux - 1);
        }

        return static_cast<T>(aux);
    }

    /**
     * Computes the least integer value not less than _val_.
     *
     * @tparam T The type of the elements.
     * @param val Value to compute the absolute value.
     * @return Least integer value not less than _val_.
     */
    template<typename T>
    inline T ceil(T val)
    {
        if (val - floor(val) > 0)
        {
            return floor(val + 1);
        }

        return floor(val);
    }

    /**
     * Re-maps a value from one range to another.
     *
     * @tparam T The type of the elements.
     * @param val The value to map.
     * @param from_low The lower bound of the value’s current range.
     * @param from_high The upper bound of the value’s current range.
     * @param to_low The lower bound of the value’s target range.
     * @param to_high The upper bound of the value’s target range.
     * @return
     */
    template<typename T>
    inline T map(T val, T from_low, T from_high, T to_low, T to_high)
    {
        return (val - from_low) * (to_high - to_low) / (from_high - from_low)
               + to_low;
    }
}

#endif /* EMBLATE_MATH_H */
