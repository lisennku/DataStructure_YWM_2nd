//
// Created by lisen on 24-8-30.
//
// 二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct TreeNode BTNode;
typedef struct TreeNode * BTree;


/*
 * 逐行入队，然后逐行出队，记录处理的次数
 * 使用数组模仿队列，front 记录队首，rear记录队尾，使用size记录每行入栈的结点数，从而弹出一行内所有结点
 */
int maxDepth(struct TreeNode* root) {
    BTNode ** arr = (BTNode **) malloc(sizeof(BTNode *) * 10001);
    if(arr == NULL)
        exit(-1);
    memset(arr, NULL, 10001);

    int front = 0;
    int rear = 0;

    int depth = 0;

    if (root == NULL)
        return 0;

    arr[front] = root;
    rear ++;

    while(front != rear) {
        int size = rear - front;
        while(size) {
            size -- ;
            BTNode * p = arr[front];
            front ++;
            if(p->left) {
                arr[rear] = p->left;
                rear ++;
            }
            if(p->right) {
                arr[rear] = p->right;
                rear++;
            }
        }
        depth ++;
    }

    return depth;
}

















