#include "src/Internal/Container/Queue.h"
#include <gtest/gtest.h>

using Emblate::Queue;

TEST(QueueTest, DefaultConstructor)
{
    Queue<int> queue;

    EXPECT_TRUE(queue.empty());
}

TEST(QueueTest, ValueConstructor)
{
    Queue<int> queue(5, 10);

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 5);
    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 10);
}

TEST(QueueTest, ArrayConstructor)
{
    int array[] = { 1, 2, 3, 4, 5 };
    Queue<int> queue(array, 5);

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 5);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 5);
}

TEST(QueueTest, CopyConstructor)
{
    int array[] = { 1, 2, 3, 4, 5 };
    Queue<int> original_queue(array, 5);
    Queue<int> copied_queue(original_queue);

    EXPECT_EQ(copied_queue.size(), 5);
    for (size_t i = 0; i < 5; i++)
    {
        EXPECT_EQ(original_queue.at(i), copied_queue.at(i));
    }
}

TEST(QueueTest, AssignmentOperator)
{
    int array[] = { 1, 2, 3, 4, 5 };
    Queue<int> original_queue(array, 5);
    Queue<int> assigned_queue(3, 7);
    assigned_queue = original_queue;

    EXPECT_EQ(assigned_queue.size(), 5);
    for (size_t i = 0; i < 5; ++i)
    {
        EXPECT_EQ(original_queue.at(i), assigned_queue.at(i));
    }
}

TEST(QueueTest, PushPop)
{
    Queue<int> queue;

    for (int i = 0; i < 5; i++)
    {
        queue.push(i);
    }

    EXPECT_EQ(queue.size(), 5);
    for (size_t i = 0; i < 5; i++)
    {
        EXPECT_EQ(queue.front(), i);
        EXPECT_EQ(queue.back(), 4);
        queue.pop();
    }
}

TEST(QueueTest, Slide)
{
    int array[] = { 1, 2, 3, 4, 5 };
    Queue<int> queue(array, 5);
    queue.slide(6);

    EXPECT_EQ(queue.size(), 5);
    EXPECT_EQ(queue.back(), 6);
    for (size_t i = 0; i < 5; i++)
    {
        EXPECT_EQ(queue.at(i), i + 2);
    }

}

TEST(QueueTest, SlideLimited)
{
    int array[] = { 1, 2, 3, 4, 5 };
    Queue<int> queue(array, 5);
    queue.slide_limited(6, 5);

    EXPECT_EQ(queue.size(), 5);
    EXPECT_EQ(queue.back(), 6);
    for (size_t i = 0; i < 5; i++)
    {
        EXPECT_EQ(queue.at(i), i + 2);
    }

    queue.slide_limited(7, 6);

    EXPECT_EQ(queue.size(), 6);
    EXPECT_EQ(queue.back(), 7);
    for (size_t i = 0; i < 6; i++)
    {
        EXPECT_EQ(queue.at(i), i + 2);
    }
}
