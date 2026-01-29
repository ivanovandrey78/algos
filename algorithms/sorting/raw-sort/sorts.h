#pragma once

#include <cstddef>
#include <cstdlib>

namespace algs {

enum class PartitionType {
    kHoare,
    kRandom,  // Hoare with random pivot
    kLomuto,
};

// Sorting Algorithms (templated)
template <typename T>
void InsertSort(T* arr, int n, int& comparison_count);

template <typename T>
void BubbleSort(T* arr, int size);

template <typename T>
void SelectionSort(T* arr, int n);

template <typename T>
void MergeSort(T* arr, std::size_t size);

template <typename T>
void QuickSort(T* arr, int start, int end,
               PartitionType type = PartitionType::kRandom);

template <typename T>
void HeapSort(T* arr, int n);

// Helper functions
template <typename T>
bool IsSorted(const T* arr, int n);

// Internal helpers
namespace detail {

template <typename T>
void Merge(T* result, const T* left, std::size_t left_size,
           const T* right, std::size_t right_size);

template <typename T>
int PartitionLomuto(T* arr, int low, int high);

template <typename T>
int PartitionHoare(T* arr, int low, int high);

template <typename T>
int PartitionRandomLomuto(T* arr, int low, int high);

}  // namespace detail

}  // namespace algs