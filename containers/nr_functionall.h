#pragma once

#include <cstdlib>
#include <functional>
#include <memory>
#include <type_traits>

template<typename>
class Functionall;

template<typename R, typename... Args>
class Functionall<R(Args...)> {
public:
    Functionall() noexcept = default;
    Functionall(std::nullptr_t) noexcept : callable_(nullptr) {}

    template<typename F,
             typename = std::enable_if_t<
                 !std::is_same_v<std::decay_t<F>, Functionall>>>
    Functionall(F&& f)
        : callable_(
            std::make_unique<Callable<std::decay_t<F>>>(
                std::forward<F>(f)))
    {}

    Functionall(const Functionall& other)
        : callable_(other.callable_ ? other.callable_->Clone() : nullptr)
    {}

    Functionall(Functionall&& other) noexcept = default;

    Functionall& operator=(const Functionall& other) {
        if (this != &other) {
            callable_ = other.callable_ ? other.callable_->Clone() : nullptr;
        }
        return *this;
    }

    Functionall& operator=(Functionall&& other) noexcept = default;

    Functionall& operator=(std::nullptr_t) noexcept {
        callable_.reset();
        return *this;
    }

    template<typename F,
             typename = std::enable_if_t<
                 !std::is_same_v<std::decay_t<F>, Functionall>>>
    Functionall& operator=(F&& f) {
        callable_ = std::make_unique<Callable<std::decay_t<F>>>(
            std::forward<F>(f));
        return *this;
    }

    R operator()(Args... args) const {
        if (!callable_) {
            throw std::bad_function_call();
        }
        return callable_->Invoke(std::forward<Args>(args)...);
    }

    explicit operator bool() const noexcept {
        return callable_ != nullptr;
    }

    bool operator==(std::nullptr_t) const noexcept {
        return !callable_;
    }

    bool operator!=(std::nullptr_t) const noexcept {
        return !!callable_;
    }

private:
    class ICallable {
    public:
        virtual ~ICallable() = default;
        virtual R Invoke(Args... args) const = 0;
        virtual std::unique_ptr<ICallable> Clone() const = 0;
    };

    template<typename F>
    class Callable final : public ICallable {
    public:
        Callable(const F& f) : functor_(f) {}
        Callable(F&& f) : functor_(std::move(f)) {}
        R Invoke(Args... args) const override {
            return functor_(std::forward<Args>(args)...);
        }
        std::unique_ptr<ICallable> Clone() const override {
            return std::make_unique<Callable<F>>(functor_);
        }
        F functor_;
    };

    std::unique_ptr<ICallable> callable_ = nullptr;
};