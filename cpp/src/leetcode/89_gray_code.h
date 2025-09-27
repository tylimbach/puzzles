
#include <vector>
namespace leetcode {

/*
000 001 011 010 110 111 101 100 000


  1 2 3
  x
  x x
    x
	x x
  x x x
  x   x
      x
jjjjj
00 -> 10 or 01
     11 or 00  | 11 or 00
x


00

*/

bool recurse(std::vector<bool>& memo, std::vector<int>& path, size_t value, int n, size_t nums) {
	if (memo[value]) return false;

	memo[value] = true;	
	path.push_back(static_cast<int>(value));
	if (path.size() == nums) return true; // technically this might be wrong, ex: can u end on 11 starting on 00?

	for (int i = 0; i < n; i++) {
		size_t newValue = value ^ (1 << i);
		bool validSln = recurse(memo, path, newValue, n, nums);

		if (validSln) {
			return true;
		}
	}

	memo[value] = false;
	path.pop_back();

	return false;
}

inline std::vector<int> grayCode(int n) {
	size_t nums = 1;
	for (int i = 0; i < n; i++) {
		nums *= 2;
	}

	std::vector<bool> memo(nums, false);
	std::vector<int> path;
	path.reserve(nums);
	recurse(memo, path, 0, n, nums);

	return path;
}

}
