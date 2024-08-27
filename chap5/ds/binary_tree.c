//
// Created by lisen on 24-8-27.
//
#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"

void create_binary_tree(BTree * tree) {
    char c ;
    scanf("%c", &c);
    // c = getchar();
    if (c == '#') {
        *tree = NULL;
    }
    else {
        *tree = (BTNode *) malloc(sizeof(BTNode));
        if(*tree == NULL)
            exit(EXIT_FAILURE);
        (*tree)->data = c;
        (*tree)->left_child = NULL;
        (*tree)->right_child = NULL;
        create_binary_tree(&((*tree)->left_child));
        create_binary_tree(&((*tree)->right_child));
    }
}

void pre_order_traverse_recursive(BTree tree) {
    if(tree) {
        printf("%c ->", tree->data);
        pre_order_traverse_recursive(tree->left_child);
        pre_order_traverse_recursive(tree->right_child);
    }
}
void in_order_traverse_recursive(BTree tree) {
    if(tree) {
        in_order_traverse_recursive(tree->left_child);
        printf("%c ->", tree->data);
        in_order_traverse_recursive(tree->right_child);
    }
}

void post_order_traverse_recursive(BTree tree) {
    if(tree) {
        post_order_traverse_recursive(tree->left_child);
        post_order_traverse_recursive(tree->right_child);
        printf("%c ->", tree->data);
    }
}

void pre_order_traverse_non_recursive(BTree tree);
void in_order_traverse_non_recursive(BTree tree);
void post_order_traverse_non_recursive(BTree tree);