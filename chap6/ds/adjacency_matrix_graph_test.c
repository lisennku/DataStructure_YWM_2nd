//
// Created by lisen on 24-8-30.
//

#include "adjacency_matrix_graph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    AMGraph g;
    // amg_create_undirected_graph(&g);
    amg_create_undirected_net(&g);
    amg_display(g);
    putchar('\n');
    // bool visited[g.vertex_nums];
    //
    // amg_bfs_traverse(g, visited);
    // amg_minimum_span_tree_prim(g, 'a');
    amg_minimum_span_tree_kruskal(g);
    return 0;
}
