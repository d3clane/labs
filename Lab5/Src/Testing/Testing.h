#ifndef TESTING_H
#define TESTING_H

#include <stddef.h>

#include "Hash/Hash.h"

double TestHash(const char* inFileName, const char* outFileName,
                size_t numberOfValues, HashFuncType Hash);

void TestLoadFactor(const char* inFileName, const char* outFileName,
                    size_t numberOfValues,
                    const float minLoadFactor, const float maxLoadFactor, 
                    const float loadFactorStep,
                    HashFuncType Hash);

void TestTablesOperations(const char* inFileDir, const char* outFileName,
                           const size_t from, const size_t to, const size_t step,
                           HashFuncType Hash);

double TestTablesSearches(const char* insertValuesFileName, const char* searchValuesFileName,
                          const size_t numberOfInsertedVals, const size_t numberOfSearchingVals);
                        
#endif