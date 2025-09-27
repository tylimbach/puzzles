#include <gtest/gtest.h>
#include "../../src/leetcode/38_count_and_say.h"

TEST(CountAndSayTest, One) {
    EXPECT_EQ(leetcode::countAndSay(1), "1");
}

TEST(CountAndSayTest, Two) {
    EXPECT_EQ(leetcode::countAndSay(2), "11");
}

TEST(CountAndSayTest, Three) {
    EXPECT_EQ(leetcode::countAndSay(3), "21");
}

TEST(CountAndSayTest, Four) {
    EXPECT_EQ(leetcode::countAndSay(4), "1211");
}

TEST(CountAndSayTest, Five) {
    EXPECT_EQ(leetcode::countAndSay(5), "111221");
}

