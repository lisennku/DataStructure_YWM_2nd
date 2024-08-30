//
// Created by lisen on 24-8-30.
//

#include <stdio.h>
#include <stdlib.h>
#include "adjacency_list_graph.h"

// 根据结点值，找到该结点在表头数组内的下标
// 找不到则返回-1
int alg_locate_vertex(const ALGraph g, const vertex v) {
    for(int i = 0; i < g.vertex_nums; i++) {
        if(g.hd[i].data == v)
            return i;
    }
    return -1;
}

// 创建一个无向图
void alg_create_undirected_graph(ALGraph * g) {
    // 确定图的顶点和边数
    printf("please input vertex numbers\n");
    scanf("%d", &g->vertex_nums);
    printf("please input edge numbers\n");
    scanf("%d", &g->edge_nums);

    // 输入图的顶点的值
    for(int i = 0; i < g->vertex_nums; i++) {
        printf("please input no. %d vertex value, no duplicated!\n", i);
        scanf(" %c", &(g->hd[i].data));
        // 因为hd数组中的各个元素是边链表的头结点，所以需要初始化first_arc指针为NULL
        g->hd[i].first_arc = NULL;
    }

    // 根据边的长度，输入边两端的顶点的值
    for(int i = 0; i < g->edge_nums; i++) {
        vertex v1, v2;
        int idx1, idx2;
        do {
            printf("please input a pair of vertex value for no. %d edge\n", i);
            scanf(" %c %c", &v1, &v2);
            idx1 = alg_locate_vertex(*g, v1);
            idx2 = alg_locate_vertex(*g, v2);
            if(idx1 != -1 && idx2 != -1) {
                // 为了方便，边链表的新结点在表头处插入，也即放到顶点所表示的头结点后
                // 因为是无向图
                // 先处理 v1 -> v2 的边
                Arc_Node * arn1 = (Arc_Node *) malloc(sizeof(Arc_Node));
                // 更新索引值
                arn1->adj_idx = idx1;
                // 找到v1对应的表头结点，将当前的first_arc的值，赋值给新结点的next_art
                arn1->next_arc = g->hd[idx1].first_arc;
                g->hd[idx1].first_arc = arn1;

                // 再处理 v2 -> v1 的边
                Arc_Node * arn2 = (Arc_Node *) malloc(sizeof(Arc_Node));
                arn2->adj_idx = idx2;
                arn2->next_arc = g->hd[idx2].first_arc;
                g->hd[idx2].first_arc = arn2;
            }
        }while(idx1 == -1 || idx2 == -1);
    }
}

// 创建一个无向网
void alg_create_undirected_net(ALGraph * g);

void alg_display(ALGraph g) {
    for(int i = 0; i < g.vertex_nums; i++) {
        printf("%c:", g.hd[i]);
        Arc_Node * p = g.hd[i].first_arc;
        while(p) {
            printf(" -> %c", g.hd[p->adj_idx]);
            p = p->next_arc;
        }
        putchar('\n');
    }
}