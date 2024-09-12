//
// Created by lisen on 24-9-12.
//
// https://www.bjfuacm.com/problem/291
// 假设一棵平衡二叉树的每个结点都标明了平衡因子b，设计一个算法，求平衡二叉树的高度。
// 多组数据，每组数据一行，为平衡二叉树的先序序列
// 输入的数字为该节点的平衡因子
// 当序列为“#”时，输入结束。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

struct avl_node {
    int balance;
    struct avl_node *left;
    struct avl_node *right;
};

typedef struct avl_node AVL_Node;
typedef struct avl_node * AVLTree;

// void convert_inputs(char * inputs, char * convert_inputs);
void create_avl_tree_prefix(AVLTree * tree, char * inputs, int index, int len);
void calc_avl_height(AVLTree tree, int * height);

int main() {
    char inputs[MAXSIZE];
    while(scanf("%s", inputs) == 1 && inputs[0] != '#') {
        AVLTree tree;
        create_avl_tree_prefix(&tree, inputs, 0, strlen(inputs));
        int height = 0;
        calc_avl_height(tree, &height);
        printf("%d\n", height);
    }

    return 0;
}

// void convert_inputs(char * inputs, char * convert_inputs) {
// }
void create_avl_tree_prefix(AVLTree * tree, char * inputs, int index, int len) {
    // 因为给定的是具有平衡因子的结点 且是前序遍历 所以直接构建 不考虑旋转等
    if(index == len - 1)
        return ;
    if(inputs[index] == '#')
        *tree = NULL;
    else {
        *tree = (AVL_Node *) malloc(sizeof(AVL_Node));
        if(*tree == NULL)
            exit(-1);
        (*tree)->balance = inputs[index] - '0';
        create_avl_tree_prefix(&((*tree)->left), inputs, ++index, len);
        create_avl_tree_prefix(&((*tree)->right), inputs, ++index, len);
    }
}
void calc_avl_height(AVLTree tree, int * height) {
    // 考虑一个带有每个结点平衡因子的avl树
    //  如果某个结点bf为0 说明起左右子树的高度相同
    //  如果某个结点bf为1 说明左子树高
    //  如果某个结点bf为-1 说明右子树高
    // 所以从根结点开始 往更高的子树遍历
    //  对于高度相同 也即bf为0 左右子树都可以
    if(tree) {
        (*height)++;
        if(tree->balance == 1)
            calc_avl_height(tree->left, height);
        else
            calc_avl_height(tree->right, height);
    }
}