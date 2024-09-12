//
// Created by lisen on 24-9-12.
//
// https://www.bjfuacm.com/problem/289
// 已知二叉排序树采用二叉链表存储结构，根结点的指针为T,链结点的结构为(lchild,data,rchild)
//  其中lchild、rchild分别指向该结点左，右孩子的指针，data域存放结点数据。
// 试编写算法，从小到大输出二叉排序树中所有数值大于等于x的结点的数据。要求先找到第一个满足条件的结点后，再依次输出其他满足条件的结点。
// 多组数据，每组三行。
//  第一行为二叉排序树的结点数n
//  第二行为空格分隔的n个数字，对应二叉排序树中的n个结点
//  第三行为一个数字x
// n=0时输入结束
// 关键思路
//  找到该结点 并以中序输出该结点为根的子树，注意不输出左子树 最后再输出该结点的父结点 如果有的话

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

struct bst_node {
    int data;
    struct bst_node *lchild;
    struct bst_node *rchild;
    struct bst_node *parent;  // 记录该结点的父结点 在插入时赋值
};

typedef struct bst_node BST_Node;
typedef struct bst_node * BSTree;

void insert_binary_search_tree(BSTree * tree, BST_Node * parent, int key) {
    // 递归的插入结点
    if(*tree == NULL) {
        BST_Node * p = (BST_Node *) malloc(sizeof(BST_Node));
        if(!p)
            exit(-1);
        p->data = key;
        p->lchild = p->rchild = NULL;
        p->parent = parent;
        *tree = p;
    }
    else {
        parent = *tree;
        if((*tree)->data < key)
            insert_binary_search_tree(&(*tree)->rchild, parent, key);
        else
            insert_binary_search_tree(&(*tree)->lchild, parent, key);
    }
}

void create_binary_search_tree(BSTree * tree, int * inputs, int len) {
    *tree = NULL;
    for(int i = 0; i < len; i++)
        insert_binary_search_tree(tree, NULL, inputs[i]);
}

BST_Node * search_binary_search_tree(BSTree tree, int key) {
    // 搜索
    if(tree == NULL || tree->data == key)
        return tree;
    if(tree->data < key)
        return search_binary_search_tree(tree->rchild, key);
    return search_binary_search_tree(tree->lchild, key);
}

void in_order_traverse_binary_search_tree(BSTree tree, int key) {
    // 中序遍历
    // 但是注意第一次的根结点的左子树不输出 此处通过正常遍历然后判断data
    if(tree) {
        in_order_traverse_binary_search_tree(tree->lchild, key);
        if(tree->data >= key)
            printf("%d ", tree->data);
        in_order_traverse_binary_search_tree(tree->rchild, key);
    }
}

void display_result(BSTree tree, int key) {
    in_order_traverse_binary_search_tree(tree, key);
    // 最后要输出找到结点的根 但有两种情况不输出
    // 一个是结点本身是根 他没有父结点
    // 另一个是结点是其父结点的右子树 此时父结点的值小于结点的值 不需要输出
    if(tree->parent != NULL && tree->parent->lchild == tree)
        printf("%d", tree->parent->data);
    putchar('\n');
}

int main() {
    int cnt;
    while(scanf("%d", &cnt) == 1 && cnt != 0) {
        BSTree tree;
        BST_Node *p = NULL;
        int inputs[MAXSIZE];
        int target;

        for(int i = 0; i < cnt; i++)
            scanf("%d", &inputs[i]);

        scanf("%d", &target);

        create_binary_search_tree(&tree, inputs, cnt);
        p = search_binary_search_tree(tree, target);
        display_result(p, target);

        // printf("cnt %d, target %d\n", cnt, target);
        // for(int i = 0; i < cnt; i++)
        //     printf("%d ", inputs[i]);
    }

    return 0;
}