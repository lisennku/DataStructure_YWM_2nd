//
// Created by lisen on 24-8-27.
//

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef char ElemType;

struct binary_tree_node {
    ElemType data;
    struct binary_tree_node * left_child;
    struct binary_tree_node * right_child;
};

typedef struct binary_tree_node BTNode;
typedef struct binary_tree_node * BTree;

void create_binary_tree(BTree * tree);
BTree create_binary_tree_no_para();

void pre_order_traverse_recursive(BTree tree);
void in_order_traverse_recursive(BTree tree);
void post_order_traverse_recursive(BTree tree);

void pre_order_traverse_non_recursive(BTree tree);
void in_order_traverse_non_recursive(BTree tree);
void post_order_traverse_non_recursive(BTree tree);


#endif //BINARY_TREE_H
