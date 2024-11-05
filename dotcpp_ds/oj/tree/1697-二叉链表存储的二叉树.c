//
// Created by lisen on 24-11-5.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BTNode {
    int data;
    struct BTNode * left;
    struct BTNode * right;
}BTNode, * BTree;

void btree_create_with_pre_order_seq(BTree * tree, char * seq, int * pos) {
    if(*pos == strlen(seq))
        return ;
    if(seq[*pos] == ' ') {
        *tree = NULL;
        (*pos)++;
        return ;
    }
    *tree = calloc(1, sizeof(BTNode));
    if(tree == NULL)
        exit(EXIT_FAILURE);
    (*tree)->data = seq[*pos];
    (*pos)++;
    btree_create_with_pre_order_seq(&((*tree)->left), seq, pos);
    btree_create_with_pre_order_seq(&((*tree)->right), seq, pos);
}

void btree_pre_order_traverse(BTree tree) {
    if(tree) {
        printf("%c ", tree->data);
        btree_pre_order_traverse(tree->left);
        btree_pre_order_traverse(tree->right);
    }
}

void btree_in_order_traverse_recursive(BTree tree) {
    if(tree) {
        btree_in_order_traverse_recursive(tree->left);
        printf("%c ", tree->data);
        btree_in_order_traverse_recursive(tree->right);
    }
}

void btree_in_order_traverse_iterative(BTree tree) {
    BTNode * stack[101] ;
    int top = 0;

    BTNode * node = tree;
    stack[top++] = tree;
    while(top != 0) {
        node = stack[top - 1];
        while(node) {
            stack[top++] = node->left;
            node = stack[top - 1];
        }
        top--; // 上方while循环退出时 将NULL压入栈中 此时-- 意味着去掉该NULL值
        if(top != 0) {
            node = stack[--top];
            printf("%c ", node->data);
            stack[top++] = node->right;
        }
    }
}

int main() {
    char s[101] ;
    fgets(s, 101, stdin);
    BTree tree;
    int start = 0;
    btree_create_with_pre_order_seq(&tree, s, &start);
    btree_pre_order_traverse(tree);
    putchar('\n');
    btree_in_order_traverse_iterative(tree);
    putchar('\n');
    btree_in_order_traverse_recursive(tree);
    putchar('\n');
}
