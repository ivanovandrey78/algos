#pragma once 

#include "my_config.h"

#include <iostream>
#include <cstdlib>
#include <cstring>

class String {
public:
    String() 
        : capacity_(1), 
          data_(new char[1]), 
          size_(0) {
        data_[0] = '\0';
    }

    explicit String(size_t capacity)
        : capacity_(std::max(size_t(1), capacity)),
          data_(new char[capacity_]),
          size_(0) {
        data_[0] = '\0';
    }

    String(const char* s) {
        size_t len = strlen(s);
        capacity_ = std::max(len + 1, size_t(1));
        data_ = new char[capacity_];
        size_ = len;
        strcpy(data_, s);
    }

    ~String() { delete[] data_; }

    String(const String& other) 
        : capacity_(other.capacity_),
          data_(new char[other.capacity_]),
          size_(other.size_) {
        strcpy(data_, other.data_);
    }

    String(String&& other) noexcept 
        : capacity_(other.capacity_),
          data_(other.data_),
          size_(other.size_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    String& operator=(String other) {
        contcon::Swap(capacity_, other.capacity_);
        contcon::Swap(data_, other.data_);
        contcon::Swap(size_, other.size_);
        return *this;
    }

    String& operator+=(const String& other) {
        while (capacity_ < other.size_ + size_) {
            Expand();
        }
        *this += other.data_;
        size_ += other.size_;
        return *this;
    }

    String& operator+=(const char* s) {
        while (capacity_ < strlen(s) + size_) {
            Expand();
        }
        for (size_t i = size_; i <= strlen(s) + size_; ++i) {
            data_[i] = s[i - size_];
        }
        size_ += strlen(s);
        return *this;
    }

    String& operator+=(char letter) {
        PushBack(letter);
        return *this;
    }
    
    void PushBack(char value) {
        if (size_  + 1 >= capacity_) { Expand(); }
        data_[size_] = value;
        data_[++size_] = '\0';
    }

    char& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("");
        }
        return data_[index];
    }

    const char& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("");
        }
        return data_[index];
    }
    
    size_t GetSize() const { return size_; }
    size_t GetCapacity() const { return capacity_; }

    bool IsEmpty() const { return size_ == 0; }
    
    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.data_;
        return os;
    }

private:
    void Expand() {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        char* new_data = new char[new_capacity];
        for (size_t i = 0; i <= size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    size_t capacity_ = 0;
    char* data_ = nullptr;
    size_t size_ = 0;
};

inline String operator+(const String& lhs, const String& rhs) {
    String s3(lhs);
    s3 += rhs;
    return s3;
}

inline String operator+(const String& lhs, char letter) {
    String s3(lhs);
    s3 += letter;
    return s3;
}

// bool operator==(const String& lhs, const String& rhs) {}
// bool operator!=(const String& lhs, const String& rhs) {}