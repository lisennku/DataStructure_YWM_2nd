//
// Created by lisen on 24-8-30.
//

#include "adjacency_matrix_graph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    AMGraph g;
    // amg_create_undirected_graph(&g);
    amg_create_directed_net(&g);
    amg_display(g);
    putchar('\n');
    // bool visited[g.vertex_nums];
    //
    // amg_bfs_traverse(g, visited);
    // amg_minimum_span_tree_prim(g, 'a');
    // amg_minimum_span_tree_kruskal(g);
    bool s[g.vertex_nums];
    Edge d[g.vertex_nums];
    int  path[g.vertex_nums];
    amg_shortest_path_dijkstra(g, 0, s, d, path);

    for(int i = 0; i < g.vertex_nums; i++)
        printf("index %d preceding %d\n", i, path[i]);

    amg_dijkstra_path_display(g, path, 0);
    return 0;

}
