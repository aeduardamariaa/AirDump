#include "src/Internal/Algorithm/Utils.h"
#include <gtest/gtest.h>

using Emblate::swap;
using Emblate::strCmp;

TEST(UtilsTest, SwapValuesInt)
{
    int a = 0;
    int b = 5;

    swap(a, b);

    EXPECT_EQ(a, 5);
    EXPECT_EQ(b, 0);
}

TEST(UtilsTest, SwapValuesFloat)
{
    float x = 0.0f;
    float y = 5.0f;

    swap(x, y);

    EXPECT_FLOAT_EQ(x, 5.0f);
    EXPECT_FLOAT_EQ(y, 0.0f);
}

TEST(UtilsTest, StrCmpEqualStrings)
{
    const char* str1 = "hello";
    const char* str2 = "hello";

    bool result = strCmp(str1, str2);

    EXPECT_TRUE(result);
}

TEST(UtilsTest, StrCmpDifferentStrings)
{
    const char* str1 = "hello";
    const char* str2 = "world";

    bool result = strCmp(str1, str2);

    EXPECT_FALSE(result);
}

TEST(UtilsTest, StrCmpEmptyStrings)
{
    const char* str1 = "";
    const char* str2 = "";

    bool result = strCmp(str1, str2);

    EXPECT_TRUE(result);
}

TEST(UtilsTest, StrCmpOneEmptyString)
{
    const char* str1 = "hello";
    const char* str2 = "";

    bool result = strCmp(str1, str2);

    EXPECT_FALSE(result);
}
