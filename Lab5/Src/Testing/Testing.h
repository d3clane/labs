#ifndef TESTING_H
#define TESTING_H

#include <stddef.h>

#include "Hash/Hash.h"

double TestHash(const char* inFileName, const char* outFileName,
                size_t numberOfValues, HashFuncType hash);

#endif