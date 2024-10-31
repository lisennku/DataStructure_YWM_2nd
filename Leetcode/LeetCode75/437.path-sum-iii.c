//
// Created by lisen on 24-10-30.
//
// https://leetcode.cn/problems/path-sum-iii/description/?envType=study-plan-v2&envId=leetcode-75

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

int dfs(struct TreeNode *root, int target_sum, long long int sum) {
    if(root == NULL)
        return 0;
    sum += (long long int) root->val;
    if(sum == target_sum)
        return 1 + dfs(root->left, target_sum, sum) + dfs(root->right, target_sum, sum);
    else
        return dfs(root->left, target_sum, sum) + dfs(root->right, target_sum, sum);
}


int pathSum(struct TreeNode* root, int targetSum) {
    if(root == NULL)
        return 0;
    return dfs(root, targetSum, (long long int) 0 ) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);
}


int main() {
    // int arr1[] = {3,1,4,3,0,1,5};
    int arr1[] = {10,5,-3,3,2,0,11,3,-2,0,1};
    // int arr1[] = {3,3,0,4,2};
    int size1 = sizeof(arr1) / sizeof(int);

    struct TreeNode * root1 = create_tree_by_level(arr1, size1);

    printf("%d\n", pathSum(root1, 8));

    return 0;
}