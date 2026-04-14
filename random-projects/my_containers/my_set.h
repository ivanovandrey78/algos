#pragma once

#include "my_config.h"

#include <iostream>
#include <cstdlib>

template<typename T>
struct Node {
    T* data = nullptr;
    Node* next = nullptr;
    Node();
    Node(T* value, Node* next_element) 
        : data(value),
          next(next_element)
          {}
};

template<typename T>
class CSet {
public:
    CSet() = default;

    CSet(size_t capacity) 
        : capacity_(capacity),
          data_(new T[capacity_])
          {}

    virtual ~CSet() { delete[] data_; }

    CSet(const CSet& other) 
        : capacity_(other.capacity_),
          data_(new T[capacity_]),
          size_(other.size_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    CSet(CSet&& other)
        : capacity_(other.capacity_),
          data_(other.data_),
          size_(other.size_) {
        other.capacity_ = 0;
        other.data_ = nullptr;
        other.size_ = 0;
    }

    CSet& operator=(CSet other) {
        contcon::Swap(capacity_, other.capacity_);
        contcon::Swap(data_, other.data_);
        contcon::Swap(size_, other.size_);
        return *this;
    }

    size_t GetSize() const { return size_; }
    size_t GetCapacity() const { return capacity_; }

    void Erase() {}

    void Insert(const T& val) {}

    bool Contains(const T& val) {
        for (size_t i = 0; i < size_; ++i) {
            
        }
    }

    friend std::ostream& operator<<(std::ostream& os, CSet& set) {
        for (size_t i = 0; i < set.size_; ++i) {
            
        }
    }

private:
    void Expand() {
        size_t new_cap = (capacity_ == 0) 
                         ? 1 : capacity_ * 2;
        T* new_data = new T[new_cap];
        if (!new_data) { throw std::bad_alloc(); }
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

    size_t capacity_ = 0;
    T* data_ = nullptr;
    size_t size_ = 0;
};