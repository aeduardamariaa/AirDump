#include "src/Internal/Algorithm/Search.h"
#include "src/Container"
#include <gtest/gtest.h>

using Emblate::Vector;
using Emblate::binarySearch;
using Emblate::invalid_argument;

int sortedArrayInt[] = { -5, -4, -3, -2, -1, 0, 2, 3, 4, 5 };
Emblate::Vector<int> sortedVectorInt(sortedArrayInt, 10);

TEST(SearchTest, BinarySearchFoundElementInt)
{
    auto result = binarySearch(sortedVectorInt, 0,
                               0, sortedVectorInt.size() - 1);
    size_t expected = 5;

    EXPECT_EQ(result, expected);
}

TEST(SearchTest, BinarySearchLowerBoundInt)
{
    auto result = binarySearch(sortedVectorInt, -5,
                               0, sortedVectorInt.size() - 1);
    size_t expected = 0;

    EXPECT_EQ(result, expected);
}

TEST(SearchTest, BinarySearchUpperBoundInt)
{
    auto result = binarySearch(sortedVectorInt, 5,
                               0, sortedVectorInt.size() - 1);
    size_t expected = 9;

    EXPECT_EQ(result, expected);
}

TEST(SearchTest, BinarySearchElementNotInArrayLowerInt)
{
    auto result = binarySearch(sortedVectorInt, -6,
                               0, sortedVectorInt.size() - 1);
    size_t expected = 0;

    EXPECT_EQ(result, expected);
}

TEST(SearchTest, BinarySearchElementNotInArrayUpperInt)
{
    auto result = binarySearch(sortedVectorInt, 6,
                               0, sortedVectorInt.size() - 1);
    size_t expected = 9;

    EXPECT_EQ(result, expected);
}

TEST(SearchTest, BinarySearchElementNotInArrayMiddleInt)
{
    auto result = binarySearch(sortedVectorInt, 1,
                               0, sortedVectorInt.size() - 1);
    size_t expected = 5;

    EXPECT_EQ(result, expected);
}

TEST(SearchTest, BinarySearchEmptyArrayInt)
{
    Vector<int> emptyVector;

    EXPECT_THROW(binarySearch(emptyVector, 0, 0, emptyVector.size() - 1),
                 invalid_argument);
}

float sortedArrayFloat[] = { -5.5f, -4.4f, -3.3f, -2.2f, -1.1f, 0.0f, 2.2f,
                             3.3f, 4.4f, 5.5f };
Emblate::Vector<float> sortedVectorFloat(sortedArrayFloat, 10);

TEST(SearchTest, BinarySearchFoundElementFloat)
{
    auto result = binarySearch(sortedVectorFloat, 0.0f,
                               0, sortedVectorFloat.size() - 1);
    size_t expected = 5;

    EXPECT_EQ(result, expected);
}

TEST(SearchTest, BinarySearchLowerBoundFloat)
{
    auto result = binarySearch(sortedVectorFloat, -5.5f,
                               0, sortedVectorFloat.size() - 1);
    size_t expected = 0;

    EXPECT_EQ(result, expected);
}

TEST(SearchTest, BinarySearchUpperBoundFloat)
{
    auto result = binarySearch(sortedVectorFloat, 5.5f,
                               0, sortedVectorFloat.size() - 1);
    size_t expected = 9;

    EXPECT_EQ(result, expected);
}

TEST(SearchTest, BinarySearchElementNotInArrayLowerFloat)
{
    auto result = binarySearch(sortedVectorFloat, -6.6f,
                               0, sortedVectorFloat.size() - 1);
    size_t expected = 0;

    EXPECT_EQ(result, expected);
}

TEST(SearchTest, BinarySearchElementNotInArrayUpperFloat)
{
    auto result = binarySearch(sortedVectorFloat, 6.6f,
                               0, sortedVectorFloat.size() - 1);
    size_t expected = 9;

    EXPECT_EQ(result, expected);
}

TEST(SearchTest, BinarySearchElementNotInArrayMiddleFloat)
{
    auto result = binarySearch(sortedVectorFloat, 1.1f,
                               0, sortedVectorFloat.size() - 1);
    size_t expected = 5;

    EXPECT_EQ(result, expected);
}

TEST(SearchTest, BinarySearchEmptyArrayFloat)
{
    Vector<float> emptyVector;

    EXPECT_THROW(binarySearch(emptyVector, 0.0f, 0, emptyVector.size() - 1),
                 invalid_argument);
}
