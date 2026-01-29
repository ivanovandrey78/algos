#pragma once

#include <cstddef>
#include <vector>

namespace algs {

enum class PartitionType {
    kHoare,
    kRandom,
    kLomuto,
};

// Vector-based Sorting Algorithms
template <typename T>
void InsertSort(std::vector<T>& vec, int& comparison_count);

template <typename T>
void BubbleSort(std::vector<T>& vec);

template <typename T>
void SelectionSort(std::vector<T>& vec);

template <typename T>
void MergeSort(std::vector<T>& vec);

template <typename T>
void QuickSort(std::vector<T>& vec,
               PartitionType type = PartitionType::kRandom);

// Helper functions
template <typename T>
bool IsSorted(const std::vector<T>& vec);

// Internal helpers
namespace detail {

template <typename T>
void Merge(std::vector<T>& result,
           const std::vector<T>& left,
           const std::vector<T>& right);

template <typename T>
int PartitionLomuto(std::vector<T>& vec, int low, int high);

template <typename T>
int PartitionHoare(std::vector<T>& vec, int low, int high);

template <typename T>
int PartitionRandomLomuto(std::vector<T>& vec, int low, int high);

}  // namespace detail

}  // namespace algs