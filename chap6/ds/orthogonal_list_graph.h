//
// Created by lisen on 24-9-2.
//

#ifndef ORTHOGONAL_LIST_GRAPH_H
#define ORTHOGONAL_LIST_GRAPH_H
#if 0
    十字链表 是用于存储有向图的链式表达
        类似邻接表 也分两类结点
            1. 头结点
                存储图的顶点信息
            2. 弧结点
                存储每个弧的信息
        头结点
            data      数据域
            first_in  以顶点为弧头的第一个弧
            first_out 以顶点为弧尾的第一个弧
        弧结点
            head_vertex  该弧的弧头所在数组的下标
            tail_vertex  该弧的弧尾所在数组的下标
            head_arc     同一个弧头的下一个弧的地址
            tail_arc     同一个弧尾的下一个弧的地址
            info         弧的信息
#endif

#define MAX_VERTEX 100
typedef int weight;
typedef char vertex;

struct arc_node {
    int head_vertex;
    int tail_vertex;
    struct arc_node * head_link;
    struct arc_node * tail_link;
    int info;
};

typedef struct arc_node ArcNode;

struct vertex_node {
    vertex data;
    ArcNode * in;
    ArcNode * out;
};

typedef struct vertex_node VerNode;

struct orthogonal_list_graph {
    VerNode xlist[MAX_VERTEX];
    int vertex_nums;
    int edge_nums;
};

typedef struct orthogonal_list_graph OLGraph;

// 根据结点值，找到该结点在表头数组内的下标
// 找不到则返回-1
int olg_locate_vertex(const OLGraph g, const vertex v);

// 创建一个有向图
void olg_create_directed_graph(OLGraph * g);

void olg_display(OLGraph g);



#endif //ORTHOGONAL_LIST_GRAPH_H
