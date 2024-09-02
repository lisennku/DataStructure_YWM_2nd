//
// Created by lisen on 24-8-30.
//
#include "adjacency_list_graph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    ALGraph g;
    ALGraph ig;
    // alg_create_undirected_graph(&g);
    // amg_create_undirected_net(&g);
    alg_create_directed_graph_w_inverse(&g, &ig);
    // alg_display(g);
    alg_display(ig);

    return 0;
}
