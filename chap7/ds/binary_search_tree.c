//
// Created by lisen on 24-9-6.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10
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

void binary_search_tree_create(BSTree * t, const key_type * arr, int len);

int binary_search_tree_delete_node(BSTree * t, key_type key);

void binary_search_tree_in_order_iterative(BSTree t, key_type * arr, int * idx);

void binary_search_tree_in_order_recursive(BSTree t, key_type * arr, int * idx);

int main() {
    key_type in_arr[MAX_SIZE] = {10, 1, 2, 13, 50, 44, 33, 77, 88, 99};
    key_type out_arr[MAX_SIZE];
    key_type out_arr2[MAX_SIZE-1];

    BSTree tree;
    int index = 0;
    binary_search_tree_create(&tree, in_arr, MAX_SIZE);
    // binary_search_tree_in_order_recursive(tree, out_arr, &index);
    binary_search_tree_in_order_iterative(tree, out_arr, &index);
    for(int i = 0; i < MAX_SIZE; i++)
        printf("%d ", out_arr[i]);
    putchar('\n');

    binary_search_tree_delete_node(&tree, 10);
    index = 0;
    binary_search_tree_in_order_iterative(tree, out_arr2, &index);
    for(int i = 0; i < MAX_SIZE - 1; i++)
        printf("%d ", out_arr2[i]);
    putchar('\n');
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

void binary_search_tree_create(BSTree * t, const key_type * arr, int len) {
    *t = NULL;
    for(int i = 0; i < len; i++)
        binary_search_tree_insert_node_recursive(t, arr[i]);
}

int binary_search_tree_delete_node(BSTree * t, key_type key) {
    /*
     * 针对被删除结点左右子树都有的情况，采取以其中序遍历中直接前驱结点替代被删除结点的方式
     * 直接前驱，说明是其左子树的最右侧的结点
     * 对于其他情况，需要做两点
     *  1. 判断待删除结点是其父结点的左或右结点
     *  2. 判断待删除结点的左或右子树存在
     */
    // 找到被删除的结点
    BST_Node * p = *t;
    BST_Node * f = NULL;
    while(p) {
        if(p->data.key == key)
            break;
        f = p;  // 将f指向p，用来表示待删除结点的父结点
        if(p->data.key < key)
            p = p->right;
        else
            p = p->left;
    }
    // p为NULL 包含两种情况 1. 树t为空；2. 找不到指定的key的结点
    // 直接返回-1 ，不做任何处理
    if(p == NULL)
        return -1;

    // 没有返回-1 说明找到了待删除结点
    // 此时p指向该结点，f指向待删除结点的父结点
    // 因为涉及到修改指针操作，因此先判断左右子树均存在的情况
    if(p->left && p->right) {
        // 此时不需要删除p指针，但涉及到修改p的data成员
        // 因此使用额外指针保存p
        BST_Node * q = p;
        BST_Node * s = p->left; // 需要在p的左子树中找到其直接前驱
        while(s->right) {
            q = s;
            s = s->right;
        }
        p->data.key = s->data.key;
        // 此时需要将s的左子树放到其父结点的右子树位置
        // 但是需要判断一种情况
        // 也即如果进入循环前的s，没有右子树，也就没有进入循环
        // 此时需要将s的左子树作为p，也即q，的左子树，而非右子树

        if(q != p)
            q->right = s->left;
        else
            q->left = s->left;

        free(s);
        return 1;
    }
    // 待删除结点的右子树为空
    // 将其左子树挂接到父结点
    // 此时也处理了左子树为NULL的情况
    BST_Node * q = p;
    if(p->right == NULL) {
        q = p;         // 后续删除使用q
        p = p->left;   // 后续挂到父结点f的时候使用p
    }
    else {
        q = p;
        p = p->right;
    }

    // 如果删除的是根结点
    if(f == NULL)
        *t = p;
    // 如果删除的是左结点
    else if(q == f->left)
        f->left = p;
    // 如果是删除的是右结点
    else
        f->right = p;
    free(q);

    return 1;
}

void binary_search_tree_in_order_iterative(BSTree t, key_type * arr, int * idx) {
    // 使用数组代替栈
    BST_Node * stack[MAX_SIZE];
    int front = 0;
    int rear = 0;

    BST_Node * p = t;
    while(p != NULL || front != rear) {
        if(p) {
            stack[rear++] = p;
            p = p->left;
        }
        else {
            p = stack[--rear];
            arr[(*idx)++] = p->data.key;
            p = p->right;
        }
    }
}

void binary_search_tree_in_order_recursive(BSTree t, key_type * arr, int * idx) {
    if(t) {
        binary_search_tree_in_order_recursive(t->left, arr, idx);
        arr[*idx] = t->data.key;
        (*idx)++;
        binary_search_tree_in_order_recursive(t->right, arr, idx);
    }
}