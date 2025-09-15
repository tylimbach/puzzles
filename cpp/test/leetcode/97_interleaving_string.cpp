#include <gtest/gtest.h>
#include "../../src/leetcode/97_interleaving_string.h"

TEST(InterleavingStringTest, Example1) {
    EXPECT_TRUE(leetcode::isInterleave("aabcc", "dbbca", "aadbbcbcac"));
}

TEST(InterleavingStringTest, Example2) {
    EXPECT_FALSE(leetcode::isInterleave("aabcc", "dbbca", "aadbbbaccc"));
}
