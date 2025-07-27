#pragma once

#include "vector.h"
#include <concepts>
#include <limits>
#include <stdexcept>
#include <utility>

namespace dev {

template <typename H, typename K>
concept Hasher = requires(H hash, K key) {
    { hash(key) } -> std::convertible_to<size_t>;
};

template <typename K, typename V, typename Hash = std::hash<K>>
	requires Hasher<Hash, K>
class oa_hashmap
{
public:
	oa_hashmap(const size_t initial_capacity = DEFAULT_INITIAL_CAPACITY, const Hash hasher = Hash());
	~oa_hashmap();

	oa_hashmap(const oa_hashmap& other);
	oa_hashmap(oa_hashmap&& other) noexcept = delete;
	oa_hashmap& operator=(const oa_hashmap& other);
	oa_hashmap& operator=(oa_hashmap&& other) noexcept = delete;

	void clear();
	bool contains(const K& key);
	void grow(size_t capacity);
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
	enum class State: uint8_t { EMPTY, OCCUPIED, DELETED };
	struct Node {
		Node(){}
		Node(K key, V value) : key_(std::move(key)), value_(std::move(value)), state_(State::OCCUPIED){}

		K key_;
		V value_;
		State state_{ State::EMPTY };
	};

	size_t get_hash_index(const K& key) const;
	size_t find_slot(const K& key) const;
	void maybe_rehash();

    static constexpr float DEFAULT_MAX_LOAD_FACTOR = 0.35f;
    static constexpr size_t DEFAULT_INITIAL_CAPACITY = 16;

	vector<Node> table_;
	size_t size_{ 0 };
	float max_load_factor_{ DEFAULT_MAX_LOAD_FACTOR };
	Hash hasher_{ Hash() };
};


template <typename K, typename V, typename Hash>
	requires Hasher<Hash, K>
oa_hashmap<K, V, Hash>::oa_hashmap(size_t initial_capacity, Hash hasher) : hasher_(hasher) {
	table_ = vector<Node>(initial_capacity);
}

template <typename K, typename V, typename Hash>
	requires Hasher<Hash, K>
oa_hashmap<K, V, Hash>::~oa_hashmap() {

}

template <typename K, typename V, typename Hash>
	requires Hasher<Hash, K>
oa_hashmap<K, V, Hash>& oa_hashmap<K, V, Hash>::operator=(const oa_hashmap<K, V, Hash>& other) {

}

template <typename K, typename V, typename Hash>
	requires Hasher<Hash, K>
void oa_hashmap<K, V, Hash>::clear() {

}

/*
 * @brief Insert the pair into the hash map.
 * @return True if the pair was inserted. False if the key already exists.
 */
template <typename K, typename V, typename Hash>
	requires Hasher<Hash, K>
template <typename KF, typename VF>
	requires std::convertible_to<KF, K> && std::convertible_to<VF, V>  
bool oa_hashmap<K, V, Hash>::insert(KF&& key, VF&& value) {
	size_t hash_index = hasher_(std::forward<KF>(key)) % table_.capacity();
	Node& node = table_[hash_index];

	while (node.state_ != State::EMPTY) {
		if (node.state_ == State::OCCUPIED && node.key_ == key) {
			return false;
		}
		hash_index = (hash_index + 1) % table_.capacity();
		node = table_[hash_index];
	}

	node.key_ = std::forward<KF>(key);
	node.value_ = std::forward<VF>(value);
	node.state_ = State::OCCUPIED;

	if ((float)size_ / table_.capacity() > max_load_factor_) {
		if (std::numeric_limits<size_t>::max() / 2 < table_.capacity()) {
			throw new std::logic_error("oa_hashmap overflow");
		}
		size_t new_capacity = table_.capacity() * 2;
		grow(new_capacity);
	}

	return true;
}

};
