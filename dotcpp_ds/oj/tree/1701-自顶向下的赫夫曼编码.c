//
// Created by lisen on 24-11-5.
//
// https://www.dotcpp.com/oj/problem1701.html

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ** HuffmanCode;

typedef struct HuffmanNode {
    int visited;
    int weight;
    int parent;
    int left;
    int right;
}HuffmanNode, * HuffmanTree;

void select_two_min_idx(HuffmanTree hf, int end_position, int * idx1, int * idx2) {
    int min1 = INT_MAX;
    int min2 = INT_MAX;

    *idx1 = *idx2 = -1;

    for(int i = 1; i <= end_position; i++) {
        if(hf[i].parent != 0)
            continue;
        if(min1 > hf[i].weight) {
            min1 = hf[i].weight;
            *idx1 = i;
        }
    }

    for(int i = 1; i <= end_position; i++) {
        if(hf[i].parent != 0 || i == *idx1)
            continue;
        if(min2 > hf[i].weight) {
            min2 = hf[i].weight;
            *idx2 = i;
        }
    }
    // 一致性保证 左子结点是小序号 右子结点是大序号
    int tmp = *idx1;
    if(*idx1 > *idx2) {
        *idx1 = *idx2;
        *idx2 = tmp;
    }

}

void hfm_tree_init(HuffmanTree * hf, int * array, int size) {
    int m = 2 * size - 1;
    *hf = calloc(m + 1, sizeof(HuffmanNode));
    if(*hf == NULL)
        exit(EXIT_FAILURE);

    // 初始化 位置0废弃不用
    // 初始化数组
    for(int i = 1; i <= m; i++) {
        (*hf)[i].weight = 0;
        (*hf)[i].parent = 0;
        (*hf)[i].left = 0;
        (*hf)[i].right = 0;
    }

    for(int i = 1; i <= size; i++)
        (*hf)[i].weight = array[i-1];
}

void hfm_tree_create(HuffmanTree * hf, int size) {
    int m = 2 * size - 1;

    for(int i = size + 1; i <= m; i ++) {
        int idx1, idx2;
        select_two_min_idx(*hf, i - 1, &idx1, &idx2);
        // printf("%d %d\n", idx1, idx2);
        (*hf)[idx1].parent = (*hf)[idx2].parent = i;
        (*hf)[i].weight = (*hf)[idx1].weight + (*hf)[idx2].weight;
        (*hf)[i].left = idx1;
        (*hf)[i].right = idx2;
    }
}

void hfm_tree_code_create(HuffmanTree hf, HuffmanCode * code, int size) {
    // 从根根结点向左子树深度遍历 并记录遍历次数
    int m = 2 * size - 1;

    *code = (char **) calloc(size + 1, sizeof(char *));
    char * tmp = (char *) calloc(size, sizeof(char));
    int tmp_len = 0;

    while(m) {
        if(hf[m].visited == 0) {
            hf[m].visited = 1;
            if(hf[m].left !=  0) {
                hf[m].visited = 1;
                m = hf[m].left;
                tmp[tmp_len++] = '0';
            }
            else {
                // 表示叶结点完成遍历
                (*code)[m] = calloc(tmp_len+1, sizeof(char));
                tmp[tmp_len] = '\0';
                strcpy((*code)[m], tmp);
            }
        }
        else if(hf[m].visited == 1) {
            hf[m].visited = 2;
            if(hf[m].right != 0) {
                m = hf[m].right;
                tmp[tmp_len++] = '1';
            }
        }
        else {
            tmp_len --;
            m = hf[m].parent;
        }
    }
}

void hfm_display(HuffmanTree hf, int size) {
    int m = 2 * size - 1;
    printf("  %10s %10s %10s %10s\n", "weight", "parent", "left", "right");
    for(int i = 1; i <= m; i++) {
        printf("%d  ", i);
        printf("%10d %10d %10d %10d\n", (hf)[i].weight, (hf)[i].parent, (hf)[i].left, (hf)[i].right);
    }
}

int main() {
    HuffmanTree hf;
    HuffmanCode code;
    int cnt;
    scanf("%d", &cnt);
    int * array = calloc(cnt, sizeof(int));
    if(array == NULL)
        exit(EXIT_FAILURE);

    for(int i = 0; i < cnt; i++)
        scanf("%d", &array[i]);

    hfm_tree_init(&hf, array, cnt);
    hfm_tree_create(&hf, cnt);
    hfm_display(hf, cnt);
    hfm_tree_code_create(hf, &code, cnt);

    for(int i = 1; i <= cnt; i++)
        printf("%s\n", code[i]);


    return 0;
}

























