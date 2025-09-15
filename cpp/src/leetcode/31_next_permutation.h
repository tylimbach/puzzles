#pragma once
#include <utility>
#include <vector>

namespace leetcode {

inline void nextPermutation(std::vector<int>& nums) {
	if (nums.size() == 1) {
		return;
	}
	size_t r = nums.size() - 1;
	for (size_t l = r - 1; r > 0; r--, l--) {
		if (nums[l] < nums[r]) {
			std::optional<size_t> next_largest;
			for (size_t i = r; i < nums.size(); i++) {
				if (nums[i] > nums[l] && 
					(!next_largest.has_value() || nums[i] < nums[next_largest.value()])) {
					next_largest = i;
				}
			}
			std::swap(nums[l], nums[next_largest.value()]);
			std::sort(nums.begin() + static_cast<std::vector<int>::difference_type>(r), nums.end());
			return;
		}
	}

	std::sort(nums.begin() + static_cast<std::vector<int>::difference_type>(r), nums.end());
}


};
