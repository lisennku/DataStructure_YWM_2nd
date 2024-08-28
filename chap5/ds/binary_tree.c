//
// Created by lisen on 24-8-27.
//
#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"

void create_binary_tree(BTree * tree) {
    /*
     * 以中序遍历方式创建二叉树
     * 在输入时，需要为叶结点输入#的左子树或右子树
     * 请注意，由于我们采取的是char作为Item，因此对于输入函数要注意，不能使用getchar，因为会导致获取到换行符，以至于一直无法结束输入
     * 对于scanf，需要使用" %c"的格式字符串，%前的空格，可以跳过任何空白字符串
     */
    char c ;
    scanf(" %c", &c);
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

BTree create_binary_tree_no_para() {
    /*
     * 以中序遍历方式创建二叉树
     * 在输入时，需要为叶结点输入#的左子树或右子树
     * 请注意，由于我们采取的是char作为Item，因此对于输入函数要注意，不能使用getchar，因为会导致获取到换行符，以至于一直无法结束输入
     * 对于scanf，需要使用" %c"的格式字符串，%前的空格，可以跳过任何空白字符串
     */
    BTree tree;

    char c;
    scanf(" %c", &c);
    if(c == '#')
        tree = NULL;
    else {
        tree = (BTNode *)malloc(sizeof(BTNode));
        tree->data = c;
        tree->left_child = create_binary_tree_no_para();
        tree->right_child = create_binary_tree_no_para();
    }

    return tree;
}

void pre_order_traverse_recursive(BTree tree) {
    if(tree) {
        printf("%c", tree->data);
        pre_order_traverse_recursive(tree->left_child);
        pre_order_traverse_recursive(tree->right_child);
    }
}
void in_order_traverse_recursive(BTree tree) {
    if(tree) {
        in_order_traverse_recursive(tree->left_child);
        printf("%c", tree->data);
        in_order_traverse_recursive(tree->right_child);
    }
}

void post_order_traverse_recursive(BTree tree) {
    if(tree) {
        post_order_traverse_recursive(tree->left_child);
        post_order_traverse_recursive(tree->right_child);
        printf("%c", tree->data);
    }
}

void pre_order_traverse_non_recursive(BTree tree);
void in_order_traverse_non_recursive(BTree tree);
void post_order_traverse_non_recursive(BTree tree);