/*
Any leftover nodes at end are unchanged

Ex:
1, 2, 3, 4, 5, 6
k = 2
2, 1, 4, 3, 6, 5


1 2 3 4
2 1 3 4
3 2 1 4
4 3 2 1
head 1 2 3 4
head next 2 1 2 3
tail 1 1 1 1
tail next 2 3 4 _

Approach:
How do we reverse one list?
- Use a stack to flip it
- O(1) swap one node at a time

For multiple
- Reverse one list
- cache prev end
- reverse the next list, update prev end next to new head
- if our list ends early, reverse the current head again

*/

#pragma once

#include <tuple>
namespace leetcode {
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

inline std::tuple<ListNode*, ListNode*> reverseK(ListNode* head, int k, bool undo) {
	ListNode* tail = head;
	for (int i = 0; i < k - 1; i++) {
		if (tail->next == nullptr) {
			return undo 
				? std::tuple<ListNode*, ListNode*>{head, tail} 
				: reverseK(head, k, true);
		}
		auto prevHead = head;
		head = tail->next;
		tail->next = tail->next->next;
		head->next = prevHead;
	}
	
	return {head, tail};
}
	
inline ListNode* reverseKGroup(ListNode* head, int k) {
	auto [firstHead, tail] = reverseK(head, k, false);

	while (tail->next != nullptr) {
		auto [nextHead, nextTail] = reverseK(tail->next, k, false);
		tail->next = nextHead;
		tail = nextTail;
		head = nextHead; // technically unnecessary
	}

	return firstHead;
}
};

