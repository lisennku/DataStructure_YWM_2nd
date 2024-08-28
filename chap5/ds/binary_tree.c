//
// Created by lisen on 24-8-27.
//
#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

#include "btnode_queue.h"


void create_binary_tree(BTree * tree) {
    /*
     * 以中序遍历方式创建二叉树
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
     * 以中序遍历方式创建二叉树
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
void post_order_traverse_non_recursive(BTree tree);

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