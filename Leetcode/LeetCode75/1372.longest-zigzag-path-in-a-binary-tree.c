//
// Created by lisen on 24-10-30.
//
// https://leetcode.cn/problems/longest-zigzag-path-in-a-binary-tree/description/?envType=study-plan-v2&envId=leetcode-75

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
struct TreeNode * create_tree_node(int val) {
    struct TreeNode * node = malloc(sizeof(struct TreeNode));
    if(node == NULL)
        exit(EXIT_FAILURE);

    node->val = val;
    node->left = node->right = NULL;

    return node;
}

struct TreeNode * create_tree_by_level(int * lvl, int size) {
    if(size == 0)
        return NULL;
    struct TreeNode * root = create_tree_node(lvl[0]);

    int i = 1;      // 数组遍历用
    int front = 0;  // 队首
    int rear = 0;   // 队尾
    // 使用队列来根据横向遍历的数组创建二叉树
    struct TreeNode ** queue = calloc(size, sizeof(struct TreeNode*));
    if(queue == NULL)
        exit(EXIT_FAILURE);
    // 根结点入队
    queue[rear++] = root;
    while(front < rear && i < size) {
        // 弹出队首元素
        struct TreeNode * front_node = queue[front++];
        if(i < size && lvl[i] != 0) {
            front_node->left = create_tree_node(lvl[i]);
            queue[rear++] = front_node->left;
        }
        i++;

        if(i < size && lvl[i] != 0) {
            front_node->right = create_tree_node(lvl[i]);
            queue[rear++] = front_node->right;
        }
        i++;
    }
    free(queue);
    return root;
}

void preorderTraversal(struct TreeNode * root) {
    if (root == NULL) return;
    printf("%d ", root->val);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

int max(int a, int b) {
    return a >= b ? a : b;
}

int dfs(struct TreeNode * root, bool flag) {
    if(root == NULL)
        return 0;

    if(flag == true)
        return 1 + dfs(root->right, !flag);
    else
        return 1 + dfs(root->left, !flag);
}

int longestZigZag(struct TreeNode* root) {
    if(root == NULL)
        return 0;
    return max(max(dfs(root->left, true), dfs(root->right, false)), max(longestZigZag(root->left), longestZigZag(root->right)));
}


int main() {
    // int arr1[] = {3,1,4,3,0,1,5};
    // int arr1[] = {10,5,-3,3,2,0,11,3,-2,0,1};
    // int arr1[] = {1,1,1,0,1,0,0,1,1,0,1};
    int arr1[] = {1,0,1,1,1,0,0,1,1,0,1,0,0,0,1};
    // int arr1[] = {3,3,0,4,2};
    int size1 = sizeof(arr1) / sizeof(int);

    struct TreeNode * root1 = create_tree_by_level(arr1, size1);

    printf("%d\n", longestZigZag(root1));

    return 0;
}