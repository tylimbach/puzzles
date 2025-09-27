#include <cassert>
#include <vector>

namespace leetcode {

/*

sorting makes our comparisons much more limited / easier

*/

inline std::vector<std::vector<int>> merge (std::vector<std::vector<int>>& intervals) {
	assert(intervals.size() >= 1);
	std::sort(intervals.begin(), intervals.end(), [](auto &l, auto &r) { return l[0] < r[0]; });
	std::vector<std::vector<int>> results {};

	std::vector<int> left = intervals[0];
	for (size_t i = 1; i < intervals.size(); i++) {
		if (intervals[i][0] - left[1] < 1) {
			auto min = left[0];
			auto max = std::max(intervals[i][1], left[1]);

			left = { min, max };
		} else {
			results.push_back(left);
			left = intervals[i];
		}
	}

	results.push_back(left);

	return results;
}

}

