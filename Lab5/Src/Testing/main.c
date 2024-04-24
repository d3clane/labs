#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Testing.h"
#include "Hash/Hash.h"
#include "HashTable/HashTableOpen.h"
#include "HashTable/HashTableWithList.h"

int main()
{
    //-----------------------Hashes testing-------------------------------------------

/*
#if TYPE == INT_TYPE
    printf("Mod - %lf\n", TestHash("Tests/IntHash/1000000_1.in",
                                   "TestsResults/IntHash/Mod.out",
                                   1000000, ModHashInt));
    printf("Bit - %lf\n", TestHash("Tests/IntHash/1000000_1.in",
                                    "TestsResults/IntHash/Bit.out",
                                    1000000, BitHashInt));
    printf("Knuth - %lf\n", TestHash("Tests/IntHash/1000000_1.in",
                                    "TestsResults/IntHash/Knuth.out",
                                    1000000, KnuthHashInt));
#elif TYPE == FLOAT_TYPE
    printf("Float to int bit - %lf\n", TestHash("Tests/FloatHash/1000000_1.in",
                                   "TestsResults/FloatHash/FloatToIntBit.out",
                                   1000000, FloatToIntHash));
    printf("Float bit - %lf\n", TestHash("Tests/FloatHash/1000000_1.in",
                                    "TestsResults/FloatHash/FloatBit.out",
                                    1000000, BitHashFloat));
    printf("Mantissa - %lf\n", TestHash("Tests/FloatHash/1000000_1.in",
                                    "TestsResults/FloatHash/Mantissa.out",
                                    1000000, MantissaHash));
    printf("Exponent - %lf\n", TestHash("Tests/FloatHash/1000000_1.in",
                                    "TestsResults/FloatHash/Exponent.out",
                                    1000000, ExponentHash));
    printf("Exponent x Mantissa - %lf\n", TestHash("Tests/FloatHash/1000000_1.in",
                                    "TestsResults/FloatHash/ExpXMantissa.out",
                                    1000000, ExpXMantissaHash));
#else
    printf("Len - %lf\n", TestHash("Tests/StrHash/1000000_1.in",
                                    "TestsResults/StrHash/Len.out",
                                    1000000, StringLenHash));

    printf("Sum - %lf\n", TestHash("Tests/StrHash/1000000_1.in",
                                    "TestsResults/StrHash/Sum.out",
                                    1000000, SumCharsHash));

    printf("Polynomial - %lf\n", TestHash("Tests/StrHash/1000000_1.in",
                                    "TestsResults/StrHash/Polynom.out",
                                    1000000, StringPolynomialHash));

    printf("CRC32 - %lf\n", TestHash("Tests/StrHash/1000000_1.in",
                                    "TestsResults/StrHash/CRC32.out",
                                    1000000, CRC32Hash));
#endif
*/
    //------------------------Hash table-----------------------------

#define OUT_DIR "TestsResults/LoadFactor/LoadFactor"

    float maxLoadFactor  = 0.9;
    float minLoadFactor  = 0.01;
    float loadFactorStep = 0.01;
#if defined(LIST_TABLE)
    const char* outFileName = OUT_DIR "List.out";
    minLoadFactor  = 0.1;
    maxLoadFactor  = 5;
    loadFactorStep = 0.05;
#elif defined(OPEN_TABLE) && PROBE_FUNC == LINEAR
    const char* outFileName = OUT_DIR "Linear.out";
#elif defined(OPEN_TABLE) && PROBE_FUNC == QUADRATIC
    const char* outFileName = OUT_DIR "Quadratic.out";
#else
    const char* outFileName = OUT_DIR "Hash.out";
#endif

#undef OUT_DIR

    //TestLoadFactor("Tests/IntHash/1000000_1.in", outFileName,
    //               1000000, minLoadFactor, maxLoadFactor, loadFactorStep, KnuthHashInt);

#define OUT_DIR "TestsResults/Ops/Ops1"
#if defined(LIST_TABLE)
    outFileName = OUT_DIR "List.out";
#elif defined(OPEN_TABLE) && PROBE_FUNC == LINEAR
    outFileName = OUT_DIR "Linear.out";
#elif defined(OPEN_TABLE) && PROBE_FUNC == QUADRATIC
    outFileName = OUT_DIR "Quadratic.out";
#else
    outFileName = OUT_DIR "Hash.out";
#endif

    TestTablesOperations("Tests/Ops1", outFileName, 
                         10000, 1000000, 10000, KnuthHashInt);

#define OUT_DIR "TestsResults/Ops/Ops2"
#if defined(LIST_TABLE)
    outFileName = OUT_DIR "List.out";
#elif defined(OPEN_TABLE) && PROBE_FUNC == LINEAR
    outFileName = OUT_DIR "Linear.out";
#elif defined(OPEN_TABLE) && PROBE_FUNC == QUADRATIC
    outFileName = OUT_DIR "Quadratic.out";
#else
    outFileName = OUT_DIR "Hash.out";
#endif

    TestTablesOperations("Tests/Ops2", outFileName,
                        10000, 1000000, 10000, KnuthHashInt);
}