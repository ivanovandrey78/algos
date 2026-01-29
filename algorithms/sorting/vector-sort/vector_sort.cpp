#include "vector_sort.h"

#include <algorithm>
#include <cstdlib>
#include <utility>
#include <vector>

namespace algs {

namespace detail {

template <typename T>
void Merge(std::vector<T>& result,
           const std::vector<T>& left,
           const std::vector<T>& right) {
    std::size_t i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            result[k++] = left[i++];
        } else {
            result[k++] = right[j++];
        }
    }
    while (i < left.size()) result[k++] = left[i++];
    while (j < right.size()) result[k++] = right[j++];
}

template <typename T>
int PartitionLomuto(std::vector<T>& vec, int low, int high) {
    T pivot = vec[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (vec[j] <= pivot) {
            ++i;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[high]);
    return i + 1;
}

template <typename T>
int PartitionHoare(std::vector<T>& vec, int low, int high) {
    T pivot = vec[low];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do { ++i; } while (vec[i] < pivot);
        do { --j; } while (vec[j] > pivot);

        if (i >= j) {
            return j;
        }
        std::swap(vec[i], vec[j]);
    }
}

template <typename T>
int PartitionRandomLomuto(std::vector<T>& vec, int low, int high) {
    int random_idx = low + std::rand() % (high - low + 1);
    std::swap(vec[random_idx], vec[high]);
    return PartitionLomuto(vec, low, high);
}

}  // namespace detail

// Public implementations
template <typename T>
void InsertSort(std::vector<T>& vec, int& comparison_count) {
    comparison_count = 0;
    for (int i = 1; i < static_cast<int>(vec.size()); ++i) {
        T key = vec[i];
        int j = i - 1;

        while (j >= 0 && vec[j] > key) {
            ++comparison_count;
            vec[j + 1] = vec[j];
            --j;
        }
        if (j >= 0) ++comparison_count;
        vec[j + 1] = key;
    }
}

template <typename T>
void BubbleSort(std::vector<T>& vec) {
    std::size_t n = vec.size();
    for (std::size_t i = 0; i + 1 < n; ++i) {
        bool swapped = false;
        for (std::size_t j = 0; j + 1 < n - i; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

template <typename T>
void SelectionSort(std::vector<T>& vec) {
    std::size_t n = vec.size();
    for (std::size_t i = 0; i + 1 < n; ++i) {
        std::size_t min_idx = i;
        for (std::size_t j = i + 1; j < n; ++j) {
            if (vec[j] < vec[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(vec[i], vec[min_idx]);
        }
    }
}

template <typename T>
void MergeSort(std::vector<T>& vec) {
    std::size_t n = vec.size();
    if (n <= 1) return;

    std::size_t mid = n / 2;
    std::vector<T> left(vec.begin(), vec.begin() + mid);
    std::vector<T> right(vec.begin() + mid, vec.end());

    MergeSort(left);
    MergeSort(right);

    detail::Merge(vec, left, right);
}

template <typename T>
void QuickSort(std::vector<T>& vec, PartitionType type) {
    int n = static_cast<int>(vec.size());
    if (n <= 1) return;

    struct Recursion {
        int low, high;
    };
    // Используем явный стек вместо рекурсии (чтобы избежать переполнения на больших векторах)
    std::vector<Recursion> stack;
    stack.push_back({0, n - 1});

    while (!stack.empty()) {
        int low = stack.back().low;
        int high = stack.back().high;
        stack.pop_back();

        if (low >= high) continue;

        int pivot;
        switch (type) {
            case PartitionType::kHoare:
                pivot = detail::PartitionHoare(vec, low, high);
                stack.push_back({low, pivot});
                stack.push_back({pivot + 1, high});
                break;

            case PartitionType::kLomuto:
                pivot = detail::PartitionLomuto(vec, low, high);
                stack.push_back({low, pivot - 1});
                stack.push_back({pivot + 1, high});
                break;

            case PartitionType::kRandom:
            default:
                pivot = detail::PartitionRandomLomuto(vec, low, high);
                stack.push_back({low, pivot - 1});
                stack.push_back({pivot + 1, high});
                break;
        }
    }
}

template <typename T>
bool IsSorted(const std::vector<T>& vec) {
    for (std::size_t i = 0; i + 1 < vec.size(); ++i) {
        if (vec[i] > vec[i + 1]) {
            return false;
        }
    }
    return true;
}

}  // namespace algs