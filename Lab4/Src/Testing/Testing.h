#ifndef TESTING_H
#define TESTING_H

#include <stddef.h>

double* TestHeap(const char* testsFromDir, const char* testsOutFile, 
                size_t from, size_t to, size_t step, size_t numberOfTests,
                void (*Heap)(int* arr, size_t arrSize));

#endif