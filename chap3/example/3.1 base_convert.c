//
// Created by lisen on 24-8-19.
//
#include <stdio.h>
#include <stdlib.h>
#include "basic.h"
#include "../ds/array_stack.h"
#include "../ds/linked_stack.h"

void convert_with_array_stack();
void convert_with_linked_stack();

int main() {
    convert_with_array_stack();
}

void convert_with_array_stack() {
    int n = 123456;
    int convert = 8;
    Array_Stack s;
    if(array_stack_init(&s) != OK)
        exit(ERROR);
    while(n) {
        array_stack_push(&s, n % convert);
        n = n / convert;
    }
    while(!array_stack_is_empty(s)) {
        Item e;
        array_stack_pop(&s, &e);
        printf("%d", e);
    }
    printf("\n");

}
void convert_with_linked_stack() {

}
