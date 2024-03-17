#include <assert.h>
#include <stdio.h>

#define STACK_ON_LIST 0
#define STACK_ON_ARR  1

#define STACK_TYPE 0

#include "tests.h"

int main()
{
    FILE* arrOut  = fopen("Output/Test4Arr.txt",  "w");
    //FILE* listOut = fopen("Output/Test4List.txt", "w");
    assert(arrOut);
    //assert(listOut);

    printf("Test1, stack on arr : %lf\n", TestStack1());
    //printf("Test1, stack on list: %lf\n", resList);

    printf("Test2, stack on arr : %lf\n", TestStack2());
    //("Test2, stack on list: %lf\n", resList);  

    printf("Test3, stack on arr : %lf\n", TestStack3());
    //printf("Test3, stack on list: %lf\n", resList);

    TestStack4(arrOut);
}
