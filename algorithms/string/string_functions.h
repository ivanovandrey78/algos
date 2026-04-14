#pragma once 

#include <iostream>

int StrLen(const char* string);
int SymbolIndex(char symbol,const char* s);
void Print(const char* s);
const char* StrFind(const char* str, const char* substr);
char* StrCopy(char* dest, const char* src);
bool IsEqual(const char* str1, const char* str2);
char* StrCopyN(char* dest, const char* src, int n);
void TrimRight(char* str);
const char* SkipSpaces(const char* str);