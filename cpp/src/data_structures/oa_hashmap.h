#pragma once

#include "vector.h"
#include <concepts>
namespace dev {

template <typename K, typename V, typename Hash = std::hash<K>>
class oa_hashmap
{
public:
	oa_hashmap();
	~oa_hashmap();

	oa_hashmap(const oa_hashmap& other);
	oa_hashmap(oa_hashmap&& other) noexcept = delete;
	oa_hashmap& operator=(const oa_hashmap& other);
	oa_hashmap& operator=(oa_hashmap&& other) noexcept = delete;

	void clear();
	bool contains(const K& key);
	void reserve(size_t capacity);
	std::optional<V> remove(const K& key);

	V& at(const K& key) noexcept;
	const V& at(const K& key) const noexcept;

	template <typename KF, typename VF>
		requires std::convertible_to<KF, K> && std::convertible_to<VF, V>
	bool insert(KF&& key, VF&& value);

	template <typename... VArgs>
	bool emplace(const K& key, VArgs&&... args);

	template <typename... KArgs, typename... VArgs>
	bool try_emplace(KArgs&&... k_args, VArgs&&... v_args);

	size_t size();
	bool is_empty();

	V& operator[](const K& key);

private:
	struct Node {
		Node(K key, V value) : key_(key), value_(value){};

		K key_;
		V value_;
		// TODO: do we need special destructor?
	};

	size_t get_hash_index();

	vector<Node> table_;
	size_t size_;
	size_t capacity_;
};


template <typename K, typename V, typename Hash>
oa_hashmap<K, V, Hash>::oa_hashmap() {
	throw;
}

template <typename K, typename V, typename Hash>
oa_hashmap<K, V, Hash>::~oa_hashmap() {

}

};


