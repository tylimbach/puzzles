#include <unordered_map>
namespace leetcode {

template<typename T>
struct ListNode {
	T value;
	ListNode<T>* next;
	ListNode<T>* prev;

	ListNode(T value) : value(value), next(nullptr), prev(nullptr) { }
};

class LRUCache {
public:
	LRUCache(int capacity) : _capacity(capacity) { }

	int get(int key) {
		auto found = _map.find(key);
		if (found != _map.end()) {
			return found->second->value;
		}

		return -1;
	}

	void put(int key, int value) {
		auto found = _map.find(key);
		if (found != _map.end()) {
			found->second->value = value;
			toFront(found->second);
		} else if (_size < _capacity) {
			auto node = new ListNode(value);
			_map[key] = node;
			_size++;

			toFront(node);
		} else {
			if (_capacity == _size) {
				removeBack();
			}

			auto node = new ListNode(value);
			_map[key] = node;
			toFront(node);
		}
	}

private:
	int _size = 0;
	int _capacity;
	std::unordered_map<int, ListNode<int>*> _map;
	ListNode<int>* _mru;
	ListNode<int>* _lru;

	void toFront(ListNode<int>* node) {
		if (node->prev != nullptr) {
			if (node->next != nullptr) {
				node->next->prev = node->prev;
			}
			node->prev->next = node->next;
			node->next = _mru;
			_mru = node;
			_mru->next->prev = _mru;
		}
	}

	void removeBack() {
		auto prev = _lru->prev;
		prev->next = nullptr;
		delete _lru;

		_lru = prev; 
	}
};

}
