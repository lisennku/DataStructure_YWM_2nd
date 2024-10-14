//
// Created by lisen on 24-10-14.
//
// https://www.bjfuacm.com/problem/277


#include <stdio.h>
#include <stdlib.h>

/*
 * 图的邻接表示法
 *  使用链表表示每个顶点的边 结点类型包括边的另一端的顶点值 下一个边的指针
 *  使用一维数组存储顶点 数组元素类型应该包括 1. 顶点值 2. 第一个邻接边
 * 邻接表示法的最终类型 包括
 *  一维数组 表示表头顶点
 *  边的数量
 *  顶点的数量
 */

#define MAX_VERTEX 100

typedef struct edge {         // 链表 表示从表头结点表对应结点发出的边
    int vertex;               // 边的另一端的顶点值
    int weight;               // 边的权重
    struct edge * next;       // 下一条边
}Edge;

typedef struct vertex {       // 表头结点表内元素类型
    int header;               // 顶点值
    Edge * first_edge;   // 邻接的第一条边
}Headers;

typedef struct {
    Headers headers[MAX_VERTEX];  // 表头结点表
    int vertex_nums;              // 顶点数量
    int edge_nums;                // 边数
}ALGraph;

void init_algraph(ALGraph * graph) {
    graph->vertex_nums = 0;
    graph->edge_nums = 0;
}

int locate_vertex_graph(ALGraph graph, int vertex) {
    for(int i = 0; i < graph.vertex_nums; i++)
        if(graph.headers[i].header == vertex)
            return i;
    return -1;
}

void create_algraph(ALGraph * graph, int input_vertex, int input_edge) {
    // 为表头顶点表赋值
    for(int i = 1; i <= input_vertex; i++) {
        graph->headers[graph->vertex_nums].header = i;
        graph->headers[graph->vertex_nums].first_edge = NULL;
        graph->vertex_nums ++;

    }

    // 根据输入的边 为表头顶点表的每个顶点创建对应的链表

    for(int i = 0; i < input_edge; i++) {
        int h, t;
        scanf("%d %d", &h, &t);
        int idx_h, idx_t;
        idx_h = locate_vertex_graph(*graph, h);
        idx_t = locate_vertex_graph(*graph, t);
        if(idx_h != -1 && idx_t != -1) {
            // 先处理 h -> t 新链表结点插入头位置
            Edge * h2t = (Edge *) malloc(sizeof(Edge));
            if(h2t == NULL)
                exit(EXIT_FAILURE);
            h2t->vertex = t;
            h2t->weight = -1;
            h2t->next = graph->headers[idx_h].first_edge;
            graph->headers[idx_h].first_edge = h2t;

            // 再处理 t -> h 新链表结点插入头位置
            Edge * t2h = (Edge *) malloc(sizeof(Edge));
            if(t2h == NULL)
                exit(EXIT_FAILURE);
            t2h->vertex = h;
            t2h->weight = -1;
            t2h->next = graph->headers[idx_t].first_edge;
            graph->headers[idx_t].first_edge = t2h;

            graph->edge_nums += 2;
        }
    }
}

void insert_vertex_algraph(ALGraph * graph, int vertex_val) {
    graph->headers[graph->vertex_nums].header = vertex_val;
    graph->headers[graph->vertex_nums].first_edge = NULL;
    graph->vertex_nums ++;
}

void insert_edge_algraph(ALGraph * graph, int vertex_val, int edge_val);

void delete_vertex_algraph(ALGraph * graph, int vertex) {
    int idx_del = locate_vertex_graph(*graph, vertex);

    if(idx_del != -1) {
        /*
         * 先删除对应位置的链表
         * 删除时应注意 需要删除两部分
         *  一部分是被删除顶点所对应的链表
         *  另一部分是被删除顶点的边 对应的另一端顶点链表里的结点
         */
        Edge * del = graph->headers[idx_del].first_edge;
        while(del != NULL) {
            Edge * cur = del;
            // 边的邻接顶点 检索被删除的顶点的结点
            int adj_vertex_idx = locate_vertex_graph(*graph, cur->vertex);
            if(adj_vertex_idx != -1) {
                Edge * adj_prev = NULL;
                Edge * adj_cur = graph->headers[adj_vertex_idx].first_edge;
                while(adj_cur->vertex != vertex) {
                    adj_prev = adj_cur;
                    adj_cur = adj_cur->next;
                }
                // 此处判断是因为如果邻接顶点的下一个结点是被删除的顶点
                // 那么需要将该顶点的first_edge进行赋值，而不是adj_prev
                if(adj_prev == NULL)
                    graph->headers[adj_vertex_idx].first_edge = adj_cur->next;
                else
                    adj_prev->next = adj_cur->next;
                free(adj_cur);
            }

            // 删除该顶点的链表
            del = del->next;
            graph->edge_nums -= 2;
            free(cur);
        }
        // 再删除表头顶点位置 其实是后续元素往前挪动
        for(int i = idx_del; i < graph->vertex_nums - 1; i++)
            graph->headers[i] = graph->headers[i+1];
        graph->vertex_nums --;
    }
}

void display_graph(ALGraph graph) {
    for(int i = 0; i < graph.vertex_nums; i++) {
        printf("%d", graph.headers[i].header);
        Edge * edge_node = graph.headers[i].first_edge;
        while(edge_node != NULL) {
            printf(" %d", edge_node->vertex);
            edge_node = edge_node->next;
        }
        printf("\n");
    }

}

int main() {
    int input_vertex, input_edge;
    ALGraph graph;

    while(1) {
        init_algraph(&graph);
        scanf("%d %d", &input_vertex, &input_edge);
        if(input_edge == 0 && input_vertex == 0)
            break;
        create_algraph(&graph, input_vertex, input_edge);
        int del_vertex;
        scanf("%d", &del_vertex);
        delete_vertex_algraph(&graph, del_vertex);
        display_graph(graph);

    }


    return 0;
}