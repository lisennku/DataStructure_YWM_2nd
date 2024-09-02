//
// Created by lisen on 24-9-2.
//
#include <stdio.h>
#include "adjacency_multi_list_graph.h"

int main() {
    AMLGraph g;
    amlg_create_undirected_graph(&g);
    amlg_display(g);
}
