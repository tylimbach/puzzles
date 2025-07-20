#pragma once

#include <cstddef>
#include <cstring>
#include <type_traits>
#include <utility>

namespace dev {

template<typename T>
class vector {
public:
    vector(size_t initial_capacity = 4);
    ~vector();

    vector(const vector& other) = default; 
    vector(vector&& other) noexcept = default;
    vector& operator=(const vector& other) = default;
    vector& operator=(vector&& other) noexcept = default;

    /**
     * @brief Remove all elements.
     */
    void clear();

    template <typename... Args>
    void push_back(Args&&... args);
    
    void reserve(size_t new_capacity);

    [[nodiscard]] bool is_full() const;
    
    // Additional useful methods
    [[nodiscard]] size_t size() const { return size_; }
    [[nodiscard]] size_t capacity() const { return capacity_; }
    
    T& operator[](size_t index) { return buf_[index]; }
    const T& operator[](size_t index) const { return buf_[index]; }

private:
    size_t size_;
    size_t capacity_;
    T* buf_;
};

// Template implementation

template<typename T>
vector<T>::vector(size_t initial_capacity)
    : size_(0), capacity_(initial_capacity) 
{ 
    buf_ = static_cast<T*>(operator new(sizeof(T) * initial_capacity));
}

template<typename T>
vector<T>::~vector()
{ 
    clear();
    operator delete(buf_);
}

template<typename T>
void vector<T>::clear() 
{
    for (size_t i = size_; i > 0; i--) {
        buf_[i - 1].~T();
    }
    size_ = 0;
}

template <typename T>
template <typename... Args>
void vector<T>::push_back(Args&&... args) 
{
    if (size_ == capacity_) {
        reserve(capacity_ * 2);
    }

    new (buf_ + size_) T(std::forward<Args>(args)...);
    size_++;
}

template<typename T>
void vector<T>::reserve(size_t new_capacity) 
{
    if (new_capacity <= capacity_) {
        return;
    }

    T* temp = static_cast<T*>(operator new(sizeof(T) * new_capacity));

    if constexpr (std::is_trivially_copyable_v<T>) {
        std::memcpy(temp, buf_, size_ * sizeof(T));
    } else {
        size_t i = 0;
        try {
            for (; i < size_; i++) {
                if constexpr (std::is_move_constructible_v<T>) {
                    new (temp + i) T(std::move(buf_[i]));
                } else {
                    new (temp + i) T(buf_[i]);
                }
            }
        } 
        catch (...) {
            // Clean up any successfully constructed elements
            for (size_t j = 0; j < i; j++) {
                (temp + j)->~T();
            }
            operator delete(temp);
            throw; // Rethrow
        }
        
        // Destroy original elements
        for (size_t i = 0; i < size_; i++) {
            buf_[i].~T();
        }
    }

    operator delete(buf_);
    buf_ = temp;
    capacity_ = new_capacity;
}

template<typename T>
bool vector<T>::is_full() const 
{
    return size_ == capacity_;
}

} // namespace dev