#pragma once 

#include <iostream>
#include <cstdlib>
#include <cstring>

struct TwoStr {
    TwoStr& operator=(const char* other) {
        if (strlen(other) > 2) {
            throw std::out_of_range("");
        }
        strcpy(data, other);
        return *this;
    }
    char data[3];
};

struct Ceil {
    int key = 0;
    TwoStr value;
};

class Int2StrDict{
public:
    Int2StrDict() = default;

    Int2StrDict(const Int2StrDict& other) 
        : capacity_(other.capacity_),
          data_(new Ceil[capacity_]),
          size_(other.size_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    Int2StrDict& operator=(Int2StrDict other) {
        std::swap(capacity_, other.capacity_);        
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        return *this;
    }

    const int& operator[](const char* val) const {
        for (size_t i = 0; i < size_; ++i) {
            if (strcmp(data_[i].value.data, val) == 0) {
                return data_[i].key;
            }
        }
    }

    int& operator[](const char* val) {
        for (size_t i = 0; i < size_; ++i) {
            if (strcmp(data_[i].value.data, val) == 0) {
                return data_[i].key;
            }
        }
    }

    TwoStr& operator[](int val) {
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i].key == val) {
                return data_[i].value;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Int2StrDict& dict) {
        os << '{';
        for (size_t i = 0; i < dict.size_; ++i) {
            os << dict.data_[i].key << " : " << static_cast<char*>(dict.data_[i].value.data);
        }
        os << '}';
        return os;
    }

private:
    void Expand() {
        size_t new_cap = (capacity_ == 0) 
                         ? 1 : capacity_ * 2;
        Ceil* new_data = new Ceil[new_cap];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        capacity_ = new_cap;
        data_ = new_data;
    }

    size_t capacity_ = 0;
    Ceil* data_ = nullptr;
    size_t size_ = 0;
}; // std deprecated