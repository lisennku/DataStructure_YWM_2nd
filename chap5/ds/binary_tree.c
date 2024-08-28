//
// Created by lisen on 24-8-27.
//
#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

#include "btnode_queue.h"


void create_binary_tree(BTree * tree) {
    /*
     * 以前序遍历方式创建二叉树
     * 在输入时，需要为叶结点输入#的左子树或右子树
     * 请注意，由于我们采取的是char作为Item，因此对于输入函数要注意，不能使用getchar，因为会导致获取到换行符，以至于一直无法结束输入
     * 对于scanf，需要使用" %c"的格式字符串，%前的空格，可以跳过任何空白字符串
     */
    char c ;
    scanf(" %c", &c);
    // c = getchar();
    if (c == '#') {
        *tree = NULL;
    }
    else {
        *tree = (BTNode *) malloc(sizeof(BTNode));
        if(*tree == NULL)
            exit(EXIT_FAILURE);
        (*tree)->data = c;
        (*tree)->left_child = NULL;
        (*tree)->right_child = NULL;
        create_binary_tree(&((*tree)->left_child));
        create_binary_tree(&((*tree)->right_child));
    }
}
BTree create_binary_tree_no_para() {
    /*
     * 以前序遍历方式创建二叉树
     * 在输入时，需要为叶结点输入#的左子树或右子树
     * 请注意，由于我们采取的是char作为Item，因此对于输入函数要注意，不能使用getchar，因为会导致获取到换行符，以至于一直无法结束输入
     * 对于scanf，需要使用" %c"的格式字符串，%前的空格，可以跳过任何空白字符串
     */
    BTree tree;

    char c;
    scanf(" %c", &c);
    if(c == '#')
        tree = NULL;
    else {
        tree = (BTNode *)malloc(sizeof(BTNode));
        tree->data = c;
        tree->left_child = create_binary_tree_no_para();
        tree->right_child = create_binary_tree_no_para();
    }

    return tree;
}

void pre_order_traverse_recursive(BTree tree) {
    if(tree) {
        printf("%c ", tree->data);
        pre_order_traverse_recursive(tree->left_child);
        pre_order_traverse_recursive(tree->right_child);
    }
}
void in_order_traverse_recursive(BTree tree) {
    if(tree) {
        in_order_traverse_recursive(tree->left_child);
        printf("%c ", tree->data);
        in_order_traverse_recursive(tree->right_child);
    }
}
void post_order_traverse_recursive(BTree tree) {
    if(tree) {
        post_order_traverse_recursive(tree->left_child);
        post_order_traverse_recursive(tree->right_child);
        printf("%c ", tree->data);
    }
}

void pre_order_traverse_non_recursive(BTree tree) {
    BT_SStack s;
    bt_linked_stack_init(&s);
    BTNode * p = tree;
    while(p != NULL || (!bt_linked_stack_is_empty(s))) {
        if(p != NULL) {
            printf("%c ", p->data);
            bt_linked_stack_push(&s, p);
            p = p->left_child;
        }
        else {
            bt_linked_stack_pop(&s, &p);
            p = p->right_child;
        }
    }
}
void in_order_traverse_non_recursive(BTree tree) {
    BT_SStack s;
    bt_linked_stack_init(&s);
    BTNode *p = tree;
    while(p != NULL || (!bt_linked_stack_is_empty(s))) {
        if(p != NULL) {
            bt_linked_stack_push(&s, p);
            p = p->left_child;
        }
        else {
            bt_linked_stack_pop(&s, &p);
            printf("%c ", p->data);
            p = p->right_child;
        }
    }
}
void post_order_traverse_non_recursive(BTree tree) {
    /*
    * 	□ 后序遍历的思路和前中序类似，也要借助栈实现，
        □ 第一个指针p，用于遍历树，和承接弹出/获取栈顶元素
        □ 但是区别在于需要用额外指针记录出栈的结点r，以便和下一轮循环时的结点的右子结点比较是否相等
        □ 整体思路是从根开始，一直将左子结点入栈，直到左子结点为空
        □ 然后获取栈顶元素，判断右子结点是否不为空，且右子结点不是刚刚出栈的元素
            ® 不为空，且不是刚刚访问的结点，则
                ◊ 将指针指向右子结点，然后入栈，再从前一步开始操作，依次将左子结点入栈
            ® 为空，或刚刚访问的，则
                ◊ 弹出栈顶元素给p，进行访问
                ◊ 将r指向p
                ◊ 将p置空，由于整个程序使用p进行遍历，不置为空会导致弹出结点重复入栈
     */
    BT_SStack s;
    bt_linked_stack_init(&s);
    BTNode * p = tree;
    BTNode * r = NULL;

    while(p != NULL || (!bt_linked_stack_is_empty(s))) {
        if(p != NULL) {
            bt_linked_stack_push(&s, p);
            p = p->left_child;
        }
        else {
            p = bt_linked_stack_get_top(s);
            if(p->right_child && p->right_child != r) {
                p = p->right_child;
            }
            else {
                bt_linked_stack_pop(&s, &p);
                printf("%c ", p->data);
                r = p;
                p = NULL;
            }
        }
    }
}

void level_traverse(BTree tree) {
    BT_Queue q;
    bt_linked_queue_init(&q);

    if(tree != NULL) {
        bt_linked_queue_enqueue(&q, tree);
        while(!bt_linked_queue_is_empty(q)) {
            BTNode * tmp ;
            bt_linked_queue_dequeue(&q, &tmp);
            printf("%c ", tmp->data);
            if (tmp->left_child != NULL)
                bt_linked_queue_enqueue(&q, tmp->left_child);
            if (tmp->right_child != NULL)
                bt_linked_queue_enqueue(&q, tmp->right_child);
        }
    }
}

void copy_binary_tree(BTree src, BTree * tgt) {
    if(src == NULL)
        *tgt = NULL;
    else {
        BTNode * t = (BTNode *) malloc(sizeof(BTNode));
        if(t == NULL)
            exit(EXIT_FAILURE);
        t->data = src->data;
        copy_binary_tree(src->left_child, &t->left_child);
        copy_binary_tree(src->right_child, &t->right_child);
    }
}

int calc_binary_tree_depth(BTree tree) {
    if(tree == NULL)
        return 0;
    int m = calc_binary_tree_depth(tree->left_child);
    int n = calc_binary_tree_depth(tree->right_child);
    if(m >= n)
        return m + 1;
    else
        return n + 1;
}

int calc_binary_tree_nodes(BTree tree) {
    if(tree == NULL)
        return 0;
    return calc_binary_tree_nodes(tree->left_child) + calc_binary_tree_nodes(tree->right_child) + 1;
}
