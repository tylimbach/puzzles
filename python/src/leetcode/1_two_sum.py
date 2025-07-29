# 1. Two Sum
# Solved
# Easy
#
# Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
# You may assume that each input would have exactly one solution, and you may not use the same element twice.
# You can return the answer in any order.
#
# Example 1:
#
# Input: nums = [2,7,11,15], target = 9
# Output: [0,1]
# Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
# Example 2:
#
# Input: nums = [3,2,4], target = 6
# Output: [1,2]
# Example 3:
#
# Input: nums = [3,3], target = 6
# Output: [0,1]
#
#
# Constraints:
#
# 2 <= nums.length <= 104
# -109 <= nums[i] <= 109
# -109 <= target <= 109
# Only one valid answer exists.


def solve_2sum_inefficient(nums: list[int], target: int):
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            if i == j:
                continue
            
            sum = nums[i] + nums[j]
            if sum == target:
                return [i, j]


def solve_2sum_efficient(nums: list[int], target: int):
    seen = dict()

    for index, num in enumerate(nums):
        complement = target - num
        if complement in seen:
            complement_index = seen[complement]
            return [index, complement_index]

        seen[num] = index

def test():
    nums = []
    for _ in range(100000000):
        nums.append(1)
    nums.append(20)

    solve_2sum_inefficient(nums, 21)
    solve_2sum_efficient(nums, 21)


