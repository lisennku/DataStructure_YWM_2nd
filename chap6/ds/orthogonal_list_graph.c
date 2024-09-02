//
// Created by lisen on 24-9-2.
//
#include <stdio.h>
#include <stdlib.h>
#include "orthogonal_list_graph.h"

// 根据结点值，找到该结点在表头数组内的下标
// 找不到则返回-1
int olg_locate_vertex(const OLGraph g, const vertex v) {
    for(int i = 0; i < g.vertex_nums; i++) {
        if(g.xlist[i].data == v)
            return i;
    }
    return -1;
}

// 创建一个有向图
void olg_create_directed_graph(OLGraph * g) {
    // 确定图的顶点和边数
    printf("please input vertex numbers\n");
    scanf("%d", &g->vertex_nums);
    printf("please input edge numbers\n");
    scanf("%d", &g->edge_nums);

    // 输入顶点数据
    for(int i = 0; i < g->vertex_nums; i++) {
        printf("please input no. %d vertex value, no duplicated!\n", i);
        scanf(" %c", &(g->xlist[i].data));
        // 将头结点的in/out初始化为NULL
        g->xlist[i].in = NULL;
        g->xlist[i].out = NULL;
    }

    // 根据边的数量，输入边的弧尾弧头，先输入弧尾，再输入弧头
    for(int i = 0; i < g->edge_nums; i++) {
        vertex arc_tail, arc_head;
        int idx_tail, idx_head;

        do {
            printf("please input a pair of vertex value for no. %d edge\n", i);
            scanf(" %c %c", &arc_tail, &arc_head);
            idx_tail = olg_locate_vertex(*g, arc_tail);
            idx_head = olg_locate_vertex(*g, arc_head);
            if(idx_tail != -1 && idx_head != -1) {
                // 先创建一个弧结点，初始tail_link和head_link为NULL
                ArcNode * new_arc_node = (ArcNode *) malloc(sizeof(ArcNode));
                if(new_arc_node == NULL)
                    exit(-1);
                new_arc_node->tail_vertex = idx_tail;
                new_arc_node->head_vertex = idx_head;
                new_arc_node->tail_link = NULL;
                new_arc_node->head_link = NULL;

                // 插入新结点时，采取尾插法
                ArcNode * t;
                ArcNode * h;
                // 更新弧尾链表
                t = g->xlist[idx_tail].out;
                if(t == NULL)  // 初始情况时
                    g->xlist[idx_tail].out = new_arc_node;
                else {
                    while(t->tail_link != NULL) {
                        t = t->tail_link;
                    }
                    t->tail_link = new_arc_node;
                }
                // 更新弧头链表
                h = g->xlist[idx_head].in;
                if(h == NULL)  // 初始情况时
                    g->xlist[idx_head].in = new_arc_node;
                else {
                    while(h->head_link != NULL) {
                        h = h->head_link;
                    }
                    h->head_link = new_arc_node;
                }
            }
            else {
                printf("vertex value not exist, please re-enter\n");
            }
        }while(idx_tail == -1 || idx_head == -1);
    }
}

void olg_display(OLGraph g) {
    for(int i = 0; i < g.vertex_nums; i++) {
        printf("arc ends with %c :\n", g.xlist[i].data);
        ArcNode * p = g.xlist[i].in;
        while(p != NULL) {
            printf("    index %d, %c -> %c\n", p->tail_vertex, g.xlist[p->tail_vertex].data, g.xlist[i].data);
            p = p->head_link;
        }

        printf("arc start with %c :\n", g.xlist[i].data);
        p = g.xlist[i].out;
        while(p != NULL) {
            printf("    index %d, %c -> %c\n", p->head_vertex, g.xlist[i].data, g.xlist[p->head_vertex].data);
            p = p->tail_link;
        }

    }
}