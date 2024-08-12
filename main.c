#include <stdio.h>
#include "chap2/single_linked_list.h"
#include <stdlib.h>

int main(void)
{
    int a = 10;
    int *b = &a;
    int **c = &b;
    printf("address for variable a, b, c is %p, %p, %p\n", &a, &b, &c);
    printf("value for variable b is %p\n", b);
    printf("value for variable c is %p\n", c);
    printf("value for *c is %p\n", *c);
}
