//
// Created by lisen on 24-8-27.
//
#include <stdio.h>
#include "binary_tree.h"

int main() {
    // BTree t = create_binary_tree_no_para();
    BTree t;
    create_binary_tree(&t);
    printf("pre-order traverse\n");
    pre_order_traverse_non_recursive(t);
    putchar('\n');
    printf("in-order traverse\n");
    in_order_traverse_non_recursive(t);
    putchar('\n');
    printf("post-order traverse\n");
    post_order_traverse_non_recursive(t);
    putchar('\n');
    printf("level traverse\n");
    level_traverse(t);

    return 0;
}