//
// Created by lisen on 24-8-29.
//
// 给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。

#include <stdlib.h>
// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct TreeNode BTNode;
typedef struct TreeNode * BTree;

void in_order_traverse(BTree root, int *returnSize, int * ret) {
    if(root) {
        in_order_traverse(root->left, returnSize, ret);
        ret[*returnSize] = root->val;
        (*returnSize)++;
        in_order_traverse(root->right, returnSize, ret);
    }
}
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int * ret = (int *) malloc(sizeof(int) * 501);
    if(!ret)
        exit(-1);

    *returnSize = 0;
    in_order_traverse(root, returnSize, ret);

    return ret;
}