//
// Created by lisen on 24-9-2.
//
#include <stdio.h>
#include "orthogonal_list_graph.h"

int main() {
    OLGraph g;
    olg_create_directed_graph(&g);
    olg_display(g);
}
