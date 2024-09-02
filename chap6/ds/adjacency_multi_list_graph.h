//
// Created by lisen on 24-9-2.
//

#ifndef ADJACENCY_MULTI_LIST_GRAPH_H
#define ADJACENCY_MULTI_LIST_GRAPH_H

#if 0
    表示无向图
    综合十字链表和邻接表
    对于每条边 只有一个边结点表示
    同时用两个指针域分别表示依附于对应顶点的边 此处类似于十字链表
    对于表头结点的first_arc链表 使用带有头结点的链表操作更方便
#endif

#include <stdbool.h>

#define MAX_VERTEX 100
typedef char vertex;
typedef bool is_visited;
typedef int weight;

struct arc_node {
    is_visited visite_flag;

    weight w;

    int i_vertex;
    int j_vertex;

    struct arc_node * i_link;
    struct arc_node * j_link;
};

typedef struct arc_node ArcNode;

struct vertex_node {
    vertex data;
    ArcNode * first_arc;
};

typedef struct vertex_node VerNode;

struct adjacency_multi_list_graph {
    VerNode mlist[MAX_VERTEX];
    int vertex_nums;
    int edge_nums;
};

typedef struct adjacency_multi_list_graph AMLGraph;

// 根据结点值，找到该结点在v数组内的下标
// 找不到则返回-1
int amlg_locate_vertex(const AMLGraph g, const vertex v);

// 创建一个无向图
void amlg_create_undirected_graph(AMLGraph * g);

void amlg_display(AMLGraph g);




#endif //ADJACENCY_MULTI_LIST_GRAPH_H
