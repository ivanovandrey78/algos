#pragma once

#include <exception>
#include <iostream>

struct Node {
    long long data;
    Node* next;
    Node(long long val) : data(val), next(nullptr) {}
};

class Queue {
private:
    Node* front_;
    Node* end_;
    size_t size_;
    
public:
    Queue() 
        : front_(nullptr), 
          end_(nullptr),
          size_(0) {}
          
    ~Queue() {
        while (!IsEmpty()) { Pop(); } 
    }

    void PushBack(long long value) {
        Node* newNode = new Node(value);
        
        if (IsEmpty()) {
            front_ = end_ = newNode;
        } else {
            end_->next = newNode;
            end_ = newNode;
        }
        size_++;
    }
    
    long long Pop() {
        if (IsEmpty()) { throw std::runtime_error("Queue is empty"); }
        
        Node* temp = front_;
        long long value = temp->data;
        front_ = front_->next;
        
        if (front_ == nullptr) { end_ = nullptr; }
        
        delete temp;
        size_--;
        return value;
    }
    
    long long Top() const {
        if (IsEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return front_->data;
    }
    
    bool IsEmpty() const { return front_ == nullptr; }
    
    int GetSize() const { return size_; }
    
    void Print() const {
        Node* cur = front_;
        while (cur != nullptr) {
            std::cout << cur->data;
            if (cur->next != nullptr) {
                std::cout << " - ";
            }
            cur = cur->next;
        }
        std::cout << std::endl; 
    }
};