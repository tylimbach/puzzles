#pragma once
#include <cstddef>
#include <optional>
#include <stack>
#include <string>

/*
 )(()()))
1
*/

namespace leetcode {

inline size_t longestValidParentheses(std::string s) {
	std::stack<size_t> open_parens{};

	size_t l = 0, r = 0;
	std::optional<size_t> popped_prev;
	for (size_t i = 0; i < s.length(); i++) {
		if (s[i] == '(') {
			auto push_val = popped_prev.value_or(i);
			open_parens.push(push_val);
			popped_prev = std::nullopt;
		} else if (open_parens.empty()) {
			popped_prev = std::nullopt;	
		} else {
			popped_prev = open_parens.top();
			if (i - popped_prev.value() > r - l) {
				r = i;
				l = popped_prev.value();
			}
			open_parens.pop();
		}
	}

	if (r == 0) return 0;

	return r - l + 1;
}

};
