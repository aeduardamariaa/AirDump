#ifndef EMBLATE_INTERPOLATE_H
#define EMBLATE_INTERPOLATE_H

#include "./Search.h"
#include "./Sort.h"
#include "../Core/Exception.h"
#include "../Container/Defines.h"
#include "../Container/Vector.h"

namespace Emblate
{
    /**
     * One-dimensional interpolation methods over a data grid.
     *
     * @tparam T The type of the elements.
     */
    template<typename T>
    class Interp1d
    {
    public:
        Interp1d(Vector<T> xp, Vector<T> yp,
                 bool check_bounds = false,
                 bool assume_sorted = false);

        T linear(T x);

    private:
        Vector<T> m_x;
        Vector<T> m_y;
        size_t m_size;
        bool m_check_bounds;
        bool m_assume_sorted;

    };

    /**
     * Constructs a grid data with x- and y-coordinates.
     *
     * @tparam T The type of the elements.
     * @param xp The x-coordinates of the data points, must be sorted if
     * _assume_sorted_ is True. Otherwise, xp is internally sorted.
     * @param yp The y-coordinates of the data points, same length as xp.
     * @param check_bounds Check _x_ bounds to interpolate.
     * @param assume_sorted Assume the _x_ array is sorted.
     */
    template<typename T>
    Interp1d<T>::Interp1d(Vector<T> xp, Vector<T> yp,
                          bool check_bounds,
                          bool assume_sorted)
            : m_x(xp), m_y(yp),
              m_check_bounds(check_bounds),
              m_assume_sorted(assume_sorted)
    {
        if (m_x.size() != m_y.size()) { throw invalid_argument(); }
        m_size = m_x.size();

        // TODO: Implement sorting algorithms
        if (!m_assume_sorted)
        {
            throw not_implemented();
        }
    }

    /**
     * Linear interpolation.
     *
     * @tparam T The type of the elements.
     * @param x The x-coordinates at which to evaluate the interpolated values.
     * @return Interpolated value.
     */
    template<typename T>
    T Interp1d<T>::linear(T x)
    {
        if ((m_check_bounds) && (x < m_x.front() || x > m_x.back())) { throw out_of_range(); }

        size_t i = binarySearch<T>(m_x, x, 0, m_size - 1);
        if ((i == m_size - 1) || (i != 0 && x < m_x[i])) { i--; }

        T dydx = ((m_y[i + 1] - m_y[i]) / (m_x[i + 1] - m_x[i]));
        return m_y[i] + dydx * (x - m_x[i]);
    }
}

#endif /* EMBLATE_INTERPOLATE_H */
