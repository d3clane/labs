#ifndef TESTING_H
#define TESTING_H

#include <stddef.h>

#include "Hash/Hash.h"

double TestHash(const char* inFileName, const char* outFileName,
                size_t numberOfValues, HashFuncType Hash);

#ifdef OPEN_TABLE

void TestLoadFactor(const char* inFileName, const char* outFileName,
                    size_t numberOfValues,
                    const float minLoadFactor, const float maxLoadFactor,
                    HashFuncType Hash);

#endif

#endif