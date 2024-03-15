#ifndef QSORTS_H
#define QSORTS_H

#include <stddef.h>

void QsortHoare    (int* arr, const size_t arrSize);
void QsortLomuto   (int* arr, const size_t arrSize);
void QsortTernary  (int* arr, const size_t arrSize);
void QsortOneBranch(int* arr, const size_t arrSize);

#endif