#include <stdio.h>
#include "stack.h"

int main(int argc, char const *argv[])
{
    Stack s;
    boolean test;
    int val, i;
    CreateStack(&s);
    // push(&s, 5);
    // push(&s, 9);
    // push(&s, 17);
    // push(&s, 519);
    for (i = 0; i < STACK_CAPACITY; i++)
    {
        //push(&s, 7);
    }
    test = isFull(s);
    if (test)
    {
        printf("Stack penuh\n");
    }
    else{
        printf("Stack tidak penuh\n");
    }
    printf("Idx top = %d dan top = %d\n", IDX_TOP(s), TOP(s));
    //pop(&s, &val);
    printf("Idx top = %d, top = %d, dan val = %d\n", IDX_TOP(s), TOP(s), val);
    test = isFull(s);
    if (test)
    {
        printf("Stack penuh\n");
    }
    else{
        printf("Stack tidak penuh\n");
    }
    return 0;
}
