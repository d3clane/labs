#ifndef HASH_H
#define HASH_H

#include <stdint.h>
#include <stddef.h>

#if TYPE == INT_TYPE
typedef unsigned int HashValType;
#define HASH_VAL_FORMAT_STR "%d"
#elif TYPE == FLOAT_TYPE
typedef float HashValType;
#define HASH_VAL_FORMAT_STR "%f"
#else 
typedef char* HashValType;
#define HASH_VAL_FORMAT_STR "%s"
#endif

#ifdef KNUTH_HASH
typedef size_t (*HashFuncType)(HashValType value, size_t arraySize);
#else
typedef size_t (*HashFuncType)(HashValType value);
#endif

size_t ModHashUInt   (unsigned int value);
size_t BitHashUInt   (unsigned int value);

#ifdef KNUTH_HASH
size_t KnuthHashUInt (unsigned int value, size_t arrSize);
#endif

size_t UniversalHashFixed (unsigned int value);
size_t UniversalHash(unsigned int value, const size_t a, const size_t b, const size_t mod);


size_t FloatToIntHash  (float value);
size_t BitHashFloat    (float value);
size_t MantissaHash    (float value);
size_t ExponentHash    (float value);
size_t ExpXMantissaHash(float value);

size_t StringLenHash        (char* str);
size_t SumCharsHash         (char* str);
size_t StringPolynomialHash (char* str);
size_t CRC32Hash            (char* str);

#endif