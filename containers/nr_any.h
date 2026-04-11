#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>

class CAny {
public: 
    CAny() = default;

    template<typename T,
             typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, CAny>>>
    CAny(T&& v) 
        : data_ptr_(new Holder<std::decay_t<T>>(std::forward<T>(v)))
        {}

    CAny(const CAny& other)
        : data_ptr_(other.data_ptr_ ? other.data_ptr_->Copy() : nullptr)
        {}

    CAny& operator=(const CAny& other) {
        if (this != &other) {
            data_ptr_.reset();
            if (other.data_ptr_) {
                data_ptr_ = other.data_ptr_->Copy();
            }
        }
        return *this;
    }

    template<typename T>
    CAny& operator=(T&& v) {
        data_ptr_.reset();
        data_ptr_ = std::make_unique<Holder<std::decay_t<T>>>(std::forward<T>(v));
        return *this;
    }

    bool HasValue() const { return data_ptr_ == nullptr; }
    const std::type_info& Type() const { return data_ptr_->Type(); }

    friend std::ostream& operator<<(std::ostream& os, CAny* a) {
        a->data_ptr_->Print();
        return os;
    }

    template<typename T>
    friend T* AnyCast(CAny* a) {
        if (!a || !a->data_ptr_) return nullptr;
        if (a->data_ptr_->Type() != typeid(T)) return nullptr;
        return &static_cast<Holder<T>*>(a->data_ptr_.get())->data;
    }

    template<typename T>
    friend T* AnyCast(const CAny* a) {
        if (!a || !a->data_ptr_) return nullptr;
        if (a->data_ptr_->Type() != typeid(T)) return nullptr;
        return &static_cast<const Holder<T>*>(a->data_ptr_.get())->data;
    }

    template<typename T>
    friend T AnyCast(CAny& a) {
        T* p = AnyCast<T>(&a);
        if (!p) throw std::bad_cast();
        return *p;
    }

    template<typename T>
    friend T AnyCast(const CAny& a) {
        const T* p = AnyCast<T>(&a);
        if (!p) throw std::bad_cast();
        return *p;
    }

private:
    struct IHolder {
        virtual ~IHolder() = default;
        virtual const std::type_info& Type() const = 0;
        virtual std::unique_ptr<IHolder> Copy() const = 0;
        virtual void Print() const = 0;
    };

    template<typename T>
    struct Holder final : public IHolder {
        Holder(T&& v) : data(v) {}
        Holder(const T& v) : data(v) {}
        const std::type_info& Type() const override {
            return  typeid(T);
        }
        std::unique_ptr<IHolder> Copy() const override {
            return std::make_unique<Holder>(data);
        }
        void Print() const override {
            std::cout << data << std::endl;
        }
        T data;
    };

    std::unique_ptr<IHolder> data_ptr_ = nullptr;
};