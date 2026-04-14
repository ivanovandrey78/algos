#pragma once 

#include <cstddef>
#include <iterator>

template<typename T>
class Iterator {
public: 
    using value_type = T;
    using pointer = T*;
    using reference = const T&;
    // using iterator_category = std::iterator; - standart iterator
    using difference_type = std::ptrdiff_t;

    explicit Iterator(T* ptr) : ptr_(ptr) {}
    Iterator() : ptr_(nullptr) {}

    Iterator& operator++() {
        ++ptr_;
        return *this;
    }
    reference operator*() const { return *ptr_; }

private:
    T* ptr_;
};

template<typename T>
class InputIterator {
public: 
    using value_type = T;
    using pointer = T*;
    using reference = const T&;
    using iterator_category = std::input_iterator_tag;
    using difference_type = std::ptrdiff_t;

    explicit InputIterator(T* ptr) : ptr_(ptr) {}
    InputIterator() : ptr_(nullptr) {}

    InputIterator& operator++() {
        ++ptr_;
        return *this;
    }
    InputIterator operator++(int) {
        InputIterator tmp = *this;
        ++ptr_;
        return tmp;
    }

    reference operator*() const { return *ptr_; }
    pointer operator->() const { return ptr_; }

    bool operator==(const InputIterator& other) const {
        return ptr_ == other.ptr_;
    }
    bool operator!=(const InputIterator& other) const {
        return ptr_ != other.ptr_;
    }

private:
    T* ptr_;
};

template<typename T>
class OutputIterator {
public:
    using value_type = void; // For records only
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::output_iterator_tag;
    using difference_type = std::ptrdiff_t;

    OutputIterator(T* ptr) : ptr_(ptr) {}

    OutputIterator& operator++() {
        ++ptr_;
        return *this;
    }
    OutputIterator operator++(int) {
        OutputIterator tmp = *this;
        ++ptr_;
        return tmp;
    }
    reference operator*() { return *ptr_; }

private:
    T* ptr_;
};

template<typename T>
class ForwardIterator {
public: 
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;

    explicit ForwardIterator(T* ptr) : ptr_(ptr) {}
    ForwardIterator() : ptr_(nullptr) {}

    ForwardIterator& operator++() {
        ++ptr_;
        return *this;
    }
    ForwardIterator operator++(int) {
        ForwardIterator tmp = *this;
        ++ptr_;
        return tmp;
    }

    reference operator*() { return *ptr_; }
    pointer operator->() const { return ptr_; } 

    bool operator==(const ForwardIterator& other) const {
        return ptr_ == other.ptr_;
    }
    bool operator!=(const ForwardIterator& other) const {
        return ptr_ != other.ptr_;
    }

private:
    T* ptr_;
};  

template<typename T>
class BidirectionalIterator {
public: 
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    explicit BidirectionalIterator(T* ptr) : ptr_(ptr) {}
    BidirectionalIterator() : ptr_(nullptr) {}

    BidirectionalIterator& operator++() {
        ++ptr_;
        return *this;
    }
    BidirectionalIterator operator++(int) {
        BidirectionalIterator tmp = *this;
        ++ptr_;
        return tmp;
    }
    BidirectionalIterator& operator--() {
        --ptr_;
        return *this;
    }
    BidirectionalIterator operator--(int) {
        BidirectionalIterator tmp = *this;
        --ptr_;
        return tmp;
    }

    reference operator*() { return *ptr_; }
    pointer operator->() const { return ptr_; } 

    bool operator==(const BidirectionalIterator& other) const {
        return ptr_ == other.ptr_;
    }
    bool operator!=(const BidirectionalIterator& other) const {
        return ptr_ != other.ptr_;
    }

private:
    T* ptr_;
};

template<typename T>
class RandomAccessIterator {
public: 
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;

    explicit RandomAccessIterator(T* ptr) : ptr_(ptr) {}
    RandomAccessIterator() : ptr_(nullptr) {}

    RandomAccessIterator& operator++() {
        ++ptr_;
        return *this;
    }
    RandomAccessIterator operator++(int) {
        RandomAccessIterator tmp = *this;
        ++ptr_;
        return tmp;
    }
    RandomAccessIterator& operator--() {
        --ptr_;
        return *this;
    }
    RandomAccessIterator operator--(int) {
        RandomAccessIterator tmp = *this;
        --ptr_;
        return tmp;
    }

    RandomAccessIterator& operator+=(difference_type n) {
        ptr_ += n; 
        return *this;
    }
    RandomAccessIterator& operator-=(difference_type n) {
        ptr_ -= n; 
        return *this;
    }

    RandomAccessIterator operator+(difference_type n) const {
        RandomAccessIterator tmp = *this;
        tmp += n;
        return tmp;
    }
    RandomAccessIterator operator-(difference_type n) const {
        RandomAccessIterator tmp = *this;
        tmp -= n;
        return tmp;
    }

    difference_type operator-(const RandomAccessIterator& other) const {
        return ptr_ - other.ptr_;
    }

    bool operator<(const RandomAccessIterator& other) const {
        return ptr_ < other.ptr_;
    }
    bool operator>(const RandomAccessIterator& other) const {
        return ptr_ > other.ptr_;
    }
    bool operator>=(const RandomAccessIterator& other) const {
        return !(*this < other);
    }
    bool operator<=(const RandomAccessIterator& other) const {
        return !(*this > other);
    }

    reference operator*() const { return *ptr_; }
    pointer operator->() const { return ptr_; } 
    reference operator[](difference_type n) const { return *(ptr_ + n); }

    bool operator==(const RandomAccessIterator& other) const {
        return ptr_ == other.ptr_;
    }
    bool operator!=(const RandomAccessIterator& other) const {
        return ptr_ != other.ptr_;
    }

private:
    pointer ptr_;
};

template<typename T>
RandomAccessIterator<T> operator+(typename RandomAccessIterator<T>::difference_type n,
                                  const RandomAccessIterator<T>& it) {
    return it + n;
}
