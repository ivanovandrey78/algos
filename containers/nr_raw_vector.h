#pragma once 

#include <iostream>
#include <cstddef>
#include <new>

template<typename T>
class RandomAccessIterator {
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = std::ptrdiff_t;
    using iterator_type = std::random_access_iterator_tag;

    reference operator*() {

    }

private:
    pointer ptr_;
};

template <class T>
struct LoggingAllocator {
    using value_type = T;

    LoggingAllocator() noexcept = default;

    template <class U>
    LoggingAllocator(const LoggingAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        std::cout << "allocate " << n << " objects of size " << sizeof(T) << '\n';
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) noexcept {
        std::cout << "deallocate " << n << " objects\n";
        ::operator delete(p);
    }
};

template <typename T, typename Allocator = std::allocator<T>>
class raw_vector {
public:
    // Name Requirements
    using value_type = T;
    using allocator_type = Allocator;
    using traits = std::allocator_traits<Allocator>;

    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;

    using iterator = T*;
    using const_iterator = const T*;

    // Constructor & destructor
    raw_vector() = default;
    explicit raw_vector(size_t capacity) {
        reserve(capacity);
    }
    ~raw_vector() noexcept {
        clear();
        if (data_) {
            traits::deallocate(alloc_, data_, capacity_);
        }
    }

    // Copy semantics
    raw_vector(const raw_vector& other) 
        : alloc_(other.alloc_) 
    {
        if (other.size_ == 0) { return; }
        pointer new_data = traits::allocate(alloc_, other.capacity_);
        size_t i = 0;
        try {
            for (; i < other.size_; ++i) {
                traits::construct(alloc_, new_data + i, other.data_[i]);
            }
        } catch (...) {
            for (std::size_t j = 0; j < i; ++j) {
                traits::destroy(alloc_, new_data + j);
            }
            traits::deallocate(alloc_, new_data, other.capacity_);
            throw;
        }
        data_ = new_data;
        size_ = other.size_;
        capacity_ = other.capacity_;
    }

    raw_vector& operator=(const raw_vector& other) = delete;
    raw_vector& operator=(raw_vector&& other) = delete;

    // Move semantics
    raw_vector(raw_vector&& other) noexcept
        : data_(other.data_),
          alloc_(std::move(other.alloc_)), 
          size_(other.size_),
          capacity_(other.capacity_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    reference operator[](size_t index) {
        return data_[index];
    }
    const_reference operator[](size_t index) const {
        return data_[index];
    }

    void reserve(size_t new_cap) {
        if (new_cap <= capacity_) { return; }
        pointer new_data = traits::allocate(alloc_, new_cap);
        size_t old_size = size_;
        size_t i = 0;
        try {
            for (; i < size_; ++i) {
                traits::construct(alloc_, new_data + i, data_[i]);
            }
        } catch (...) {
            for (size_t j = 0; j < i; ++j) {
                traits::destroy(alloc_, new_data + j);
            }
            traits::deallocate(alloc_, new_data, new_cap);
            throw;
        }
        clear();
        if (data_) {
            traits::deallocate(alloc_, data_, capacity_);
        }
        data_ = new_data;
        capacity_ = new_cap;
        size_ = old_size;
    }

    // STL Container minimum functions
    iterator begin() noexcept { return data_; }
    const_iterator begin() const noexcept  { return data_; }
    const_iterator cbegin() const noexcept { return data_; }

    iterator end() noexcept { return data_ + size_; }
    const_iterator end() const noexcept  { return data_ + size_; }
    const_iterator cend() const noexcept { return data_ + size_; }

    bool empty() const noexcept { return size_ == 0; }
    size_type size() const noexcept { return size_; }
    size_type max_size() const noexcept { return static_cast<size_type>(-1) / sizeof(T); }

    void swap(raw_vector& other) noexcept {
        using std::swap;
        swap(data_, other.data_);
        swap(size_, other.size_);
        swap(capacity_, other.capacity_);
    }

    // Sequence Container functions 
    reference front() { return data_[0]; }
    const_reference front() const { return data_[0]; }
    reference back() { return data_[size_ - 1]; }
    const_reference back() const { return data_[size_ - 1]; }

    void push_back(const T& x) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        traits::construct(alloc_, data_ + size_, x);
        ++size_;
    }
    void push_back(T&& x) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        traits::construct(alloc_, data_ + size_, std::move(x));
        ++size_;
    }
    void pop_back() noexcept {
        if (size_ == 0) return;
        traits::destroy(alloc_, data_ + size_ - 1);
        --size_;
    }
    void push_front(const T& x) {}
    void push_front(T&& x) {}
    void pop_front() {}
    void clear() noexcept {
        for (size_t i = 0; i < size_; ++i) {
            traits::destroy(alloc_, data_ + i);
        }
        size_ = 0;
    }

private:
    pointer data_ = nullptr;
    allocator_type alloc_;
    size_t size_ = 0;
    size_t capacity_ = 0;
};