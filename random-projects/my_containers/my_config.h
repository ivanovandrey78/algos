#pragma once

namespace contcon {

template<typename T>
void Swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

}  // namespace contcon