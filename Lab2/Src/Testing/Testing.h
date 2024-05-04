#ifndef TESTING_H
#define TESTING_H

#include <stddef.h>

double* TestSort(const char* testsFromDir, const char* testsOutFile, 
                size_t from, size_t to, size_t step, size_t numberOfTests,
                void (*sort)(int* arr, size_t arrSize));

void TestHeapSort(const char* testsFromDir, const char* testsResFileName, 
                  size_t from, size_t to, size_t step, size_t numberOfTests,
                  void (*sort)(int* arr, size_t arrSize, size_t heapRank));

void TestIntroSort(const char* testsFromDir, const char* testsResFileName, 
                  size_t from, size_t to, size_t step, size_t numberOfTests,
                  void (*sort)(int* arr, size_t arrSize, double recursionDepthConstant));
                  
#endif