#include <iostream>
#include <cstdlib>
#include <cstring>

struct TwoStr {
    TwoStr() = default;
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
        if (size_ >= capacity_) { Expand(); }
        size_t idx = size_;
        size_++;
        data_[idx].key = val;
        return data_[idx].value; 
    }

    friend std::ostream& operator<<(std::ostream& os, const Int2StrDict& dict) {
        os << '{';
        for (size_t i = 0; i < dict.size_; ++i) {
            if (i == dict.size_ - 1) {
                os << dict.data_[i].key << " : " 
                   << static_cast<char*>(dict.data_[i].value.data);
            } else {
                os << dict.data_[i].key << " : " 
                   << static_cast<char*>(dict.data_[i].value.data) 
                   << ", ";
            }
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

std::ostream& Test(std::ostream& os) {
    Int2StrDict d;
    d[1] = "aa";
    d[2] = "bb";
    d[3] = "cc";

    std::cout << d << std::endl; // {1 : aa, 2 : bb, 3 : cc};

    std::cout << d["aa"] << std::endl; // 1;
    d["aa"] = 10;

    std::cout << d << std::endl; // {2 : bb, 3 : cc, 10 : aa};

    Int2StrDict d2 = d;
    std::cout << d2 << std::endl; // {2 : bb, 3 : cc, 10 : aa};
    std::cout << d2 << std::endl; // {2 : bb, 10 : aa};

    return os;
}