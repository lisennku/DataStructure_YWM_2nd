//
// Created by lisen on 24-9-6.
//

#include <stdio.h>
#include <stdlib.h>

typedef int key_type;

// 自定义数据类型
struct elem_type {
    key_type key;
    char info;
};

typedef struct elem_type Elem_Type;

// 二叉搜索树的结点
struct bst_node {
    Elem_Type data;
    struct bst_node * left;
    struct bst_node * right;
};

typedef struct bst_node BST_Node;   // 用于定义二叉搜索树的结点
typedef struct bst_node * BSTree;   // 用于定义二叉搜索树

BST_Node * binary_search_tree_search_iterative(BSTree t, key_type target);

BST_Node * binary_search_tree_search_recursive(BSTree t, key_type target);

void binary_search_tree_insert_node_recursive(BSTree * t, key_type key);

void binary_search_tree_insert_node_iterative(BSTree * t, key_type key);

void binary_search_tree_create(BSTree * t);

void binary_search_tree_delete_node(BSTree * t, key_type key);

void binary_search_tree_in_order_iterative(BSTree t, Elem_Type * arr);

void binary_search_tree_in_order_recursive(BSTree t, Elem_Type * arr);

int main() {

    return 0;
}

BST_Node * binary_search_tree_search_iterative(BSTree t, key_type target) {
    BST_Node * p = t;
    while(p != NULL) {
        if(p->data.key == target)
            return p;
        if(p->data.key < target)
            p = p->right;
        else
            p = p->left;
    }

    return NULL;      // 表示查找不到 包含两种情况 一个是树为空 一个是树里没有查找值
}

BST_Node * binary_search_tree_search_recursive(BSTree t, key_type target) {
    // 二叉搜索树 搜索函数的递归版本
    if(t == NULL || t->data.key == target)    // 递归基准条件
        return t;
    if(t->data.key < target)                  // 如果根结点的值小于查找值，说明要去右子树搜索
        return binary_search_tree_search_recursive(t->right, target);
    if(t->data.key > target)                  // 如果根结点的值大于查找值，说明要去左子树搜索
        return binary_search_tree_search_recursive(t->left, target);
}

void binary_search_tree_insert_node_recursive(BSTree * t, key_type key) {
    if(*t == NULL) {
        BST_Node * p = (BST_Node *) malloc(sizeof(BST_Node));
        if (p == NULL)
            exit(-1);
        p->data.key = key;
        p->left = p->right = NULL;

        *t = p;
    }

    else if((*t)->data.key < key)
        binary_search_tree_insert_node_recursive(&((*t)->right), key);
    else
        binary_search_tree_insert_node_recursive(&((*t)->left), key);
}

void binary_search_tree_insert_node_iterative(BSTree * t, key_type key) {
    BST_Node * p = (BST_Node *) malloc(sizeof(BST_Node));
    if(p == NULL)
        exit(-1);
    p->data.key = key;
    p->left = p->right = NULL;

    if (*t == NULL)
        *t = p;
    else {
        BST_Node * tmp = *t;
        while(tmp != NULL) {
            if (tmp->data.key < key)
                tmp = tmp->right;
            else
                tmp = tmp->left;
        }
        tmp = p;
    }

}