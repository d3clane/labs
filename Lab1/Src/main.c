#include <assert.h>
#include <stdio.h>

#include "tests.h"

int main()
{
#if STACK_TYPE == STACK_ON_ARR
    FILE* outStream = fopen("Output/Test4Arr.txt",  "w");
#else
    FILE* outStream = fopen("Output/Test4List.txt", "w");
#endif
    assert(outStream);

    printf("Test1: %lf\n", TestStack1());

    printf("Test2: %lf\n", TestStack2());

    printf("Test3: %lf\n", TestStack3());

    TestStack4(outStream);
}
