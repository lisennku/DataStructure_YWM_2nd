//
// Created by lisen on 24-8-29.
//
#include <stdio.h>
#include <stdlib.h>
#include "huffman_tree.h"

int main() {
    int n = 10;
    HT_Tree ht;
    create_huffman_tree(&ht, n);
    pre_order_traverse_huffman_tree(ht, 2 * n - 1);
    printf("WPL is %d\n", calc_huffman_tree_weighted_path_length(ht, 2*n-1,0));
}
