//
// Created by lisen on 24-9-11.
//
// https://www.bjfuacm.com/problem/288
// 假设二叉树每个结点的元素均为一个单字符，根据给定的字符序列按照先序遍历的顺序递归创建该树的二叉链表，然后判断该二叉树是否为二叉排序树。
// 多组数据，每组数据有一行。每行为一个二叉树对应的前序序列（其中‘#’表示空树）。当序列为“#”时，输入结束。

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

struct bst_node {
    char key;
    struct bst_node * left;
    struct bst_node * right;
};

typedef struct bst_node BST_Node;
typedef struct bst_node * BSTree;

void create_binary_search_tree(BSTree * tree, char * inputs, int * index, int len) {
    // inputs数组是二叉树前序序列
    // 根据数组递归的创建二叉树
    // index在每次递归中负责传递对应位置的字符
    if(*index == len)                     // 递归基准条件
        return ;
    if(inputs[*index] == '#') {           // #表示当前树结点是空 后续无需递归的创建左右子树
        *tree = NULL;
        (*index)++;
    }

    else {                                // 非空树 创建当前根结点 然后递归创建左右子树
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
    // 中序遍历
    // 将中序的字符保存在ret_arr内
    if(tree) {
        in_order_traverse(tree->left, ret_arr, ret_size, index);
        ret_arr[*index] = tree->key;
        (*index)++;
        (*ret_size)++;
        in_order_traverse(tree->right, ret_arr,ret_size , index);
    }
}

bool is_binary_search_tree(BSTree tree) {
    char ret_arr[MAXSIZE];
    int ret_size = 0;
    int index = 0;

    in_order_traverse(tree, ret_arr, &ret_size, &index);

    for(int i = 0; i < ret_size - 1; i++)
        if(ret_arr[i] >= ret_arr[i+1])
            return false;

    return true;
}

void result_output(bool flag) {
    if(flag)
        printf("YES\n");
    else
        printf("NO\n");
}

int main() {

    char inputs[MAXSIZE];
    while(scanf("%s", inputs) == 1 && inputs[0] != '#') {
        BSTree tree;

        int inputs_len = strlen(inputs);
        int inputs_index = 0;
        bool flag;

        create_binary_search_tree(&tree, inputs, &inputs_index, inputs_len);
        flag = is_binary_search_tree(tree);

        result_output(flag);

    }

    return 0;
}