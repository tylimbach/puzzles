#pragma once
#include <string>
#include <vector>

namespace leetcode {

inline bool isInterleaveRecurse(
	std::string& s1, std::string& s2, std::string& s3,
	size_t i1, size_t i2, size_t i3,
	std::vector<bool>& memo
) {
	if (i3 == s3.length()) return true;

	size_t index = i1 * (s2.length() + 1) + i2;
	if (memo[index]) return false;

	if (i1 < s1.length() && s1[i1] == s3[i3]) {
		if (isInterleaveRecurse(s1, s2, s3, i1 + 1, i2, i3 + 1, memo)) return true;
	}

	if (i2 < s2.length() && s2[i2] == s3[i3]) {
		if (isInterleaveRecurse(s1, s2, s3, i1, i2 + 1, i3 + 1, memo)) return true;
	}

	memo[index] = true;
	return false;
}

inline bool isInterleave(std::string s1, std::string s2, std::string s3) {
	std::vector<bool> memo((s1.length() + 1) * (s2.length() + 1), false);
	return s1.length() + s2.length() == s3.length() && 
		isInterleaveRecurse(s1, s2, s3, 0, 0, 0, memo);
}

};
