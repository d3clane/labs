#include <stdio.h>

#include "stackOnArr.h"
#include "stackOnList.h"

int main()
{
    StackOnList* stk1 = StackOnListCtor(sizeof(int));

    int a = 5;
    StackOnListPush(stk1, &a);
    a = 7;
    StackOnListPush(stk1, &a);
    a = 9;
    StackOnListPush(stk1, &a);
    a = 1;
    StackOnListPush(stk1, &a);
    a = -5;
    StackOnListPush(stk1, &a);

    int b = 78;
    StackOnListTop(stk1, &b);
    printf("%d\n", b);

    StackOnListPop(stk1);
    StackOnListTop(stk1, &b);
    printf("%d\n", b);

    StackOnListPop(stk1);
    StackOnListTop(stk1, &b);
    printf("%d\n", b);

    StackOnListPop(stk1);
    StackOnListTop(stk1, &b);
    printf("%d\n", b);

    StackOnListPop(stk1);
    StackOnListTop(stk1, &b);
    printf("%d\n", b);
}