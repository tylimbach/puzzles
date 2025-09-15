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

inline std::tuple<ListNode*, ListNode*> reverseIfK(ListNode* head, int k) {
	ListNode* tail = head;
	for (int i = 0; i < k; i++) {
		if (tail->next == nullptr) {
			// undo what we have sorted thus far
			return reverseIfK(head, i);
		}
		auto temp = tail->next->next;
		head = tail->next;
		head->next = tail;
		tail->next = temp;
	}
	
	return {head, tail};
}
	
inline ListNode* reverseKGroup(ListNode* head, int k) {
	auto [firstHead, tail] = reverseIfK(head, k);

	while (tail->next != nullptr) {
		auto [nextHead, nextTail] = reverseIfK(tail->next, k);
		tail->next = nextHead;
		tail = nextTail;
		head = nextHead; // technically unnecessary
	}

	return firstHead;
}
};

