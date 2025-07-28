#include <filesystem>
#include <fstream>
#include <ranges>
#include <span>
#include <gtest/gtest.h>
#include "../../src/io/csv_parser.h"

struct LoMidHiCt {
	double low;
	double mid;
	double high;
	int count;

    auto operator<=>(const LoMidHiCt&) const = default;
};

TEST(IOTest, Example1) {
	std::cout << "cwd: " << std::filesystem::current_path() << std::endl;

	std::ifstream file("res/csv_example_1.csv");
    ASSERT_TRUE(file.is_open()) << "Failed to open CSV file";

	dev::CsvParser<LoMidHiCt, double, double, double, int> parser(file);
	std::optional<LoMidHiCt> actual = parser.read_next();
	std::optional<LoMidHiCt> expected = LoMidHiCt { 1.0, 5.0, 3.0, 1000 };
	EXPECT_EQ(actual, expected);
}

TEST(IOTest, Example2) {
	std::cout << "cwd: " << std::filesystem::current_path() << std::endl;

	std::ifstream file("res/csv_example_2.csv");
    ASSERT_TRUE(file.is_open()) << "Failed to open CSV file";

	std::vector<LoMidHiCt> actual_items(3);
	std::span<LoMidHiCt> view(actual_items);
	dev::CsvParser<LoMidHiCt, double, double, double, int> parser(file);

	size_t lines_read = parser.read_batch(view);
	EXPECT_EQ(lines_read, 3);

	std::vector<LoMidHiCt> expected_items {
		{ 1.0, 5.0, 3.0, 1000 },
		{ 1.0, 5.0, 3.0, 1000 },
		{ 1.5, 12, 50.001, 320 },
	};
	
	for (auto [actual, expected] : std::views::zip(actual_items, expected_items)) {
		EXPECT_EQ(actual, expected);
	}
}
