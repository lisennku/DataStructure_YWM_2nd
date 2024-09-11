//
// Created by lisen on 24-9-11.
//
// https://www.bjfuacm.com/problem/288
// 假设二叉树每个结点的元素均为一个单字符，根据给定的字符序列按照先序遍历的顺序递归创建该树的二叉链表，然后判断该二叉树是否为二叉排序树。
// 多组数据，每组数据有一行。每行为一个二叉树对应的前序序列（其中‘#’表示空树）。当序列为“#”时，输入结束。

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXSIZE 100

struct bst_node {
    char key;
    struct bst_node * left;
    struct bst_node * right;
};

typedef struct bst_node BST_Node;
typedef struct bst_node * BSTree;

void create_binary_search_tree(BSTree * tree, char * inputs, int * index, int len) {
    if(*index == len)
        return ;
    if(inputs[*index] == '#') {
        *tree = NULL;
        (*index)++;
    }

    else {
        *tree = (BST_Node *) malloc(sizeof(BST_Node));
        if(*tree == NULL)
            exit(-1);
        (*tree)->key = inputs[*index];
        (*tree)->left = (*tree)->right = NULL;
        (*index)++;
        create_binary_search_tree(&((*tree)->left), inputs, index, len);
        create_binary_search_tree(&((*tree)->right), inputs, index, len);
    }


}

void in_order_traverse(BSTree tree, char * ret_arr, int * ret_size, int * index) {
    if(tree) {
        in_order_traverse(tree->left, ret_arr, ret_size, index);
        ret_arr[*index] = tree->key;
        (*index)++;
        (*ret_size)++;
        in_order_traverse(tree->right, ret_arr,ret_size , index);
    }
}

bool is_binary_search_tree(BSTree tree);

void result_output(bool flag) {
    if(flag)
        printf("YES\n");
    else
        printf("NO\n");
}

int main() {

    char inputs[7] = "ba##c##";
    BSTree tree = NULL;
    int index = 0;
    create_binary_search_tree(&tree, inputs, &index, 7);

    char result[MAXSIZE];
    int ret_size = 0;
    index = 0;
    in_order_traverse(tree, result, &ret_size, &index);

    for(int i = 0; i < ret_size; i++)
        printf("%c ", result[i]);

    return 0;
}