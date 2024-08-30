//
// Created by lisen on 24-8-30.
//

#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H
#if 0
    使用邻接表表示图
    边结构体
        adj_idx   表示该边指向的顶点 在表头结点表(一维数组)里的下标
        info      边的相关信息
        *next_arc 指向该边链表属于的顶点的下一个邻接点
    表头结构
        data      顶点的数据
        first_arc 与该顶点相邻的第一个顶点的边
    图结构体
        表头结构数组
        vertex_nums
        edge_nums
#endif

#define MAX_VERTEX_NUM  100
typedef int weight;
typedef char vertex;

// 边链表结点结构类型
struct edge_node {
    int adj_idx;                    // 边指向的顶点，所在表头数组的下标
    weight w;                       // 边的权重
    struct edge_node * next_arc;    // 指向下一个与顶点邻接的边结点
};
typedef struct edge_node Arc_Node;

struct header_node {
    vertex data;                      // 表头结点代表的顶点的值
    Arc_Node * first_arc;           // 与顶点邻接的第一个边结点
};
typedef struct header_node Header_Node;

struct adjacency_list_graph {
    Header_Node hd[MAX_VERTEX_NUM]; // 表头
    int vertex_nums;                // 顶点数
    int edge_nums;                  // 边数
};
typedef struct adjacency_list_graph ALGraph;

// 根据结点值，找到该结点在表头数组内的下标
// 找不到则返回-1
int alg_locate_vertex(const ALGraph g, const vertex v);

// 创建一个无向图
void alg_create_undirected_graph(ALGraph * g);

// 创建一个无向网
void alg_create_undirected_net(ALGraph * g);

void alg_display(ALGraph g);



#endif //ADJACENCY_LIST_GRAPH_H
