//
// Created by lisen on 24-8-29.
//
// 给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。

#include <stdlib.h>
#include <stdbool.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct TreeNode BTNode;
typedef struct TreeNode * BTree;

bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if(p == NULL && q == NULL)
        return true;
    if(p != NULL && q == NULL)
        return false;
    if(p == NULL && q != NULL)
        return false;

    return q->val == p->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}