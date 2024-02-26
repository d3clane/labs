#include <stdio.h>

#include "tests.h"

int main()
{
    FILE* arrOut  = fopen("Test4Arr",  "w");
    FILE* listOut = fopen("Test4List", "w");

    printf("Test1, stack on arr : %lf\n", TestStackOnArr1());
    printf("Test1, stack on list: %lf\n", TestStackOnList1());

    printf("Test2, stack on arr : %lf\n", TestStackOnArr2());
    printf("Test2, stack on list: %lf\n", TestStackOnList2());  

    printf("Test3, stack on arr : %lf\n", TestStackOnArr3());
    printf("Test3, stack on list: %lf\n", TestStackOnList3());

    for (size_t n = 1000; n < 1e6; n += 1000)
        fprintf(arrOut, "%zu, %lf", n, TestStackOnArr4(n));
}