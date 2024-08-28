//
// Created by lisen on 24-8-27.
//

#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "btnode_stack.h"


void create_binary_tree(BTree * tree);
BTree create_binary_tree_no_para();

void pre_order_traverse_recursive(BTree tree);
void in_order_traverse_recursive(BTree tree);
void post_order_traverse_recursive(BTree tree);

void pre_order_traverse_non_recursive(BTree tree);
void in_order_traverse_non_recursive(BTree tree);
void post_order_traverse_non_recursive(BTree tree);

void level_traverse(BTree tree);


#endif //BINARY_TREE_H
