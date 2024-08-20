//
// Created by lisen on 24-8-19.
//
#include <fenv.h>
#include <stdio.h>
#include <stdlib.h>
#include "../ds/array_stack.h"
#include "../ds/linked_stack.h"
#include "basic.h"

void convert_with_array_stack();
void convert_with_linked_stack();
void print_item(Item e);

int main() {
    convert_with_array_stack();
    convert_with_linked_stack();
}


void convert_with_array_stack() {
    int n = 123456;
    int convert = 8;
    Array_Stack as;
    if(array_stack_init(&as) != OK)
        exit(ERROR);
    while(n) {
        array_stack_push(&as, n % convert);
        n = n / convert;
    }

    printf("length of stack is %d\n", array_stack_length(as));
    printf("top value of stack is %d\n", array_stack_get_top(as));
    array_stack_traverse(as, *print_item);
    printf("\n");

    while(!array_stack_is_empty(as)) {
        Item e;
        array_stack_pop(&as, &e);
        printf("%d", e);
    }
    printf("\n");

}
void convert_with_linked_stack() {
    int n = 123456;
    int convert = 8;
    Linked_Stack ls;
    if(linked_stack_init(&ls) != OK)
        exit(ERROR);
    while(n) {
        linked_stack_push(&ls, n % convert);
        n = n / convert;
    }

    printf("length of stack is %d\n", linked_stack_length(ls));
    printf("top value of stack is %d\n", linked_stack_get_top(ls));
    printf("traverse print stack \n");
    linked_stack_traverse(ls, *print_item);
    printf("\n");


    while(!linked_stack_is_empty(ls)) {
        Item e;
        linked_stack_pop(&ls, &e);
        printf("%d", e);
    }

    printf("\n");
}

void print_item(Item e) {
    printf("%d ", e);
}