#pragma once 
#define ARRAY_FUNCTIONS_H

#include <iostream>
#include <ctime>

// Show array. 
void PrintMassive(int* a, int n);

// Operations with arrays.
int MinArray(int* a,int n);
int MaxArray(int* a,int n);
double GetMiddleArray(int *a,int n);

// New array from old.
void ReverseArray(int* arr, int n);
int* GetUniqArray(int* arr,int n,int& res_size);

// Getters. 
int* RandomMassive(int& n,int border);
int* InputArray(int& n);