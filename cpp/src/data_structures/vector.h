#pragma once

#include <cstddef>
#include <cstring>
#include <memory>
#include <type_traits>
#include <utility>
#include <stdexcept>

namespace dev {

template<typename T, typename Allocator = std::allocator<T>>
class vector {
public:
    vector(size_t initial_capacity = 4, const Allocator& alloc = Allocator());
    ~vector();

    vector(const vector& other) = default; 
    vector(vector&& other) noexcept = default;
    vector& operator=(const vector& other) = default;
    vector& operator=(vector&& other) noexcept = default;

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
vector<T, Allocator>::~vector()
{ 
    clear();
    std::allocator_traits<Allocator>::deallocate(alloc_, buf_, capacity_);
}

template<typename T, typename Allocator>
void vector<T, Allocator>::clear() 
{
    std::destroy(buf_, buf_ + size_);
    size_ = 0;
}

template <typename T, typename Allocator>
template <typename... Args>
void vector<T, Allocator>::push_back(Args&&... args) 
{
    if (size_ == capacity_) {
        reserve(capacity_ * 2);
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
