//
// Created by lisen on 24-8-29.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "huffman_tree.h"

void select_index_for_two_min_value(HT_Tree ht, int end_pos, int * idx1, int * idx2) {
    int min1 = INT_MAX;
    int min2 = INT_MAX;
    *idx1 = -1;
    *idx2 = -1;
    for(int i = 1; i <= end_pos; i++) {
        if(ht[i].parent != 0)
            continue;
        if(ht[i].weight < min1) {
            min1 = ht[i].weight;
            *idx1 = i;
        }
    }
    for(int i = 1; i <= end_pos; i++) {
        if(ht[i].parent != 0 || i == *idx1)
            continue;
        if(ht[i].weight < min2) {
            min2 = ht[i].weight;
            *idx2 = i;
        }
    }
}
void create_huffman_tree(HT_Tree * ht, int n) {
    int m = 2 * n - 1;
    // 数组动态分配内存
    *ht = (HT_Node *) malloc(sizeof(HT_Node) * (m + 1));
    if(*ht == NULL)
        exit(EXIT_FAILURE);

    // 初始化数组
    for(int i = 1; i <= m; i++) {
        (*ht)[i].weight = 0;
        (*ht)[i].parent = 0;
        (*ht)[i].left_child = 0;
        (*ht)[i].right_child = 0;
    }

    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    for(int i = 1; i <= n; i++) {
        // scanf("%d", &(*ht)[i].weight);
        (*ht)[i].weight = arr[i-1];
    }

    // for(int i = 1; i <= m; i ++)
    //     printf("node %d: weight %d, parent %d, left %d, right %d\n", i, (*ht)[i].weight, (*ht)[i].parent, (*ht)[i].left_child, (*ht)[i].right_child);

    for(int i = n + 1; i <= m; i++) {
        int idx1, idx2;
        select_index_for_two_min_value(*ht, i-1, &idx1, &idx2);
        // printf("loop %d: idx1 %d, idx2 %d \n", i-n, idx1, idx2);

        (*ht)[idx1].parent = i;
        (*ht)[idx2].parent = i;

        (*ht)[i].weight = (*ht)[idx1].weight + (*ht)[idx2].weight;
        (*ht)[i].left_child = idx1;
        (*ht)[i].right_child = idx2;
    }
}
void pre_order_traverse_huffman_tree(HT_Tree ht, int node) {
    if (node == 0) {
        return;
    }

    printf("Node %d: Weight = %d, Parent = %d, Left Child = %d, Right Child = %d\n",
            node, ht[node].weight, ht[node].parent, ht[node].left_child, ht[node].right_child);
    pre_order_traverse_huffman_tree(ht, ht[node].left_child);

    pre_order_traverse_huffman_tree(ht, ht[node].right_child);
}
int calc_huffman_tree_weighted_path_length(HT_Tree ht, int pos, int path_length) {
    if(pos == 0)
        return 0;
    if(ht[pos].left_child == 0 && ht[pos].right_child == 0) {
        printf("weight %d, path length %d\n", ht[pos].weight, path_length);
        return ht[pos].weight * path_length;
    }

    return calc_huffman_tree_weighted_path_length(ht, ht[pos].left_child, path_length + 1)
        + calc_huffman_tree_weighted_path_length(ht, ht[pos].right_child, path_length + 1);
}
void generate_huffman_code(HT_Tree ht, int n, HT_Code * code) {
    /*
     * ht是一个数组，前n个元素为叶结点
     * 从叶结点开始，向树根出发找寻，每次判断当前节点是其父节点的左还是右，并对应赋值0/1
     * 编码保存在二维的char数组code里
     * 使用临时char数组，从后向前存储编码，因为正常的哈夫曼编码是从根向叶结点
     * 参数code使用地址传参，因为在主函数内部只是声明了该变量，初始化等操作在函数内，所以必须使用地址传参
     */
    // 为code分配行数，从1开始，因此要n+1
    *code = (char **) malloc(sizeof(char *) * (n + 1));
    char * tmp = (char *) malloc(sizeof(char) * n);
    tmp[n-1] = '\0';


    for(int i = 1; i <= n; i++) {
        // tmp数组存储字符开始的位置
        int start = n - 1;

        // 从ht下标1开始，读取每个叶结点
        int parent_idx = ht[i].parent;
        int child_idx = i;

        while(parent_idx != 0) {
            start -- ; // 因为start赋值n-1，所以进入循环要先减1
            if(ht[parent_idx].left_child == child_idx)
                tmp[start] = '0';
            else
                tmp[start] = '1';

            child_idx = parent_idx;
            parent_idx = ht[parent_idx].parent;
        }

        // 循环结束，说明此时该叶结点编码已经完成
        // 为该编码动态分配内存，其长度为n-start，包含了'\0'的长度
        (*code)[i] = (char *) malloc(sizeof(char) * (n - start));
        strcpy((*code)[i], tmp+start);
    }
    free(tmp);
}