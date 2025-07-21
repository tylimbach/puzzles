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

	size_t size() const;
	size_t capacity() const;
	bool is_empty() const;

	V& operator[](const K& key);

private:
	enum class State { EMPTY, OCCUPIED, DELETED };
	struct Node {
		Node() : state_(State::EMPTY) {};

		K key_;
		V value_;
		State state_;
	};

	size_t get_hash_index(const K& key) const;
	size_t find_slot(const K& key) const;
	void maybe_rehash();

    static constexpr float DEFAULT_MAX_LOAD_FACTOR = 0.75f;
    static constexpr size_t DEFAULT_INITIAL_CAPACITY = 16;

	vector<Node> table_;
	size_t size_;
	size_t capacity_;
	float max_load_factor_;
	Hash hasher_;
};


template <typename K, typename V, typename Hash>
oa_hashmap<K, V, Hash>::oa_hashmap() {
	throw;
}

template <typename K, typename V, typename Hash>
oa_hashmap<K, V, Hash>::~oa_hashmap() {

}

};


