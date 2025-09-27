
#include <vector>
namespace leetcode {


/*
    1
   2 3
  4 56 7

*/

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

inline void postOrderTraverse(std::vector<Node*>& rightAtDepth, Node* node, size_t depth) {
	if (rightAtDepth.size() < depth + 1) {
		rightAtDepth.push_back(nullptr);
	}

	if (node->right != nullptr) {
		postOrderTraverse(rightAtDepth, node->right, depth + 1);
		postOrderTraverse(rightAtDepth, node->left, depth + 1);
	}

	node->next = rightAtDepth[depth];
	rightAtDepth[depth] = node;
}

inline Node* connect(Node* root) {
	std::vector<Node*> rightAtDepth{};

	if (root != nullptr) {
		postOrderTraverse(rightAtDepth, root, 0);
	}
	return root;
}

}
