//
// Created by lisen on 24-10-28.
//
// https://leetcode.cn/problems/leaf-similar-trees/?envType=study-plan-v2&envId=leetcode-75

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
        if(lvl[i] != 0) {
            front_node->left = create_tree_node(lvl[i]);
            queue[rear++] = front_node->left;
        }
        i++;

        if(lvl[i] != 0) {
            front_node->right = create_tree_node(lvl[i]);
            queue[rear++] = front_node->right;
        }
        i++;
    }
    free(queue);
    return root;
}

void get_leaf_list(const struct TreeNode * root, int * return_size, int * leaf_list) {
    if(root == NULL)
        return ;
    if(root->left == NULL && root->right == NULL) {
        leaf_list[(*return_size) ++] = root->val;
        return ;
    }

    get_leaf_list(root->left, return_size, leaf_list);
    get_leaf_list(root->right, return_size, leaf_list);
}

bool leafSimilar(struct TreeNode* root1, struct TreeNode* root2) {
    int * lf1 = calloc(201, sizeof(int));
    int * lf2 = calloc(201, sizeof(int));
    int s1 = 0;
    int s2 = 0;

    get_leaf_list(root1, &s1, lf1);
    get_leaf_list(root2, &s2, lf2);

    for(int i = 0; i < s1; i++)
        printf("%d", lf1[i]);
    for(int i = 0; i < s2; i++)
        printf("%d", lf2[i]);
    if(s1 != s2)
        return false;
    for(int i = 0; i < s1; i++)
        if(lf1[i] != lf2[i])
            return false;
    return true;
}

void preorderTraversal(struct TreeNode * root) {
    if (root == NULL) return;
    printf("%d ", root->val);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

int main() {
    // int arr1[] = {3,5,1,6,2,9,8,0,0,7,4};
    int arr1[] = {1,2,3};
    int size1 = sizeof(arr1) / sizeof(int);
    // int arr2[] = {3,5,1,6,7,4,2,0,0,0,0,0,0,9,8};
    int arr2[] = {1,3,2};
    int size2 = sizeof(arr2) / sizeof(int);

    struct TreeNode * root1 = create_tree_by_level(arr1, size1);
    struct TreeNode * root2 = create_tree_by_level(arr2, size2);

    preorderTraversal(root1);
    putchar('\n');
    preorderTraversal(root2);
    putchar('\n');

    leafSimilar(root1, root2);
    return 0;
}