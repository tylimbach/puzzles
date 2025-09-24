#include <gtest/gtest.h>
#include "../../src/leetcode/12_integer_to_roman.h"

TEST(IntegerToRomanTest, Nine) {
    EXPECT_EQ(leetcode::intToRoman(9), "IX");
}

TEST(IntegerToRomanTest, Ten) {
    EXPECT_EQ(leetcode::intToRoman(10), "X");
}

TEST(IntegerToRomanTest, ThreeNineNineNine) {
    EXPECT_EQ(leetcode::intToRoman(3999), "MMMCMXCIX");
}
