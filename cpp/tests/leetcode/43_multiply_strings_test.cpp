#include <gtest/gtest.h>
#include "../../src/leetcode/43_multiply_strings.h"

TEST(MultiplyStringsTest, Example1) {
    EXPECT_EQ(leetcode::multiply("2", "3"), "6");
}

TEST(MultiplyStringsTest, Example2) {
    EXPECT_EQ(leetcode::multiply("123", "456"), "56088");
}

TEST(MultiplyStringsTest, ZeroMultiplication) {
    EXPECT_EQ(leetcode::multiply("0", "123"), "0");
    EXPECT_EQ(leetcode::multiply("456", "0"), "0");
    EXPECT_EQ(leetcode::multiply("0", "0"), "0");
}

TEST(MultiplyStringsTest, LargeNumbers) {
    EXPECT_EQ(leetcode::multiply("9999", "9999"), "99980001");
}

TEST(MultiplyStringsTest, SingleDigits) {
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 9; j++) {
            std::string expected = std::to_string(i * j);
            EXPECT_EQ(leetcode::multiply(std::to_string(i), std::to_string(j)), expected);
        }
    }
}