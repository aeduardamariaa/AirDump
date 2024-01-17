#include "src/Internal/Algorithm/Interpolate.h"
#include "src/Container"
#include <gtest/gtest.h>

using Emblate::Vector;
using Emblate::Interp1d;
using Emblate::out_of_range;

TEST(InterpolateTest, ConstructorSorted)
{
    using Emblate::Vector;
    using Emblate::Interp1d;

    double xp_array[] = { 1.0, 2.0, 3.0, 4.0 };
    Vector<double> xp(xp_array, 4);

    double yp_array[] = { 10.0, 20.0, 30.0, 40.0 };
    Vector<double> yp(yp_array, 4);

    Interp1d<double> interp(xp, yp, false, true);
}

TEST(InterpolateTest, ConstructorUnsorted)
{
    double xp_array[] = { 4.0, 2.0, 3.0, 1.0 };
    Vector<double> xp(xp_array, 4);

    double yp_array[] = { 40.0, 20.0, 30.0, 10.0 };
    Vector<double> yp(yp_array, 4);

    Interp1d<double> interp(xp, yp, false, false);
}

TEST(InterpolateTest, LinearInterpolation)
{
    double xp_array[] = { 1.0, 2.0, 3.0, 4.0 };
    Vector<double> xp(xp_array, 4);

    double yp_array[] = { 10.0, 20.0, 30.0, 40.0 };
    Vector<double> yp(yp_array, 4);

    Interp1d<double> interp(xp, yp, false, true);

    EXPECT_DOUBLE_EQ(interp.linear(1.0), 10.0);
    EXPECT_DOUBLE_EQ(interp.linear(2.5), 25.0);
    EXPECT_DOUBLE_EQ(interp.linear(4.0), 40.0);
}

TEST(InterpolateTest, OutOfBoundsInterpolation)
{
    double xp_array[] = { 1.0, 2.0, 3.0, 4.0 };
    Vector<double> xp(xp_array, 4);

    double yp_array[] = { 10.0, 20.0, 30.0, 40.0 };
    Vector<double> yp(yp_array, 4);

    Interp1d<double> interp(xp, yp, true, true);

    EXPECT_THROW(interp.linear(0.5), out_of_range);
    EXPECT_THROW(interp.linear(5.0), out_of_range);
}
