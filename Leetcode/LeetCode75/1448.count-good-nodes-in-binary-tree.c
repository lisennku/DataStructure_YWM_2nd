//
// Created by lisen on 24-10-28.
//
// https://leetcode.cn/problems/count-good-nodes-in-binary-tree/?envType=study-plan-v2&envId=leetcode-75

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

void find_goods_nodes(struct TreeNode * root, int * goods, int max) {
    if(root == NULL)
        return ;
    if(root->val >= max)
        (*goods)++;
    find_goods_nodes(root->left, goods, root->val > max ? root->val : max);
    find_goods_nodes(root->right, goods, root->val > max ? root->val : max);

}

int goodNodes(struct TreeNode* root) {
    int goods = 0;
    if (root == NULL)
        return goods;
    find_goods_nodes(root, &goods, root->val);

    return goods;
}

int main() {
    // int arr1[] = {3,1,4,3,0,1,5};
    int arr1[] = {9,0,3,6};
    // int arr1[] = {3,3,0,4,2};
    int size1 = sizeof(arr1) / sizeof(int);

    struct TreeNode * root1 = create_tree_by_level(arr1, size1);

    preorderTraversal(root1);
    putchar('\n');

    int res = goodNodes(root1);
    printf("%d\n", res);
    return 0;
}