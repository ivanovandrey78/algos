#pragma once

#include <iostream>

namespace algs {

enum class PartitionType { 
    kPartitionHoare,
    kPartitionRandom, // Based on Hoare Partition
    kPartitionLomuto,
};

// Sorts
void InsertSort(int* array, int n,int& c);
void BubbleSort(int* arr, int asize);
void SelectionSort(int* a,int n);
void MergeSort(int* a,size_t sizeA);
void QuickSort(int* a, int start, int end, PartitionType partType = PartitionType::kPartitionRandom);

// Helper functions for QuickSort
int PartitionLomuto(int* a, int start, int end);
int PartitionHoare(int* arr, int low, int high);
int Partition(int* arr, int low, int high);

// Heap 
void HeapSort(int* arr, int n);

// Helpers for sorts 
bool IsSorted(int* arr,int n);
void Merge(int* result, int* a, size_t sizeA, int* b, size_t sizeB);

} // namespace algs 