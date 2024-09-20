#include <gtest/gtest.h>
#include <iostream>


TEST(MathTest, Addition) {
    EXPECT_EQ(1 + 1, 2);  // This should pass
}

// A basic test for string comparison
TEST(StringTest, CompareStrings) {
    EXPECT_STREQ("hello", "hello");  // This should pass
    EXPECT_STRNE("hello", "world");  // This should pass
}

// A basic test that deliberately fails
TEST(FailingTest, IntentionalFailure) {
    EXPECT_EQ(1 + 1, 3);  // This will fail
}
