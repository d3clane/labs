#ifndef GENERATE_TESTS_H
#define GENERATE_TESTS_H

#include <stdio.h>

void GenerateTestsInt(size_t arraySize, int maxElement);
void GenerateTestsFloat(size_t arraySize, int range);
void GenerateTestsStrs(size_t arraySize, size_t lenMin, size_t lenMax);

void GenerateTestsOps1(size_t arraySize);
void GenerateTestsOps2(size_t arraySize);
#endif