#include <stdio.h>

#include "stackOnArr.h"
#include "stackOnList.h"

int main()
{
    StackOnArr* stk1 = StackOnArrCtor(8, sizeof(int));

    int a = 5;
    StackOnArrPush(stk1, &a);
    printf("%d\n", stk1->data.size);
    a = 7;
    StackOnArrPush(stk1, &a);
    printf("%d\n", stk1->data.size);
    a = 9;
    StackOnArrPush(stk1, &a);
    printf("%d\n", stk1->data.size);
    a = 1;
    StackOnArrPush(stk1, &a);
    printf("%d\n", stk1->data.size);
    a = -5;
    StackOnArrPush(stk1, &a);
    printf("%d\n", stk1->data.size);

    int b = 78;
    StackOnArrTop(stk1, &b);
    printf("%d\n", b);

    StackOnArrPop(stk1);
    StackOnArrTop(stk1, &b);
    printf("%d\n", b);

    StackOnArrPop(stk1);
    StackOnArrTop(stk1, &b);
    printf("%d\n", b);

    StackOnArrPop(stk1);
    StackOnArrTop(stk1, &b);
    printf("%d\n", b);

    StackOnArrPop(stk1);
    StackOnArrTop(stk1, &b);
    printf("%d\n", b);
}