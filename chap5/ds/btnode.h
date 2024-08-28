//
// Created by lisen on 24-8-28.
//

#ifndef BTNODE_H
#define BTNODE_H
typedef char ElemType;

struct binary_tree_node {
    ElemType data;
    struct binary_tree_node * left_child;
    struct binary_tree_node * right_child;
};

typedef struct binary_tree_node BTNode;
typedef struct binary_tree_node * BTree;
#endif //BTNODE_H
