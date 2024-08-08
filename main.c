#include <stdio.h>
#include "chap2/single_linked_list.h"
#include <stdlib.h>

int main(void)
{
    Single_linked_list sll;
    Node * head_node = (Node *) malloc(sizeof(Node));
    head_node->next = NULL;
    sll = head_node;
    printf("sll points to %p\n", sll);
    printf("sll's address is %p\n", &sll);
}
