#pragma once

#include <iostream>

namespace algs {

enum class PartitionType { 
    kPartitionHoare,
    kPartitionRandom, // Based on Hoare Partition
    kPartitionLomuto,
};

// Sorts
void insertSort(int* array, int n,int& c);
void bubbleSort(int* arr, int asize);
void selectionSort(int* a,int n);
void mergeSort(int* a,size_t sizeA);
void quickSort(int* a, int start, int end, PartitionType partType = PartitionType::kPartitionRandom);

// Helper functions for QuickSort
int PartitionLomuto(int* a, int start, int end);
int PartitionHoare(int* arr, int low, int high);
int partition(int* arr, int low, int high);

// Heap 
void heapSort(int* arr, int n);

// Helpers for sorts 
bool isSorted(int* arr,int n);
void merge(int* result, int* a, size_t sizeA, int* b, size_t sizeB);

} // namespace algs 