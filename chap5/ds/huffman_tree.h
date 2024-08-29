//
// Created by lisen on 24-8-29.
//

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

struct huffman_node {
    int weight;
    int parent;
    int left_child;
    int right_child;
};

typedef struct huffman_node HT_Node;
typedef struct huffman_node * HT_Tree;

void select_index_for_two_min_value(HT_Tree ht, int end_pos, int * idx1, int * idx2);
void create_huffman_tree(HT_Tree * ht, int n);
void pre_order_traverse_huffman_tree(HT_Tree ht, int n);

#endif //HUFFMAN_TREE_H