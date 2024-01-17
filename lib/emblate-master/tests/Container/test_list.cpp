#include "src/Internal/Container/List.h"
#include <gtest/gtest.h>

using Emblate::List;

TEST(ListTest, DefaultConstructor)
{
    List<int> list;

    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
}

TEST(ListTest, ValueConstructor)
{
    List<int> list(5, 1);

    EXPECT_EQ(list.size(), 5);
    EXPECT_FALSE(list.empty());
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(list.at(i), 1);
    }
}

TEST(ListTest, ArrayConstructor)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    List<int> list(arr, 5);

    EXPECT_EQ(list.size(), 5);
    EXPECT_FALSE(list.empty());
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(list.at(i), arr[i]);
    }
}

TEST(ListTest, CopyConstructor)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    List<int> list1(arr, 5);
    List<int> list2(list1);

    EXPECT_EQ(list2.size(), 5);
    EXPECT_FALSE(list2.empty());
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(list2.at(i), list1.at(i));
    }
}

TEST(ListTest, AssignmentOperator)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    List<int> list1(arr, 5);
    List<int> list2 = list1;

    EXPECT_EQ(list2.size(), 5);
    EXPECT_FALSE(list2.empty());
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(list2.at(i), list1.at(i));
    }
}

TEST(ListTest, Indexing)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    List<int> list1(arr, 5);

    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(list1[i], arr[i]);
    }
}

TEST(ListTest, Clear)
{
    List<int> list(5, 1);
    list.clear();

    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
}

TEST(ListTest, PushBackAndFrontPopBackAndFront)
{
    List<int> list;

    for (int i = 0; i < 5; i++)
    {
        list.push_back(i);
        list.push_front(5 - i - 1);
    }

    EXPECT_EQ(list.size(), 10);
    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(list.front(), i);
        list.pop_front();
        EXPECT_EQ(list.back(), 5 - i - 1);
        list.pop_back();
    }
}
