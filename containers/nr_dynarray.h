#pragma once

#include "my_config.h"

#include <iostream>
#include <cstdlib>

template<typename T>
class CDynamicArray {
public:
    CDynamicArray() = default;

    explicit CDynamicArray(size_t capacity)
        : capacity_(capacity),
          data_(new T[capacity_]) 
          {}

    ~CDynamicArray() { delete[] data_; }

    CDynamicArray(const CDynamicArray& other) 
        : capacity_(other.capacity_),
          data_(new T[other.capacity_]),
          size_(other.size_) {
        for (size_t i = 0; i < other.size_; ++i) {
            data_[i] = other.data_[i];
        }
        std::cout << "CopyCtr" << std::endl;
    }

    CDynamicArray(CDynamicArray&& other) noexcept 
        : capacity_(other.capacity_),
          data_(other.data_),
          size_(other.size_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        std::cout << "MoveCtr" << std::endl;
    }

    CDynamicArray& operator=(CDynamicArray other) {
        contcon::Swap(capacity_, other.capacity_);
        contcon::Swap(data_, other.data_);
        contcon::Swap(size_, other.size_);
        return *this;
    }
    
    void PushBack(const T& value) {
        if (size_ >= capacity_) { Expand(); }
        data_[size_++] = value;
    }

    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("");
        }
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("");
        }
        return data_[index];
    }
    
    size_t GetSize() const { return size_; }
    size_t GetCapacity() const { return capacity_; }

    bool IsEmpty() const { return size_ == 0; }
    
    friend std::ostream& operator<<(std::ostream& os, const CDynamicArray<T>& arr) {
        os << '[';
        for (size_t i = 0; i < arr.size_; ++i) {
            if (i > 0) { os << ", "; }
            os << arr.data_[i];
        }
        os << ']';
        return os;
    }

private:
    void Expand() {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    size_t capacity_ = 0;
    T* data_ = nullptr;
    size_t size_ = 0;
};