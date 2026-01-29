#include "array_functions.h"

int* RandomMassive(int& n,int border) {
    std::cin >> n;
    int* arr = new int[n];
    srand(time(0));
    for(int i = 0; i < n; ++i) { arr[i] = rand() % border + 1; }
    return arr; 
}

int* InputArray(int& n) {
    std::cin >> n;
    int* arr = new int[n];
    for(int i = 0; i<n; i++) { std::cin >> arr[i]; }
    return arr;
}

int SumArray(int *a, int n) {
    int c = 0; 
    for(int i = 0;i < n;i++) c += a[i];
    return c;
}

int MinArray(int* a,int n) {
    int m = GetMiddleArray(a,n);
    for(int i = 0;i < n;i++) {
        if (m > a[i]) m = a[i];
    }
    return m;
}

int MaxArray(int *a,int n) { 
    int m = GetMiddleArray(a,n);
    for(int i = 0;i < n;i++) {
        if (m<a[i]) m = a[i];
    }
    return m;
}

void ReverseArray(int* arr, int n) {
   for (int i = 0; i < n/2; i++) 
       std::swap(arr[i],arr[n - i - 1]);
}

void PrintMassive(int* a, int n) {
    std::cout << '{';
    for (int i=0;i<n;i++) {
        if (i == n-1)
        std::cout << a[i] << '}';
        else 
        std::cout << a[i] << ", ";
    }   
    std::cout << '\n';
} 

double GetMiddleArray(int *a,int n) {
    double sum = 0;
    for (int i=0;i<n;i++) sum += a[i];
    sum = sum/n;
    return sum;
}