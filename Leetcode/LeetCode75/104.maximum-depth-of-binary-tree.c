//
// Created by lisen on 24-10-28.
//
// https://leetcode.cn/problems/maximum-depth-of-binary-tree/?envType=study-plan-v2&envId=leetcode-75

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int max(int a, int b) {
    return a >= b? a : b;
}

int maxDepth(struct TreeNode* root) {
    if(root == NULL)
        return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}