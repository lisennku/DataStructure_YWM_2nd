//
// Created by lisen on 24-10-15.
//
// https://leetcode.cn/problems/course-schedule-ii/description/?envType=problem-list-v2&envId=graph

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_COURSES 2100

// 表头元素对应的链表
typedef struct edge {
    int adj_vertex;
    struct edge * next;
}Edge;

// 表头结点表
typedef struct vertex {       // 表头结点表内元素类型
    int header;               // 顶点值
    Edge * first_edge;        // 邻接的第一条边
}Headers;

// 邻接表
typedef struct {
    Headers header[MAX_COURSES];
    int vertex_nums;
    int edge_nums;
}ALGraph;

int locate_vertex(ALGraph graph, int vertex) {
    for(int i = 0; i < graph.vertex_nums; i++)
        if(graph.header[i].header == vertex)
            return i;
    return -1;
}

void create_algraph(ALGraph * graph, int numCourses, int** prerequisites, int prerequisitesSize) {
    graph->edge_nums = graph->vertex_nums = 0;
    // 填充表头结点表
    for(int i = 0; i < numCourses; i++) {
        graph->header[graph->vertex_nums].header = i;
        graph->header[graph->vertex_nums].first_edge = NULL;
        graph->vertex_nums++;
    }

    // 填充表头对应的边链表
    for(int i = 0; i < prerequisitesSize; i++) {
        int edge_h = prerequisites[i][1];
        int edge_t = prerequisites[i][0];

        int idx_h = locate_vertex(*graph, edge_h);
        int idx_t = locate_vertex(*graph, edge_t);
        if(idx_h != -1 && idx_t != -1) {
            Edge * edge = (Edge *) malloc(sizeof(Edge));
            if(edge == NULL)
                exit(EXIT_FAILURE);
            edge->adj_vertex = edge_t;
            edge->next = graph->header[idx_h].first_edge;
            graph->header[idx_h].first_edge = edge;
        }
    }
}

void topo_sort(ALGraph graph,int * res, int * returnSize) {
    // 拓扑序列数组

    int topo_idx = 0;

    // 栈 使用数组代替 最差情况 所有顶点都没有边 所以栈的长度初始化为顶点数
    int stack[graph.vertex_nums];
    int rear = 0;
    // 栈数组初始化
    for(int i = 0; i < graph.vertex_nums; i++)
        stack[i] = -1;

    // 入度数组 初始化后再计算
    int in_degrees[graph.vertex_nums];

    for(int i = 0; i < graph.vertex_nums; i++)
        in_degrees[i] = 0;   // 初始化

    for(int i = 0; i < graph.vertex_nums; i++) {

        Edge * edge = graph.header[i].first_edge;
        while(edge != NULL) {
            in_degrees[edge->adj_vertex] += 1;
            edge = edge->next;
        }
    }

    // 将所有入度为0的顶点的序号入栈
    for(int i = 0; i < graph.vertex_nums; i++)
        if(in_degrees[i] == 0) {
            stack[rear] = i;
            rear ++;
        }

    // 根据拓扑排序算法 依次将入度为0的顶点序号出栈 然后将该顶点从图中去掉 并将新产生的入度为0的顶点入栈
    // 直到栈为空 也即rear == 0
    while(rear != 0) {
        // 将栈顶元素出栈
        int top_idx = stack[--rear];

        // 栈顶元素保存到TOPO序列
        res[topo_idx] = top_idx;
        topo_idx ++;

        // 将该栈顶对应的顶点的弧头入度减一
        Edge * edge = graph.header[top_idx].first_edge;
        while(edge != NULL) {
            in_degrees[edge->adj_vertex]--;

            // 如果此时入度为0 入栈
            if(in_degrees[edge->adj_vertex] == 0)
                stack[rear++] = edge->adj_vertex;

            edge = edge->next;
        }
    }


    if(topo_idx == graph.vertex_nums)
        *returnSize = topo_idx;
    else
        *returnSize = 0;
}


int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize) {
    ALGraph graph;
    create_algraph(&graph, numCourses, prerequisites, prerequisitesSize);
    int * res = (int *) malloc(sizeof(int) * graph.vertex_nums);
    topo_sort(graph, res, returnSize);
    return res;
}

int main() {
    // int tmp[5][2]= {
    //     {0, 1},
    //     {1, 4},
    //     {4, 3},
    //     {3, 2},
    //     {0, 2},
    // };
    int rows = 0;
    int tmp[0][2];

    int numCourses = 1;
    int **prerequisites = malloc(sizeof(int *) * rows);

    for(int i = 0; i < rows; i++) {
        prerequisites[i] = (int *) malloc(sizeof(int) * 2);
        prerequisites[i][0] = tmp[i][0];
        prerequisites[i][1] = tmp[i][1];
    }

    int returnSize;
    int * res = findOrder(numCourses, prerequisites, rows, NULL, &returnSize);

    if(returnSize == 0)
        printf("NO Data\n");
    else {
        for(int i = 0; i < returnSize; i++)
            printf("%d ", res[i]);
    }

    return 0;
}