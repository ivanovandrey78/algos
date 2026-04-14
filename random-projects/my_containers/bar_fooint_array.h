#pragma once

#include <iostream>
#include <utility>

class Foo {};
class Bar {};

template <unsigned SIZE> 
class BarFooIntArray {
public: 
    enum ElementType {
        kNone,
        kFooType,
        kBarType,
        kIntType
    };

private:
    struct Proxy {
        ElementType type = kNone;
        union {
            int int_data;
            Foo foo_data;
            Bar bar_data;
        } data;

        Proxy() : type(kNone) {}
        
        ~Proxy() {
            if (type == kFooType) {
                data.foo_data.~Foo();
            } else if (type == kBarType) {
                data.bar_data.~Bar();
            }
        }

        bool IsBar() const { return type == kBarType; }
        bool IsFoo() const { return type == kFooType; }
        bool IsInt() const { return type == kIntType; }
        
        Proxy& operator=(const Bar& bar) {
            if (type == kFooType) {
                data.foo_data.~Foo();
            } else if (type == kBarType) {
                data.bar_data.~Bar();
            }
            
            new (&data.bar_data) Bar(bar);
            type = kBarType;
            return *this;
        }
        
        Proxy& operator=(const Foo& foo) {
            if (type == kFooType) {
                data.foo_data.~Foo();
            } else if (type == kBarType) {
                data.bar_data.~Bar();
            }
            
            new (&data.foo_data) Foo(foo);
            type = kFooType;
            return *this;
        }
        
        Proxy& operator=(int value) {
            if (type == kFooType) {
                data.foo_data.~Foo();
            } else if (type == kBarType) {
                data.bar_data.~Bar();
            }
            
            data.int_data = value;
            type = kIntType;
            return *this;
        }
        
        Proxy& operator=(const Proxy& other) {
            if (this != &other) {
                if (type == kFooType) {
                    data.foo_data.~Foo();
                } else if (type == kBarType) {
                    data.bar_data.~Bar();
                }
                
                type = other.type;
                switch (type) {
                    case kFooType:
                        new (&data.foo_data) Foo(other.data.foo_data);
                        break;
                    case kBarType:
                        new (&data.bar_data) Bar(other.data.bar_data);
                        break;
                    case kIntType:
                        data.int_data = other.data.int_data;
                        break;
                    case kNone:
                        break;
                }
            }
            return *this;
        }
        
        operator Bar() const {
            if (type != kBarType) {
                throw std::bad_cast();
            }
            return data.bar_data;
        }
        
        operator Foo() const {
            if (type != kFooType) {
                throw std::bad_cast();
            }
            return data.foo_data;
        }
        
        operator int() const {
            if (type != kIntType) {
                throw std::bad_cast();
            }
            return data.int_data;
        }
    };

public:
    BarFooIntArray() : size_(SIZE), data_(new Proxy[size_]) {}

    ~BarFooIntArray() { 
        delete[] data_; 
    }

    BarFooIntArray(const BarFooIntArray& other) 
        : size_(other.size_), data_(new Proxy[other.size_]) {
        for (unsigned i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    BarFooIntArray& operator=(BarFooIntArray other) {
        swap(*this, other);
        return *this;
    }

    Proxy& operator[](unsigned idx) {
        if (idx >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[idx];
    }
    
    const Proxy& operator[](unsigned idx) const {
        if (idx >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[idx];
    }

    unsigned GetSize() const { return size_; }
    
    friend void swap(BarFooIntArray& first, BarFooIntArray& second) noexcept {
        std::swap(first.data_, second.data_);
        std::swap(first.size_, second.size_);
    }

private:
    unsigned size_;
    Proxy* data_;
};

int Test() {
    BarFooIntArray<3> arr;

    arr[0] = Bar{};
    arr[1] = Foo{};
    arr[2] = 10;

    std::cout << arr[0].IsBar() << arr[0].IsFoo() << arr[0].IsInt() << std::endl; // 100
    std::cout << arr[1].IsBar() << arr[1].IsFoo() << arr[1].IsInt() << std::endl; // 010
    std::cout << arr[2].IsBar() << arr[2].IsFoo() << arr[2].IsInt() << std::endl; // 001

    try {
        Bar b = arr[0];
        int i = arr[2];
        std::cout << i << std::endl; // 10
    } catch (const std::bad_cast& e) {
        std::cerr << "Bad cast: " << e.what() << std::endl;
    }
    
    BarFooIntArray<3> arr2 = arr;
    std::cout << "Copy test: " << arr2[2].IsInt() << std::endl; // 1
    
    BarFooIntArray<3> arr3;
    arr3 = arr;
    std::cout << "Assignment test: " << arr3[1].IsFoo() << std::endl; // 1

    return 0;
}