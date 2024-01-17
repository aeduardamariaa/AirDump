#include "src/Internal/Container/Stack.h"
#include "gtest/gtest.h"

using Emblate::Stack;

TEST(StackTest, DefaultConstructor)
{
    Stack<int> stack;

    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, ValueConstructor)
{
    Stack<int> stack(5, 2);

    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 5);
    for (size_t i = 0; i < 5; i++)
    {
        EXPECT_EQ(stack.at(i), 2);
    }
}

TEST(StackTest, ArrayConstructor)
{
    int array[3] = { 1, 2, 3 };
    Stack<int> stack(array, 3);

    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 3);
    for (size_t i = 0; i < 3; i++)
    {
        EXPECT_EQ(stack.at(i), array[i]);
    }
}

TEST(StackTest, CopyConstructor)
{
    Stack<int> stack1(5, 2);
    Stack<int> stack2(stack1);

    EXPECT_FALSE(stack2.empty());
    EXPECT_EQ(stack2.size(), 5);
    for (size_t i = 0; i < 5; i++)
    {
        EXPECT_EQ(stack2.at(i), 2);
    }
}

TEST(StackTest, AssignmentOperator)
{
    int array[] = { 1, 2, 3, 4, 5 };
    Stack<int> original_stack(array, 5);
    Stack<int> assigned_stack(3, 7);
    assigned_stack = original_stack;

    EXPECT_EQ(assigned_stack.size(), 5);
    for (size_t i = 0; i < 5; ++i)
    {
        EXPECT_EQ(original_stack.at(i), assigned_stack.at(i));
    }
}

TEST(StackTest, StackOperations)
{
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(stack.back(), 3);
    EXPECT_EQ(stack.front(), 1);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 3);

    stack.pop();

    EXPECT_EQ(stack.back(), 2);
    EXPECT_EQ(stack.size(), 2);

    stack.clear();

    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}
