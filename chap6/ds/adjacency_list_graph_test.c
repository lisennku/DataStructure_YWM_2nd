//
// Created by lisen on 24-8-30.
//
#include "adjacency_list_graph.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {

    ALGraph g;
    ALGraph ig;
    alg_create_undirected_graph(&g);
    // amg_create_undirected_net(&g);
    // alg_create_directed_graph_w_inverse(&g, &ig);
    // alg_display(g);
    // alg_display(ig);
    bool visited[g.vertex_nums];
    alg_dfs_traverse(g, visited);  // 因为邻接表中，边链表的插入是头插法，所以输出顺序和邻接矩阵不同，但只是顺序不同而已
    return 0;
}
