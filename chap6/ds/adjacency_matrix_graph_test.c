//
// Created by lisen on 24-8-30.
//

#include "adjacency_matrix_graph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    AMGraph g;
    amg_create_undirected_graph(&g);
    // amg_create_undirected_net(&g);
    amg_display(g);
    int i = amg_first_adj_vertex_index_undirected_graph(g, 0);
    printf("\n%d", i);
    int j = amg_next_adj_vertex_index_undirected_graph(g, 0, 1);
    printf("\n%d", j);

    return 0;
}
