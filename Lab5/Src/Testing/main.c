#include "Testing.h"

#include <stdio.h>
#include "Hash/Hash.h"

int main()
{
    //-----------------------Int Hashes testing-------------------------------------------

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
}