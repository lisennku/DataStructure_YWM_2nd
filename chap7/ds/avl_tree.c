//
// Created by lisen on 24-9-9.
//

#include <stdio.h>
#include <stdlib.h>


#define MAX_SIZE 10
typedef int key_type;

struct avl_node {
    key_type key;
    struct avl_node * left;
    struct avl_node * right;
    int bf;
};

typedef struct avl_node AVL_Node;
typedef struct avl_node * AVL_Tree;




