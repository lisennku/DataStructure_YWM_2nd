//
// Created by lisen on 24-9-2.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "adjacency_multi_list_graph.h"

// 根据结点值，找到该结点在v数组内的下标
// 找不到则返回-1
int amlg_locate_vertex(const AMLGraph g, const vertex v) {
    for(int i = 0; i < g.vertex_nums; i++) {
        if(g.mlist[i].data == v)
            return i;
    }
    return -1;
}

// 创建一个无向图
void amlg_create_undirected_graph(AMLGraph * g) {
    // 确定图的顶点和边数
    printf("please input vertex numbers\n");
    scanf("%d", &g->vertex_nums);
    printf("please input edge numbers\n");
    scanf("%d", &g->edge_nums);

    // 循环输入各个顶点的值
    for(int i = 0; i < g->vertex_nums; i++) {
        printf("please input no. %d vertex value, no duplicated!\n", i);
        scanf(" %c", &(g->mlist[i].data));
        // 测试代码发现使用带有头结点的链表更方便
        g->mlist[i].first_arc = (ArcNode *) malloc(sizeof(ArcNode));
        // 初始化
        g->mlist[i].first_arc->i_link = NULL;
        g->mlist[i].first_arc->j_link = NULL;
        g->mlist[i].first_arc->i_vertex = -1;
        g->mlist[i].first_arc->j_vertex = -1;
        g->mlist[i].first_arc->w = -1;
        g->mlist[i].first_arc->visite_flag = false;
    }

    // 根据边的数量，输入边
    for(int i = 0; i < g->edge_nums; i++) {
        vertex vi, vj;
        int idx_i, idx_j;
        do {
            printf("please input a pair of vertex value for no. %d edge\n", i);
            scanf(" %c %c", &vi, &vj);
            idx_i = amlg_locate_vertex(*g, vi);
            idx_j = amlg_locate_vertex(*g, vj);

            if(idx_i != -1 && idx_j != -1) {
                ArcNode * new = (ArcNode *)malloc(sizeof(ArcNode));
                if(new == NULL)
                    exit(-1);
                // 初始化边结点的成员
                new->visite_flag = false;
                new->w = 0;
                new->i_vertex = idx_i;
                new->j_vertex = idx_j;
                new->i_link = NULL;
                new->j_link = NULL;

                ArcNode * p ;
                // 更新i对应的表头结点
                p = g->mlist[idx_i].first_arc;
                while(p->i_link != NULL)
                    p = p->i_link;
                p->i_link = new;

                // 更新j对应的表头结点
                p = g->mlist[idx_j].first_arc;
                while(p->j_link != NULL)
                    p = p->j_link;
                p->j_link = new;

            }
            else {
                printf("vertex value not exist, please re-enter\n");
            }
        }while(idx_i == -1 || idx_j == -1);
    }
}

void amlg_display(AMLGraph g) {
    for(int i = 0; i < g.vertex_nums; i++) {
        ArcNode * p = g.mlist[i].first_arc->i_link;
        while(p != NULL) {
            if(!p->visite_flag) {
                printf("%c <-> %c\n", g.mlist[i].data, g.mlist[p->j_vertex].data);
                p->visite_flag = true;
            }
            p = p->i_link;  // 不需要在遍历j_link，因为会在其他顶点遍历时访问到
        }
    }
}