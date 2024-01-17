#include "src/Internal/Algorithm/Sort.h"
#include "src/Container"
#include <gtest/gtest.h>

using Emblate::Vector;
using Emblate::HeapSort;

// TODO: Test cases for float type
// TODO: Test cases for different containers
// TODO: Test cases for custom data types

TEST(HeapSortTest, SortPositives)
{
    int unsorted_array[] = { 5, 4, 3, 2, 1 };
    Vector<int> unsorted(unsorted_array, 5);

    HeapSort<int> sorter(unsorted);
    sorter.sort();

    int sorted_array[] = { 1, 2, 3, 4, 5 };
    Vector<int> sorted(sorted_array, 5);

    for (int i = 0; i < unsorted.size(); i++)
    {
        EXPECT_EQ(unsorted[i], sorted[i]);
    }
}

TEST(HeapSortTest, SortNegatives)
{
    int unsorted_array[] = { -1, -2, -3, -4, -5 };
    Vector<int> unsorted(unsorted_array, 5);

    HeapSort<int> sorter(unsorted);
    sorter.sort();

    int sorted_array[] = { -5, -4, -3, -2, -1 };
    Vector<int> sorted(sorted_array, 5);

    for (int i = 0; i < unsorted.size(); i++)
    {
        EXPECT_EQ(unsorted[i], sorted[i]);
    }
}

TEST(HeapSortTest, SortSigned)
{
    int unsorted_array[] = { 12, -23, 20, 0, -12 };
    Vector<int> unsorted(unsorted_array, 5);

    HeapSort<int> sorter(unsorted);
    sorter.sort();

    int sorted_array[] = { -23, -12, 0, 12, 20 };
    Vector<int> sorted(sorted_array, 5);

    for (int i = 0; i < unsorted.size(); i++)
    {
        EXPECT_EQ(unsorted[i], sorted[i]);
    }
}

TEST(HeapSortTest, SortZeroStart)
{
    int unsorted_array[] = { 0, 4, 3, 2, 1 };
    Vector<int> unsorted(unsorted_array, 5);

    HeapSort<int> sorter(unsorted);
    sorter.sort();

    int sorted_array[] = { 0, 1, 2, 3, 4 };
    Vector<int> sorted(sorted_array, 5);

    for (int i = 0; i < unsorted.size(); i++)
    {
        EXPECT_EQ(unsorted[i], sorted[i]);
    }
}

TEST(HeapSortTest, SortZeroEnd)
{
    int unsorted_array[] = { 4, 3, 2, 1, 0 };
    Vector<int> unsorted(unsorted_array, 5);

    HeapSort<int> sorter(unsorted);
    sorter.sort();

    int sorted_array[] = { 0, 1, 2, 3, 4 };
    Vector<int> sorted(sorted_array, 5);

    for (int i = 0; i < unsorted.size(); i++)
    {
        EXPECT_EQ(unsorted[i], sorted[i]);
    }
}

TEST(HeapSortTest, SortZeroAll)
{
    int unsorted_array[] = { 0, 0, 0, 0, 0 };
    Vector<int> unsorted(unsorted_array, 5);

    HeapSort<int> sorter(unsorted);
    sorter.sort();

    int sorted_array[] = { 0, 0, 0, 0, 0 };
    Vector<int> sorted(sorted_array, 5);

    for (int i = 0; i < unsorted.size(); i++)
    {
        EXPECT_EQ(unsorted[i], sorted[i]);
    }
}

TEST(HeapSortTest, SortOneElement)
{
    Vector<int> unsorted;
    unsorted.push_back(1);

    HeapSort<int> sorter(unsorted);
    sorter.sort();

    Vector<int> sorted;
    sorted.push_back(1);

    for (int i = 0; i < unsorted.size(); i++)
    {
        EXPECT_EQ(unsorted[i], sorted[i]);
    }
}
