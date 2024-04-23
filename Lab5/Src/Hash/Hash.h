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

typedef size_t (*HashFuncType)(HashValType value);

size_t ModHashInt   (unsigned int value);
size_t BitHashInt   (unsigned int value);
size_t KnuthHashInt (unsigned int value);

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