//
// Created by lisen on 24-8-30.
//
#include "adjacency_list_graph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    ALGraph g;
    alg_create_undirected_graph(&g);
    // amg_create_undirected_net(&g);
    alg_display(g);

    return 0;
}
