//
// Created by lisen on 24-8-30.
//
// 给你一个二叉树的根节点 root ， 检查它是否轴对称。
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
 * 递归方法
 *  给定一个检测两个结点的函数，初始传入根节点的左子结点和右子结点
 * 函数逻辑：
 *  判断传入的结点，同时为NULL 返回true，如果只有一个为NULL 返回false
 *  如果都不为NULL，则
 *      返回两个结点值是否相等 和 左结点的左子结点，右结点的右子结点 和 左结点的右子结点，右结点的左子结点 三个条件取and
 */
bool left_and_right(BTNode * left, BTNode * right) {
    if(left == NULL && right == NULL)
        return true;
    if(left == NULL || right == NULL)
        return false;
    return left->val == right->val && left_and_right(left->left, right->right) && left_and_right(left->right, right->left);
}

/*
 * 非递归方法
 *  之前考虑使用栈，但是无法找到合适的条件，解答提示使用队列
 * 函数接受两个参数，第一次传参传入两次根结点，后序传入左/右，右/左
 * 函数逻辑：
 *  参数入队
 *  当队列不为空时
 *      弹出队首两个元素，判断
 *          如果同时为空，继续弹出
 *          如果不同时为空，或者val不相等，返回false
 *          都不满足，继续入队
 *          p1.left p2.right
 *
 *          p1.right p2.left
 *  跳出循环，返回true
 */
bool check_wo_recursive(BTNode * p1, BTNode * p2) {
    // 使用数组代替queue
    // 动态分配1001个BTNode空间
    BTNode ** arr = (BTNode **) malloc(sizeof(BTNode *) * 1001);
    if(arr == NULL)
        exit(-1);
    memset(arr, NULL, 1001);

    int front = 0, rear = 0;
    arr[front] = p1;
    arr[front+1] = p2;

    rear += 2;

    while(front != rear) {
        BTNode * a;
        BTNode * b;
        a = arr[front];
        b = arr[front+1];
        front += 2;

        if(a == NULL && b == NULL)
            continue;
        if((a == NULL || b == NULL) || (a->val != b->val))
            return false;

        arr[rear] = a->left;
        arr[rear+1] = b->right;
        rear += 2;

        arr[rear] = a->right;
        arr[rear+1] = b->left;
        rear += 2;
    }
    free(arr);
    return true;
}
bool isSymmetric(struct TreeNode* root) {
    // if (root == NULL)
    //     return true;
    // return left_and_right(root->left, root->right);
    return check_wo_recursive(root, root);
}