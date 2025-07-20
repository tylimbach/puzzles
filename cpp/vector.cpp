
#include <cstddef>
#include <cstring>
#include <type_traits>
#include <utility>
namespace dev {

template<typename T>
class vector {
public:
	vector(size_t inital_capacity = 4) 
		: size_(0), capacity_(inital_capacity) { 
		buf_ = static_cast<T*>(operator new (sizeof(T) * inital_capacity));
	};
	~vector() { 
		clear();
		operator delete(buf_); 
	};

	vector(const vector& other) = default; 
	vector(vector&& other) noexcept = default;
	vector& operator=(const vector& other) = default;
	vector& operator=(vector&& other) noexcept = default;

	/**
	 * @brief Remove all elements.
	 */
	void clear() {
		for (size_t i = size_; i > 0; i--) {
			buf_[i - 1].~T();
		}

		size_ = 0;
	}

	template <typename... Args>
	void push_back(Args&&... args) {
		if (size_ == capacity_) {
			reserve(capacity_ * 2);
		}

		new (buf_ + size_) T(std::forward<Args>(args)...);
		size_++;
	}

	void reserve(size_t new_capacity) {
		if (new_capacity < capacity_) {
			return;
		}

		T* temp = static_cast<T*>(operator new (sizeof(T) * new_capacity));

		if constexpr (std::is_trivially_copyable_v<T>) {
			std::memcpy(temp, buf_, size_ * sizeof(T));
		} else {
			for (size_t i = 0; i < size_; i++) {
				if constexpr (std::is_move_constructible_v<T>) {
					new (temp + i) T(std::move(buf_[i]));
				} else {
					new (temp + i) T(buf_[i]);
				}
			}
			for (size_t i = 0; i < size_; i++) {
				buf_[i].~T();
			}
		}

		delete(buf_);
		buf_ = temp;
		capacity_ = new_capacity;
	}

	[[nodiscard]] bool const is_full() {
		return size_ == capacity_;
	}

private:
	size_t size_;
	size_t capacity_;
	T buf_[];
};

};
