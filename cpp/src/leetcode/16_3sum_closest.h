#pragma once
#include <algorithm>
#include <cassert>
#include <vector>
#include <cmath>

/*
https://leetcode.com/problems/3sum-closest/description/
16. 3Sum Closest
Given an integer array nums of length n and an integer target, find three integers in nums such that the sum is closest to target.

Return the sum of the three integers.

You may assume that each input would have exactly one solution.

 

Example 1:

Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
Example 2:

Input: nums = [0,0,0], target = 1
Output: 0
Explanation: The sum that is closest to the target is 0. (0 + 0 + 0 = 0).
 

Constraints:

3 <= nums.length <= 500
-1000 <= nums[i] <= 1000
-104 <= target <= 104
*/

namespace leetcode {

/*
	brute force - check all combos of 3 values (n * (n - 1) * (n - 2))
	3 ptr - n * n + sort (nlogn)
*/

inline int threeSumClosest(std::vector<int>& nums, int target) {
	assert(nums.size() >= 3);

	std::sort(nums.begin(), nums.end());

	int closest = nums[0] + nums[1] + nums[2];
	for (int m = 1; m < nums.size() - 1; m++) {
		int l = 0;
		int r = nums.size() - 1;
		while (l < m && r > m) {
			int sum3 = nums[l] + nums[m] + nums[r];

			if (sum3 == target) {
				return sum3;
			}

			if (std::abs(target - sum3) < std::abs(target - closest)) {
				closest = sum3;	
			} 

			if (sum3 < target) {
				l++;		
			} else {
				r--;
			}
		}
	}

	return closest;
}

} // namespace leetcode
