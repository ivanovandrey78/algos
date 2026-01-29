# Algorithms & Data Structures Playground

A comprehensive collection of fundamental algorithms and data structures implemented from scratch in modern C++ (C++20). This repository serves as both a learning resource and a performance-oriented alternative to certain STL components.

## Contents

### Mathematical Functions (`math/`)
Hand-crafted implementations of core mathematical operations with focus on clarity and precision.

- `fibonacci(n)` – nth Fibonacci number (multiple algorithms available)
- `factorial(n)` – factorial with overflow detection
- `is_prime(n)` – deterministic primality test (optimized for 64-bit integers)
- `pow(base, exponent)` – fast integer and floating-point exponentiation
- `gcd(a, b)` / `lcm(a, b)` – Euclidean algorithm implementations
- `modular_inverse`, `binomial_coefficient`, and more

### Sorting Algorithms (`sorting/`)
Full implementations of classic and advanced sorting algorithms with detailed complexity analysis.

- `bubble_sort` – educational reference
- `insertion_sort` – optimal for small/narrow arrays
- `selection_sort`
- `merge_sort` – stable, O(n log n) guaranteed
- `quick_sort` – in-place, randomized pivot, introspective variant available
- `heap_sort` – using custom BinaryHeap

### Data Structures (`structures/`)

- **BinaryHeap** – min/max heap with O(1) peek, O(log n) operations
- **Deque** – double-ended queue with contiguous block allocation (cache-friendly)
- **HashMap** – open addressing with robin hood hashing, load factor monitoring
- **LinkedList** (singly & doubly)
- **Binary Search Tree** (self-balancing variants in development)
- **PriorityQueue** – built on top of BinaryHeap

## Goals & Standards

- Zero dependencies outside the C++ Standard Library
- Header-only where possible for maximum usability
- Full compliance with C++20 standards and concepts
- Detailed time & space complexity annotations
- Production-ready code quality (some implementations outperform STL in benchmarks)
- Educational clarity without sacrificing performance

## Roadmap

- [ ] AVL Tree / Red-Black Tree
- [ ] B-Tree and B+Tree implementations
- [ ] More graph algorithms (Dijkstra, A*, Floyd-Warshall)
- [ ] SIMD-optimized operations where beneficial
- [ ] Full benchmark suite comparison vs STL
