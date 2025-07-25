#pragma once

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <limits>
#include <memory>
#include <ranges>
#include <type_traits>
#include <utility>
#include <stdexcept>

namespace dev {

template<typename T, typename Allocator = std::allocator<T>>
class vector {
public:
    vector(size_t initial_capacity = 4, const Allocator& alloc = Allocator());
    ~vector();

    vector(const vector& other); 
    vector(vector&& other) noexcept;
    vector& operator=(const vector& other);
    vector& operator=(vector&& other) noexcept;

    void clear();
    template <typename... Args>
    void push_back(Args&&... args);
    void reserve(size_t new_capacity);
    
    T& at(size_t index);
    const T& at(size_t index) const;

    [[nodiscard]] bool is_full() const;
    [[nodiscard]] size_t size() const { return size_; }
    [[nodiscard]] size_t capacity() const { return capacity_; }
    
    T& operator[](size_t index) { return buf_[index]; }
    const T& operator[](size_t index) const { return buf_[index]; }

private:
    size_t size_;
    size_t capacity_;
    T* buf_;
    [[no_unique_address]] Allocator alloc_;
};

template<typename T, typename Allocator>
vector<T, Allocator>::vector(size_t initial_capacity, const Allocator& alloc)
    : size_(0), capacity_(initial_capacity), alloc_(alloc)
{ 
    buf_ = std::allocator_traits<Allocator>::allocate(alloc_, initial_capacity);
}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(const vector& other)
	: size_(other.size_), capacity_(other.capacity_), alloc_(std::allocator_traits<Allocator>::select_on_container_copy_construction(other.alloc_)) {
	buf_ = std::allocator_traits<Allocator>::allocate(alloc_, other.capacity_);
	auto src = std::ranges::subrange(other.buf_, other.buf_ + other.size_);
	auto dest = std::ranges::subrange(buf_, buf_ + other.size_);
	std::ranges::uninitialized_copy(src, dest);
}

template<typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other) {
	if (this == &other) {
		return *this;
	}

	clear();

	if constexpr (std::allocator_traits<Allocator>::propagate_on_container_copy_assignment::value) {
		alloc_ = other.alloc_;
	}

	if (capacity_ < other.size_) {
		std::allocator_traits<Allocator>::deallocate(alloc_, buf_, capacity_);
		capacity_ = other.size_; // assumption is we don't care to maintain extra space
		buf_ = std::allocator_traits<Allocator>::allocate(alloc_, capacity_);
	}

	try {
		auto src = std::ranges::subrange(other.buf_, other.buf_ + other.size_);
		auto dest = std::ranges::subrange(buf_, buf_ + other.size_);
		std::ranges::uninitialized_copy(src, dest);
		size_ = other.size_;
	} catch (std::exception) {
		size_ = 0;
		throw;
	}

	return *this;
}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(vector&& other) noexcept
	: size_(other.size_), capacity_(other.capacity_), buf_(other.buf_), alloc_(std::move(other.alloc_)) {
	other.capacity_ = 0;
	other.size_ = 0;
	other.buf_ = nullptr;
}

template<typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(vector&& other) noexcept {
	if (this == &other) {
		return *this;
	}

	if (buf_ != nullptr) {
		clear();
		std::allocator_traits<Allocator>::deallocate(alloc_, buf_, capacity_);
	}

	// c++ standards for allocator propogation
    if constexpr (std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value) {
        alloc_ = std::move(other.alloc_);
    } else if (alloc_ != other.alloc_) {
		buf_ = std::allocator_traits<Allocator>::allocate(alloc_, other.size_);
		auto src = std::ranges::subrange(other.buf_, other.buf_ + other.size_);
		auto dest = std::ranges::subrange(buf_, buf_ + other.size_);

		if constexpr (std::is_move_constructible_v<T>) {
			std::ranges::uninitialized_move(src, dest);
		} else {
			std::ranges::uninitialized_copy(src, dest);
		}

		size_ = other.size_;
		capacity_ = other.size_;
	} else {
		buf_ = other.buf_;
		size_ = other.size_;
		capacity_ = other.capacity_;
	}

	other.buf_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;

	return *this;
}

template<typename T, typename Allocator>
vector<T, Allocator>::~vector()
{ 
	if (buf_ != nullptr) {
		clear();
		std::allocator_traits<Allocator>::deallocate(alloc_, buf_, capacity_);
	}
}

template<typename T, typename Allocator>
void vector<T, Allocator>::clear() 
{
	if (buf_ != nullptr) {
		std::destroy(buf_, buf_ + size_);
	}
    size_ = 0;
}

template <typename T, typename Allocator>
template <typename... Args>
void vector<T, Allocator>::push_back(Args&&... args) 
{
    if (size_ == capacity_) {
		if (size_ == std::numeric_limits<size_t>::max()) {
			throw std::logic_error("vector is already at max size_t capacity");
		}

		if (std::numeric_limits<size_t>::max() / 2 < capacity_) {
			reserve(std::numeric_limits<size_t>::max());
		} else {
			reserve(capacity_ * 2);
		}
    }

    std::allocator_traits<Allocator>::construct(alloc_, buf_ + size_, std::forward<Args>(args)...);
    size_++;
}

template<typename T, typename Allocator>
void vector<T, Allocator>::reserve(size_t new_capacity) 
{
    if (new_capacity <= capacity_) {
        return;
    }

	[[assume(new_capacity > 0)]];

    T* temp = std::allocator_traits<Allocator>::allocate(alloc_, new_capacity);

    if constexpr (std::is_trivially_copyable_v<T>) {
        std::memcpy(temp, buf_, size_ * sizeof(T));
    } else {
        try {
			auto src = std::ranges::subrange(buf_, buf_ + size_);
			auto dest = std::ranges::subrange(temp, temp + size_);

            if constexpr (std::is_move_constructible_v<T>) {
                std::ranges::uninitialized_move(src, dest);
            } else {
                std::ranges::uninitialized_copy(src, dest);
            }
            
            std::destroy(buf_, buf_ + size_);
        } catch (const std::exception& e) {
            std::allocator_traits<Allocator>::deallocate(alloc_, temp, new_capacity);
            throw;
        }
    }

    std::allocator_traits<Allocator>::deallocate(alloc_, buf_, capacity_);
    buf_ = temp;
    capacity_ = new_capacity;
}

template<typename T, typename Allocator>
T& vector<T, Allocator>::at(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return buf_[index];
}

template<typename T, typename Allocator>
const T& vector<T, Allocator>::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return buf_[index];
}

template<typename T, typename Allocator>
bool vector<T, Allocator>::is_full() const 
{
    return size_ == capacity_;
}

} // namespace dev
