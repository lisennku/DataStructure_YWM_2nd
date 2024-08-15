//
// Created by lisen on 24-8-15.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "basic.h"
#include "loop_list.h"

int main() {
    loop_list list;
    printf("initializing loop list\n");
    loop_list_initial(&list);
    printf("  is list empty? %s\n", loop_list_is_empty(list) == true ? "yes" : "no");
    printf("  length of empty loop list is %d\n", loop_list_length(list));

    putchar('\n');

    printf("Now inserting element in position 1\n");
    Item e1 = 10;
    loop_list_insert_element(&list, 1, e1);
    printf("  display loop list \n");
    loop_list_display(list);
    printf("  is list empty? %s\n", loop_list_is_empty(list) == true ? "yes" : "no");
    printf("  length of empty loop list is %d\n", loop_list_length(list));

    putchar('\n');

    printf("Now inserting element in position 2\n");
    Item e2 = 12;
    loop_list_insert_element(&list, 2, e2);
    printf("  display loop list \n");
    loop_list_display(list);
    printf("  is list empty? %s\n", loop_list_is_empty(list) == true ? "yes" : "no");
    printf("  length of empty loop list is %d\n", loop_list_length(list));

    putchar('\n');

    printf("Now inserting element in position 3\n");
    Item e3 = 14;
    loop_list_insert_element(&list, 3, e3);
    printf("  display loop list \n");
    loop_list_display(list);
    printf("  is list empty? %s\n", loop_list_is_empty(list) == true ? "yes" : "no");
    printf("  length of empty loop list is %d\n", loop_list_length(list));

    putchar('\n');

    printf("Now locating element 12 in loop list\n");
    Item e_l = 19;
    unsigned int l = loop_list_locate_element(list, e_l);
    if(l)
        printf("the position is %u\n", l);
    else
        printf("not exists in loop list\n");

    putchar('\n');

    printf("Now deleting element in position 3\n");
    loop_list_delete_element(&list, 3);
    printf("  display loop list \n");
    loop_list_display(list);
    printf("  is list empty? %s\n", loop_list_is_empty(list) == true ? "yes" : "no");
    printf("  length of empty loop list is %d\n", loop_list_length(list));


    return 0;
}