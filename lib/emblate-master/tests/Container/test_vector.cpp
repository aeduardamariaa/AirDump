#include "src/Internal/Container/Vector.h"
#include <gtest/gtest.h>

using Emblate::Vector;
using Emblate::out_of_range;

TEST(VectorTest, DefaultConstructor)
{
    Vector<int> vector;

    EXPECT_EQ(vector.size(), 0);
    EXPECT_EQ(vector.capacity(), 0);
    EXPECT_TRUE(vector.empty());
}

TEST(VectorTest, SizeInitializedConstructor)
{
    Vector<int> vector(5);

    EXPECT_EQ(vector.size(), 5);
    EXPECT_EQ(vector.capacity(), 5);
    EXPECT_FALSE(vector.empty());
    for (size_t i = 0; i < 5; i++)
    {
        EXPECT_EQ(vector.at(i), int());
    }
}

TEST(VectorTest, ValueInitializedConstructor)
{
    Vector<int> vector(5, 1);

    EXPECT_EQ(vector.size(), 5);
    EXPECT_EQ(vector.capacity(), 5);
    EXPECT_FALSE(vector.empty());
    for (size_t i = 0; i < 5; i++)
    {
        EXPECT_EQ(vector.at(i), 1);
    }
}

TEST(VectorTest, ArrayInitializedConstructor)
{
    int arr[5] = { 1, 2, 3, 4, 5 };
    Vector<int> vector(arr, 5);

    EXPECT_EQ(vector.size(), 5);
    EXPECT_EQ(vector.capacity(), 5);
    EXPECT_FALSE(vector.empty());
    for (size_t i = 0; i < 5; i++)
    {
        EXPECT_EQ(vector.at(i), arr[i]);
    }
}

TEST(VectorTest, CopyConstructor)
{
    Vector<int> vector1(5, 1);
    Vector<int> vector2(vector1);

    EXPECT_EQ(vector2.size(), 5);
    EXPECT_EQ(vector2.capacity(), 5);
    EXPECT_FALSE(vector2.empty());
    for (size_t i = 0; i < 5; i++)
    {
        EXPECT_EQ(vector2.at(i), vector1.at(i));
    }
}

TEST(VectorTest, AssignmentOperator)
{
    Vector<int> vector1(5, 1);
    Vector<int> vector2 = vector1;

    EXPECT_EQ(vector2.size(), 5);
    EXPECT_EQ(vector2.capacity(), 5);
    EXPECT_FALSE(vector2.empty());
    for (size_t i = 0; i < 5; i++)
    {
        EXPECT_EQ(vector2.at(i), vector1.at(i));
    }
}

TEST(VectorTest, At)
{
    Vector<int> vector;
    vector.push_back(1);
    vector.push_back(2);

    EXPECT_EQ(vector.at(0), 1);
    EXPECT_EQ(vector.at(1), 2);
    EXPECT_THROW(vector.at(2), out_of_range);
}

TEST(VectorTest, Indexing)
{
    Vector<int> vector;
    vector.push_back(1);
    vector.push_back(2);

    EXPECT_EQ(vector[0], 1);
    EXPECT_EQ(vector[1], 2);
    EXPECT_EQ(vector[2], 1);
}

TEST(VectorTest, Front)
{
    Vector<int> vector;
    vector.push_back(1);
    vector.push_back(2);

    EXPECT_EQ(vector.front(), 1);
}

TEST(VectorTest, Back)
{
    Vector<int> vector;
    vector.push_back(1);
    vector.push_back(2);

    EXPECT_EQ(vector.back(), 2);
}

TEST(VectorTest, Data)
{
    Vector<int> vector;
    vector.push_back(1);
    vector.push_back(2);

    EXPECT_EQ(vector.data()[0], 1);
    EXPECT_EQ(vector.data()[1], 2);
}

TEST(VectorTest, Clear)
{
    Vector<int> vector(5, 1);
    vector.clear();

    EXPECT_EQ(vector.size(), 0);
    EXPECT_TRUE(vector.empty());
}

TEST(ListTest, PushBackPopBack)
{
    Vector<int> vector;

    for (int i = 0; i < 5; i++)
    {
        vector.push_back(i);
    }

    EXPECT_EQ(vector.size(), 5);
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(vector.back(), 5 - i - 1);
        vector.pop_back();
    }
}

TEST(VectorTest, Swap)
{
    Vector<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);

    vector.swap(0, 2);

    EXPECT_EQ(vector.front(), 3);
    EXPECT_EQ(vector.back(), 1);
}
