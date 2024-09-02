//
// Created by lisen on 24-8-30.
//

#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H
#if 0
    使用邻接矩阵表示图
    直接使用结构体表示图
    结构体内容
        - 二维数组
            表示顶点之间是否相连(1表示邻接 0表示不邻接)
            或者
            表示顶点之间边的权重(相连的顶点之间使用具体权重 不相连的使用具体类型的足够大的值表示)
        - 一维数组
            表示各个顶点
        - vertex_cnt 表示当前顶点数
        - edge_cnt 表示当前边数
#endif

#define INFINITE_WEIGHT 40000
#define MAX_VERTEX_NUM  100


typedef char Vertex;
typedef int  Edge;

// 直接在结构体中定义长度，后序遍历通过vertex_nums/edge_nums进行下标控制
// 后续也可以考虑采用动态内存分配
// 默认表示顶点的字符没有重复的
struct adjacency_matrix_graph {
    Vertex v[MAX_VERTEX_NUM];
    Edge adjacency_matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vertex_nums;
    int edge_nums;
};

typedef struct adjacency_matrix_graph AMGraph;

// 根据结点值，找到该结点在v数组内的下标
// 找不到则返回-1
int amg_locate_vertex(const AMGraph g, const Vertex v);

// 创建一个无向图
void amg_create_undirected_graph(AMGraph * g);

// 创建一个无向网
void amg_create_undirected_net(AMGraph * g);

// 返回无向图中，第一个与指定下标连通的顶点的下标
// 若无连通则返回 -1
int amg_first_adj_vertex_index_undirected_graph(AMGraph g, int v_index);

// 返回无向图中，相对于w_index的与v_index对应顶点连通的下一个顶点
// 若无连通则返回 -1
int amg_next_adj_vertex_index_undirected_graph(AMGraph g, int v_index, int w_index);

void amg_display(AMGraph g);




#endif //ADJACENCY_MATRIX_GRAPH_H
