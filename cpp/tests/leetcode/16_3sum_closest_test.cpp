#include <gtest/gtest.h>
#include "../../src/leetcode/16_3sum_closest.h"

TEST(MultiplyStringsTest, Match) {
	std::vector<int> nums{1, 2, 3, 4, 5, 8};
    EXPECT_EQ(leetcode::threeSumClosest(nums, 8), 8);
}

TEST(MultiplyStringsTest, High) {
	std::vector<int> nums{1, 2, 3, 4, 5, 8};
    EXPECT_EQ(leetcode::threeSumClosest(nums, 20), 17);
}

TEST(MultiplyStringsTest, Low) {
	std::vector<int> nums{1, 2, 3, 4, 5, 8};
    EXPECT_EQ(leetcode::threeSumClosest(nums, 3), 6);
}
