#include "src/Internal/Algorithm/Math.h"
#include <gtest/gtest.h>
#include <cmath>

using Emblate::abs;
using Emblate::floor;
using Emblate::ceil;
using Emblate::map;

TEST(MathTest, AbsReturnTypeInt)
{
    int x = 0;

    EXPECT_EQ(typeid(int), typeid(abs(x)));
}

TEST(MathTest, AbsPositiveInt)
{
    int x = 1;
    int expected = 1;

    EXPECT_EQ(expected, abs(x));
}

TEST(MathTest, AbsNegativeInt)
{
    int x = -1;
    int expected = 1;

    EXPECT_EQ(expected, abs(x));
}

TEST(MathTest, AbsPositiveZeroInt)
{
    int x = 0;
    int expected = 0;

    EXPECT_EQ(expected, abs(x));
}

TEST(MathTest, AbsNegativeZeroInt)
{
    int x = -0;
    int expected = 0;

    EXPECT_EQ(expected, abs(x));
}

TEST(MathTest, AbsReturnTypeFloat)
{
    float x = 0.0f;

    EXPECT_EQ(typeid(float), typeid(abs(x)));
}

TEST(MathTest, AbsPositiveFloat)
{
    float x = 1.0f;
    float expected = 1.0f;

    EXPECT_FLOAT_EQ(expected, abs(x));
}

TEST(MathTest, AbsNegativeFloat)
{
    float x = -1.0f;
    float expected = 1.0f;

    EXPECT_FLOAT_EQ(expected, abs(x));
}

TEST(MathTest, AbsPositiveZeroFloat)
{
    float x = 0.0f;
    float expected = 0.0f;

    EXPECT_FLOAT_EQ(expected, abs(x));
}

TEST(MathTest, AbsNegativeZeroFloat)
{
    float x = -0.0f;
    float expected = 0.0f;

    EXPECT_FLOAT_EQ(expected, abs(x));
}

TEST(MathTest, AbsPositiveMaxFloat)
{
    float x = FLT_MAX;
    float expected = FLT_MAX;

    EXPECT_FLOAT_EQ(expected, abs(x));
}

TEST(MathTest, AbsNegativeMaxFloat)
{
    float x = -FLT_MAX;
    float expected = FLT_MAX;

    EXPECT_FLOAT_EQ(expected, abs(x));
}

TEST(MathTest, FloorReturnTypeInt)
{
    int x = 0;

    EXPECT_EQ(typeid(int), typeid(floor(x)));
}

TEST(MathTest, FloorPositiveInt)
{
    int x = 1;
    int expected = 1;

    EXPECT_EQ(expected, floor(x));
}

TEST(MathTest, FloorNegativeInt)
{
    int x = -1;
    int expected = -1;

    EXPECT_EQ(expected, floor(x));
}

TEST(MathTest, FloorPositiveZeroInt)
{
    int x = 0;
    int expected = 0;

    EXPECT_EQ(expected, floor(x));
}

TEST(MathTest, FloorNegativeZeroInt)
{
    int x = -0;
    int expected = -0;

    EXPECT_EQ(expected, floor(x));
}

TEST(MathTest, FloorReturnTypeFloat)
{
    float x = 0;

    EXPECT_EQ(typeid(float), typeid(floor(x)));
}

TEST(MathTest, FloorPositiveFloat)
{
    float x = 1.9f;
    float expected = 1.0f;

    EXPECT_FLOAT_EQ(expected, floor(x));
}

TEST(MathTest, FloorNegativeFloat)
{
    float x = -0.1f;
    float expected = -1.0f;

    EXPECT_FLOAT_EQ(expected, floor(x));
}

TEST(MathTest, FloorPositiveZeroFloat)
{
    float x = 0.0f;
    float expected = 0.0f;

    EXPECT_FLOAT_EQ(expected, floor(x));
}

TEST(MathTest, FloorNegativeZeroFloat)
{
    float x = -0.0f;
    float expected = -0.0f;

    EXPECT_FLOAT_EQ(expected, floor(x));
}

TEST(MathTest, FloorPositiveMaxFloat)
{
    float x = FLT_MAX;
    float expected = std::floor(x);

    EXPECT_FLOAT_EQ(expected, floor(x));
}

TEST(MathTest, FloorNegativeMaxFloat)
{
    float x = -FLT_MAX;
    float expected = std::floor(x);

    EXPECT_FLOAT_EQ(expected, floor(x));
}

TEST(MathTest, CeilReturnTypeInt)
{
    int x = 0;

    EXPECT_EQ(typeid(int), typeid(ceil(x)));
}

TEST(MathTest, CeilPositiveInt)
{
    int x = 1;
    int expected = 1;

    EXPECT_EQ(expected, ceil(x));
}

TEST(MathTest, CeilNegativeInt)
{
    int x = -1;
    int expected = -1;

    EXPECT_EQ(expected, ceil(x));
}

TEST(MathTest, CeilPositiveZeroInt)
{
    int x = 0;
    int expected = 0;

    EXPECT_EQ(expected, ceil(x));
}

TEST(MathTest, CeilNegativeZeroInt)
{
    int x = -0;
    int expected = -0;

    EXPECT_EQ(expected, ceil(x));
}

TEST(MathTest, CeilReturnTypeFloat)
{
    float x = 0;

    EXPECT_EQ(typeid(float), typeid(ceil(x)));
}

TEST(MathTest, CeilPositiveFloat)
{
    float x = 0.1f;
    float expected = 1.0f;

    EXPECT_FLOAT_EQ(expected, ceil(x));
}

TEST(MathTest, CeilNegativeFloat)
{
    float x = -1.9f;
    float expected = -1.0f;

    EXPECT_FLOAT_EQ(expected, ceil(x));
}

TEST(MathTest, CeilPositiveZeroFloat)
{
    float x = 0.0f;
    float expected = 0.0f;

    EXPECT_FLOAT_EQ(expected, ceil(x));
}

TEST(MathTest, CeilNegativeZeroFloat)
{
    float x = -0.0f;
    float expected = -0.0f;

    EXPECT_FLOAT_EQ(expected, ceil(x));
}

TEST(MathTest, CeilPositiveMaxFloat)
{
    float x = FLT_MAX;
    float expected = std::ceil(x);

    EXPECT_FLOAT_EQ(expected, ceil(x));
}

TEST(MathTest, CeilNegativeMaxFloat)
{
    float x = -FLT_MAX;
    float expected = std::ceil(x);

    EXPECT_FLOAT_EQ(expected, ceil(x));
}

TEST(MathTest, MapReturnTypeInt)
{
    EXPECT_EQ(typeid(int), typeid(map<int>(5, 0, 10, 0, 100)));
}

TEST(MathTest, MapValuesInt)
{
    EXPECT_EQ(50, map<int>(5, 0, 10, 0, 100));
    EXPECT_EQ(50, map<int>(0, -10, 10, 0, 100));
    EXPECT_EQ(25, map<int>(-5, -10, 10, 0, 100));
}

TEST(MathTest, MapReturnTypeFloat)
{
    EXPECT_EQ(typeid(float),
              typeid(map<float>(5.0f, 0.0f, 10.0f, 0.0f, 100.0f)));
}

TEST(MathTest, MapValuesFloat)
{
    EXPECT_FLOAT_EQ(50, map<float>(5.0f, 0.0f, 10.0f, 0.0f, 100.0f));
    EXPECT_FLOAT_EQ(50, map<float>(0.0f, -10.0f, 10.0f, 0.0f, 100.0f));
    EXPECT_FLOAT_EQ(25, map<float>(-5.0f, -10.0f, 10.0f, 0.0f, 100.0f));
}
