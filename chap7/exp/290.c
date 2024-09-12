//
// Created by lisen on 24-9-12.
//
// https://www.bjfuacm.com/problem/290
// 已知二叉树T的结点形式为(llink,data,count,rlink)
// 在树中查找值为x的结点，若找到，则计数（count）加1；否则，作为一个新结点插入树中，插入后仍为二叉排序树
// 请写出其非递归算法
// 多组数据，每组数据3行
//  第一行为二叉排序树的结点数n
//  第二行为空格分隔的n个数字，对应二叉排序树中的n个结点
//  第三行为查找的值x
// n=0时输入结束

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100     // 输入数组的最大范围

struct bst_node {
    int data;
    struct bst_node * llink;
    struct bst_node * rlink;
    int count;
};

typedef struct bst_node BST_Node;
typedef struct bst_node * BSTree;

struct ret_traverse {
    BST_Node * nodes;
    int count;
};

typedef struct ret_traverse Ret_Nodes;

void insert_bst(BSTree * tree, int key);
void create_bst(BSTree * tree, int * inputs, int len);
void search_bst(BSTree * tree, int target);
Ret_Nodes in_order_bst(BSTree tree);

int main() {
    int cnt ;
    while(scanf("%d", &cnt) == 1 && cnt != 0) {
        int inputs[MAXSIZE];
        int target;
        for(int i = 0; i < cnt; i ++)
            scanf("%d", &inputs[i]);
        scanf("%d", &target);

        BSTree tree;
        create_bst(&tree, inputs, cnt);
        search_bst(&tree, target);
        Ret_Nodes ret = in_order_bst(tree);
        for(int i = 0; i < ret.count; i++) {
            if(i == ret.count - 1)
                printf("%d", ret.nodes[i].data);
            else
                printf("%d ", ret.nodes[i].data);
        }

        putchar('\n');
        for(int i = 0; i < ret.count; i++) {
            if(i == ret.count - 1)
                printf("%d", ret.nodes[i].count);
            else
                printf("%d ", ret.nodes[i].count);
        }
        putchar('\n');
    }

    return 0;
}

void insert_bst(BSTree * tree, int key) {
    // 非递归的插入
    BST_Node * p = (BST_Node *) malloc(sizeof(BST_Node));
    if(!p)
        exit(-1);
    p->data = key;
    p->llink = p->rlink = NULL;
    p->count = 0;

    if (*tree == NULL)
        *tree = p;
    else {
        BST_Node * tmp = *tree;
        BST_Node * parent = NULL;
        while(tmp != NULL) {
            parent = tmp;
            if(tmp->data < key)
                tmp = tmp->rlink;
            else if(tmp->data == key)
                return;
            else
                tmp = tmp->llink;
        }
        if(parent->data < key)
            parent->rlink = p;
        else
            parent->llink = p;
    }
}
void create_bst(BSTree * tree, int * inputs, int len) {
    *tree = NULL;
    for(int i = 0; i < len; i++)
        insert_bst(tree, inputs[i]);
}
void search_bst(BSTree * tree, int target) {
    // 非递归的搜索
    BST_Node * p = *tree;

    while(p != NULL) {
        if(p->data == target) {
            p->count ++;
            return ;
        }
        if(p->data < target)
            p = p->rlink;
        else
            p = p->llink;
    }

    insert_bst(tree, target);   // 没找到则插入
}
Ret_Nodes in_order_bst(BSTree tree) {
    // 非递归的遍历
    // 由于最后要先输出中序结点的data 在输出结点的count
    // Ret_Nodes中 nodes成员保存遍历的数组 count成员保存数组长度
    // 以数组代替栈

    // 初始化返回值类型变量
    Ret_Nodes ret ;
    int ret_index = 0;
    ret.nodes = (BST_Node *) malloc(sizeof(BST_Node) * MAXSIZE);
    if(ret.nodes == NULL)
        exit(-1);
    ret.count = 0;

    // 栈数组
    // front == rear 表示栈空
    // 每次从stack[rear]添加元素 添加后rear++ 可优化为stack[rear++] = elem
    // 每次从stack[rear-1]弹出元素 弹出后rear-- 可优化为elem = stack[--rear]
    BST_Node stack[MAXSIZE];
    int front = 0, rear = 0;

    BST_Node *p = tree;
    while(p != NULL || front != rear) {
        if(p != NULL) {
            // 不为空 入栈
            stack[rear++] = *p;
            // 指向左子树
            p = p->llink;
        }
        else {
            // 出栈
            BST_Node popup = stack[--rear];
            // 保存结点信息到ret
            ret.nodes[ret_index] = popup;
            ret.count ++;
            ret_index ++;
            // 指向右子树
            p = popup.rlink;
        }
    }

    return ret;
}