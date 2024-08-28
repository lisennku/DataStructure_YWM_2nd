//
// Created by lisen on 24-8-27.
//
#include <stdio.h>
#include "binary_tree.h"

int main() {
    // BTree t = create_binary_tree_no_para();
    BTree t;
    create_binary_tree(&t);
    // in_order_traverse_recursive(t);
    pre_order_traverse_non_recursive(t);
    putchar('\n');
    in_order_traverse_non_recursive(t);
    putchar('\n');
    level_traverse(t);

    return 0;
}