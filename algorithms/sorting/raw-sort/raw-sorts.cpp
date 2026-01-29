#include "sorts.h"

#include <algorithm>
#include <utility>

namespace algs {

namespace detail {

template <typename T>
void Merge(T* result, const T* left, std::size_t left_size,
           const T* right, std::size_t right_size) {
    std::size_t i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            result[k++] = left[i++];
        } else {
            result[k++] = right[j++];
        }
    }
    while (i < left_size) result[k++] = left[i++];
    while (j < right_size) result[k++] = right[j++];
}

template <typename T>
int PartitionLomuto(T* arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
int PartitionHoare(T* arr, int low, int high) {
    T pivot = arr[low];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do { ++i; } while (arr[i] < pivot);
        do { --j; } while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }
        std::swap(arr[i], arr[j]);
    }
}

template <typename T>
int PartitionRandomLomuto(T* arr, int low, int high) {
    int random_idx = low + std::rand() % (high - low + 1);
    std::swap(arr[random_idx], arr[high]);
    return PartitionLomuto(arr, low, high);
}

}  // namespace detail


// Public implementations
template <typename T>
void InsertSort(T* array, int n, int& comparison_count) {
    comparison_count = 0;
    for (int i = 1; i < n; ++i) {
        T key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key) {
            ++comparison_count;
            array[j + 1] = array[j];
            --j;
        }
        if (j >= 0) ++comparison_count;  // final failed comparison
        array[j + 1] = key;
    }
}

template <typename T>
void BubbleSort(T* arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

template <typename T>
void SelectionSort(T* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(arr[i], arr[min_idx]);
        }
    }
}

template <typename T>
void MergeSort(T* arr, std::size_t size) {
    if (size <= 1) return;

    std::size_t mid = size / 2;
    T* left = new T[mid];
    T* right = new T[size - mid];

    for (std::size_t i = 0; i < mid; ++i) left[i] = arr[i];
    for (std::size_t i = mid; i < size; ++i) right[i - mid] = arr[i];

    MergeSort(left, mid);
    MergeSort(right, size - mid);

    detail::Merge(arr, left, mid, right, size - mid);

    delete[] left;
    delete[] right;
}

template <typename T>
void QuickSort(T* arr, int start, int end, PartitionType type) {
    if (start >= end) return;

    int pivot;
    switch (type) {
        case PartitionType::kHoare:
            pivot = detail::PartitionHoare(arr, start, end);
            QuickSort(arr, start, pivot, type);
            QuickSort(arr, pivot + 1, end, type);
            break;

        case PartitionType::kLomuto:
            pivot = detail::PartitionLomuto(arr, start, end);
            QuickSort(arr, start, pivot - 1, type);
            QuickSort(arr, pivot + 1, end, type);
            break;

        case PartitionType::kRandom:
        default:
            pivot = detail::PartitionRandomLomuto(arr, start, end);
            QuickSort(arr, start, pivot - 1, type);
            QuickSort(arr, pivot + 1, end, type);
            break;
    }
}

template <typename T>
bool IsSorted(const T* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

}  // namespace algs