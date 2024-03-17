#include <assert.h>
#include <stdio.h>

#include "tests.h"

int main()
{
    FILE* arrOut  = fopen("Output/Test4Arr.txt",  "w");
    FILE* listOut = fopen("Output/Test4List.txt", "w");
    assert(arrOut);
    assert(listOut);

    double resArr  = 0;
    double resList = 0;

    TestStackArr(1, resArr);
    TestStackList(1, resList);

    printf("Test1, stack on arr : %lf\n", resArr);
    printf("Test1, stack on list: %lf\n", resList);

    TestStackArr(2, resArr);
    TestStackList(2, resList);
    printf("Test2, stack on arr : %lf\n", resArr);
    printf("Test2, stack on list: %lf\n", resList);  

    TestStackArr(3, resArr);
    TestStackList(3, resList);
    printf("Test3, stack on arr : %lf\n", resArr);
    printf("Test3, stack on list: %lf\n", resList);

    for (size_t n = 1000; n < (size_t)1e6; n += 1000)
    {
        TestStackArr(4, resArr, n);
        fprintf(arrOut, "%zu, %lf\n", n, resArr);
    }

    for (size_t n = 1000; n < (size_t)1e6; n += 1000)
    {
        TestStackList(4, resList, n);
        fprintf(listOut, "%zu, %lf\n", n, resList);
    }
}
