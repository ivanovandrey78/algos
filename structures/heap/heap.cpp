#include "heap.h"
#include <algorithm>
#include <stdexcept>

// HEAP FUNCTIONS
void SiftDown(int* arr, int size, int i, HeapType type) {
    while (2 * i + 1 < size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int target = i;
        
        switch (type) {
            case HeapType::kMinHeap:
                if (left < size && arr[left] < arr[target]) target = left;
                if (right < size && arr[right] < arr[target]) target = right;
                break;
            case HeapType::kMaxHeap:
                if (left < size && arr[left] > arr[target]) target = left;
                if (right < size && arr[right] > arr[target]) target = right;
                break;
        }
        
        if (target == i) break;
        std::swap(arr[i], arr[target]);
        i = target;
    }
}

void SiftDown(int* arr, int size, int i) {
    HeapType type = DetectHeapType(arr, size);
    SiftDown(arr, size, i, type);
}

void SiftUp(int* arr, int size, int i, HeapType type) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        bool should_swap = false;
        
        switch (type) {
            case HeapType::kMinHeap:
                should_swap = (arr[i] < arr[parent]);
                break;
            case HeapType::kMaxHeap:
                should_swap = (arr[i] > arr[parent]);
                break;
        }
        
        if (!should_swap) break;
        std::swap(arr[i], arr[parent]);
        i = parent;
    }
}

void SiftUp(int* arr, int size, int i) {
    HeapType type = DetectHeapType(arr, size);
    SiftUp(arr, size, i, type);
}

void BuildHeap(int* arr, int size, HeapType type) {
    for (int i = size / 2 - 1; i >= 0; i--) {  // Исправлено: начинаем с size/2 - 1
        SiftDown(arr, size, i, type);
    }
}

void BuildHeap(int* arr, int size) {
    HeapType type = DetectHeapType(arr, size);
    BuildHeap(arr, size, type);
}

bool IsHeap(int* arr, int size, HeapType type) {
    for (int i = 0; i < size / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        switch (type) {
            case HeapType::kMinHeap:
                if (left < size && arr[i] > arr[left]) return false;
                if (right < size && arr[i] > arr[right]) return false;
                break;
            case HeapType::kMaxHeap:
                if (left < size && arr[i] < arr[left]) return false;
                if (right < size && arr[i] < arr[right]) return false;
                break;
        }
    }
    return true;
}

bool IsHeap(int* arr, int size) {
    HeapType type = DetectHeapType(arr, size);
    return IsHeap(arr, size, type);
}

HeapType DetectHeapType(int* arr, int size) {
    if (size < 2) return HeapType::kMaxHeap;

    int max_count = 0, min_count = 0;
    
    for (int i = 0; i < size / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < size) {
            if (arr[i] >= arr[left]) max_count++;
            if (arr[i] <= arr[left]) min_count++;
        }
        if (right < size) {
            if (arr[i] >= arr[right]) max_count++;
            if (arr[i] <= arr[right]) min_count++;
        }
    }
    
    return (max_count >= min_count) ? HeapType::kMaxHeap : HeapType::kMinHeap;
}

void heapSort(int* arr, int size, HeapType type) {
    BuildHeap(arr, size, type);
    
    for (int i = size - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        SiftDown(arr, i, 0, type);
    }
}

void heapSort(int* arr, int size) {
    HeapType type = DetectHeapType(arr, size);
    heapSort(arr, size, type);
}

// KATALAN NUMBER. (Heap to Brackets)
std::string heapToBracketSequence(int* heap, int size, int index) {
    if (index >= size) {
        return "()";  
    }
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    
    std::string left_str = heapToBracketSequence(heap, size, left_child);
    std::string right_str = heapToBracketSequence(heap, size, right_child);
    
    return "(" + left_str + ")" + std::to_string(heap[index]) + "(" + right_str + ")";
}

// Alternative - without values
std::string heapToPureBrackets(int* heap, int size, int index) {
    if (index >= size) {
        return "()";
    }
    
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    
    std::string left_str = heapToPureBrackets(heap, size, left_child);
    std::string right_str = heapToPureBrackets(heap, size, right_child);
    
    return "(" + left_str + right_str + ")";
}

// PRIORITY QUEUE IMPLEMENTATION 
PriorityQueue::PriorityQueue(HeapType type) 
    : capacity_(10), size_(0), type_(type) {
    data_ = new int[capacity_];
}

PriorityQueue::PriorityQueue(int* arr, int arr_size, HeapType type)
    : capacity_(std::max(arr_size, 10)), size_(arr_size), type_(type) {
    data_ = new int[capacity_];
    for (int i = 0; i < size_; i++) {
        data_[i] = arr[i];
    }
    BuildHeap(data_, size_, type_);
}

PriorityQueue::~PriorityQueue() {
    delete[] data_;
}

PriorityQueue::PriorityQueue(const PriorityQueue& other)
    : capacity_(other.capacity_), size_(other.size_), type_(other.type_) {
    data_ = new int[capacity_];
    for (int i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
    }
}

PriorityQueue& PriorityQueue::operator=(const PriorityQueue& other) {
    if (this != &other) {
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        type_ = other.type_;
        data_ = new int[capacity_];
        for (int i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

void PriorityQueue::Resize(int new_capacity) {
    int* new_data = new int[new_capacity];
    for (int i = 0; i < size_; i++) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

void PriorityQueue::SiftUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        bool should_swap = false;
        
        switch (type_) {
            case HeapType::kMinHeap:
                should_swap = (data_[i] < data_[parent]);
                break;
            case HeapType::kMaxHeap:
                should_swap = (data_[i] > data_[parent]);
                break;
        }
        
        if (!should_swap) break;
        std::swap(data_[i], data_[parent]);
        i = parent;
    }
}

void PriorityQueue::SiftDown(int i) {
    while (2 * i + 1 < size_) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int target = i;
        
        switch (type_) {
            case HeapType::kMinHeap:
                if (data_[left] < data_[target]) target = left;
                if (right < size_ && data_[right] < data_[target]) target = right;
                break;
            case HeapType::kMaxHeap:
                if (data_[left] > data_[target]) target = left;
                if (right < size_ && data_[right] > data_[target]) target = right;
                break;
        }
        
        if (target == i) break;
        std::swap(data_[i], data_[target]);
        i = target;
    }
}

void PriorityQueue::Push(int value) {
    if (size_ == capacity_) {
        Resize(capacity_ * 2);
    }
    
    data_[size_] = value;
    SiftUp(size_);
    size_++;
}

int PriorityQueue::Pop() {
    if (Empty()) {
        throw std::runtime_error("PriorityQueue is empty");
    }
    
    int result = data_[0];
    data_[0] = data_[size_ - 1];
    size_--;
    
    if (size_ > 0) {
        SiftDown(0);
    }
    
    return result;
}

int PriorityQueue::Top() const {
    if (Empty()) {
        throw std::runtime_error("PriorityQueue is empty");
    }
    return data_[0];
}

bool PriorityQueue::Empty() const {
    return size_ == 0;
}

int PriorityQueue::Size() const {
    return size_;
}

int PriorityQueue::Capacity() const {
    return capacity_;
}

void PriorityQueue::Clear() {
    size_ = 0;
}

HeapType PriorityQueue::GetType() const {
    return type_;
}

void PriorityQueue::Print() const {
    std::cout << "PriorityQueue (";
    std::cout << (type_ == HeapType::kMaxHeap ? "MaxHeap" : "MinHeap");
    std::cout << "): [";
    for (int i = 0; i < size_; i++) {
        std::cout << data_[i];
        if (i < size_ - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

bool PriorityQueue::Validate() const {
    return IsHeap(data_, size_, type_);
}