#include <gtest/gtest.h>
#include "../../src/leetcode/js_mock.h"
#include <ranges>

TEST(JsMockTest, Good) {
	std::vector<leetcode::js::Fact> facts {};
	facts.push_back({"m", 100, "cm"});
	facts.push_back({"in", 2.50, "cm"});
	std::vector<leetcode::js::Query> queries {};
	queries.push_back({1, "m", "in"});

	std::vector<std::optional<double>> actual_list = leetcode::js::query(facts, queries);
	std::vector<std::optional<double>> expected_list { 40 };
	for (auto [actual, expected] : std::views::zip(actual_list, expected_list)) {
		EXPECT_EQ(actual, expected);
	}
}
