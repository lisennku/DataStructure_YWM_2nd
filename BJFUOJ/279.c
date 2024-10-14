//
// Created by lisen on 24-10-14.
//
// https://www.bjfuacm.com/problem/279


#include <stdio.h>

#define CONNECTED 1
#define DISCONNECTED 0

#define MAX_VERTEX 100

typedef struct {
    int vertex[MAX_VERTEX];
    int adj_matrix[MAX_VERTEX][MAX_VERTEX];
    int vertex_nums;
    int edge_nums;
} AMGraph;

void init_graph(AMGraph * graph) {
    graph->vertex_nums = 0;
    graph->edge_nums = 0;
}

int locate_vertex_graph(AMGraph graph, int vertex) {
    for(int i = 0; i < graph.vertex_nums; i++)
        if(graph.vertex[i] == vertex)
            return i;
    return -1;
}

void create_graph(AMGraph * graph, int input_vertex, int input_edge) {
    for(int i = 1; i <= input_vertex; i++) {
        graph->vertex[graph->vertex_nums] = i;
        graph->vertex_nums++;
    }

    for(int i = 0; i < graph->vertex_nums; i++)
        for(int j = i; j < graph->vertex_nums; j++)
            graph->adj_matrix[i][j] = graph->adj_matrix[j][i] = DISCONNECTED;

    for(int i = 0; i < input_edge; i++) {
        int h, t;
        scanf("%d %d", &h, &t);
        int idx_h = locate_vertex_graph(*graph, h);
        int idx_t = locate_vertex_graph(*graph, t);
        if(idx_h != -1 && idx_t != -1)
            graph->adj_matrix[idx_h][idx_t] = graph->adj_matrix[idx_t][idx_h] = CONNECTED;

        graph->edge_nums += 2;
    }
}

void insert_vertex_graph(AMGraph * graph, int vertex) {
    graph->vertex[graph->vertex_nums] = vertex;
    graph->vertex_nums ++;
    for(int i = 0; i < graph->vertex_nums; i++)
        graph->adj_matrix[i][graph->vertex_nums-1] = graph->adj_matrix[graph->vertex_nums-1][i] = DISCONNECTED;
}

void insert_edge_graph(AMGraph * graph, int edge_h, int edge_t) {
    int idx_h = locate_vertex_graph(*graph, edge_h);
    int idx_t = locate_vertex_graph(*graph, edge_t);
    if(idx_h != -1 && idx_t != -1) {
        graph->adj_matrix[idx_h][idx_t] = graph->adj_matrix[idx_t][idx_h] = CONNECTED;
    }
}

void display_graph(AMGraph graph) {
    printf("0 ");
    for(int i = 0; i < graph.vertex_nums; i++) {
        if(i == graph.vertex_nums-1)
            printf("%d\n", graph.vertex[i]);
        else
            printf("%d ", graph.vertex[i]);
    }
    for(int i = 0; i < graph.vertex_nums; i++, printf("\n")) {
        printf("%d ", graph.vertex[i]);
        for(int j = 0; j < graph.vertex_nums; j++) {
            if(j == graph.vertex_nums-1)
                printf("%d", graph.adj_matrix[i][j]);
            else
                printf("%d ", graph.adj_matrix[i][j]);
        }
    }
}


int main() {
    int input_vertex, input_edge;
    AMGraph g;

    while(1) {
        init_graph(&g);
        scanf("%d %d", &input_vertex, &input_edge);
        if(input_edge == 0 && input_vertex == 0)
            break;

        create_graph(&g, input_vertex, input_edge);

        int new_edge_h, new_edge_t;
        scanf("%d %d", &new_edge_h, &new_edge_t);
        insert_edge_graph(&g, new_edge_h, new_edge_t);
        display_graph(g);
    }


    return 0;
}

