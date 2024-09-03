//
// Created by lisen on 24-8-30.
//
#include "adjacency_matrix_graph.h"
#include <stdio.h>

// 根据结点值，找到该结点在v数组内的下标
// 找不到则返回-1
int amg_locate_vertex(const AMGraph g, const Vertex v) {
    for(int i = 0; i < g.vertex_nums; i++) {
        if(g.v[i] == v)
            return i;
    }
    return -1;
}

// 创建一个无向图
void amg_create_undirected_graph(AMGraph * g) {
    // 确定图的顶点和边数
    printf("please input vertex numbers\n");
    scanf("%d", &g->vertex_nums);
    printf("please input edge numbers\n");
    scanf("%d", &g->edge_nums);

    // 循环输入各个顶点的值
    for(int i = 0; i < g->vertex_nums; i++) {
        printf("please input no. %d vertex value, no duplicated!\n", i);
        scanf(" %c", &(g->v[i]));
    }

    // 循环，初始化表示顶点关系的矩阵
    // 无向图，初始化为0
    for(int i = 0; i < g->vertex_nums; i++) {
        for(int j = i; j < g->vertex_nums; j++) {  // 此处j = i 是因为无向图的邻接矩阵是对称的
            g->adjacency_matrix[i][j] = 0;
            g->adjacency_matrix[j][i] = 0;
        }
    }

    // 根据边数，循环修改邻接矩阵
    for(int i = 0; i < g->edge_nums; i++) {
        Vertex v1, v2;
        int i1, i2;
        do {
            printf("please input a pair of vertex value for no. %d edge\n", i);
            scanf(" %c %c", &v1, &v2);

            i1 = amg_locate_vertex(*g, v1);
            i2 = amg_locate_vertex(*g, v2);

            if (i1 != -1 && i2 != -1) {
                g->adjacency_matrix[i1][i2] = 1;
                g->adjacency_matrix[i2][i1] = 1;
            }
            else {
                printf("vertex value not exist, please re-enter\n");
            }
        }while(i1 == -1 || i2 == -1);
    }
}

// 创建一个无向网
void amg_create_undirected_net(AMGraph * g) {
    // 确定图的顶点和边数
    printf("please input vertex numbers\n");
    scanf("%d", &g->vertex_nums);
    printf("please input edge numbers\n");
    scanf("%d", &g->edge_nums);

    // 循环输入各个顶点的值
    for(int i = 0; i < g->vertex_nums; i++) {
        printf("please input no. %d vertex value, no duplicated!\n", i);
        scanf(" %c", &(g->v[i]));
    }

    // 循环，初始化表示顶点关系的矩阵
    // 无向图，初始化为0
    for(int i = 0; i < g->vertex_nums; i++) {
        for(int j = i; j < g->vertex_nums; j++) {  // 此处j = i 是因为无向图的邻接矩阵是对称的
            g->adjacency_matrix[i][j] = INFINITE_WEIGHT;
            g->adjacency_matrix[j][i] = INFINITE_WEIGHT;
        }
    }

    // 根据边数，循环修改邻接矩阵
    for(int i = 0; i < g->edge_nums; i++) {
        Vertex v1, v2;
        Edge e;
        int i1, i2;
        do {
            printf("please input a pair of vertex value and edge weight for no. %d edge\n", i);
            scanf(" %c %c %d", &v1, &v2, &e);

            i1 = amg_locate_vertex(*g, v1);
            i2 = amg_locate_vertex(*g, v2);

            if (i1 != -1 && i2 != -1) {
                g->adjacency_matrix[i1][i2] = e;
                g->adjacency_matrix[i2][i1] = e;
            }
            else {
                printf("vertex value not exist, please re-enter\n");
            }
        }while(i1 == -1 || i2 == -1);
    }
}

// 返回无向图中，第一个与指定下标连通的顶点的下标
// 若无连通则返回 -1
int amg_first_adj_vertex_index_undirected_graph(AMGraph g, int v_index) {
    if (v_index < 0 || v_index >= g.vertex_nums) {
        return -1;
    }
    // 因为是无向图，只按照行或列搜索即可
    for(int i = 0; i < g.vertex_nums; i++) {
        if(g.adjacency_matrix[v_index][i] == 1)
            return i;
    }
    return -1;
}

// 返回无向图中，相对于w_index的与v_index对应顶点连通的下一个顶点
// 若无连通则返回 -1
int amg_next_adj_vertex_index_undirected_graph(AMGraph g, int v_index, int w_index) {
    if (v_index < 0 || v_index >= g.vertex_nums) {
        return -1;
    }
    if (w_index < 0 || w_index >= g.vertex_nums) {
        return -1;
    }
    // 因为是无向图，只按照行或列搜索即可
    for(int i = w_index + 1; i < g.vertex_nums; i++) {
        if(g.adjacency_matrix[v_index][i] == 1)
            return i;
    }
    return -1;
}

void amg_dfs(AMGraph g, int v_index, bool * visited) {
    printf(" %c ", g.v[v_index]);
    visited[v_index] = true;
    for(int i = 0; i < g.vertex_nums; i++) {
        // 检查矩阵中第i行的各个单元
        // 递归条件 matrix[v][i] = 1 and visited[i] != true
        if(g.adjacency_matrix[v_index][i] == 1 && visited[i] != true) {
            amg_dfs(g, i, visited);
        }
    }
}

void amg_dfs_traverse(AMGraph g, bool * visited) {
    for(int i = 0; i < g.vertex_nums; i++) {
        visited[i] = false;
    }
    for(int i = 0; i < g.vertex_nums; i++) {
        if(visited[i] == false) {
            amg_dfs(g, i, visited);
        }
    }
}

void amg_bfs(AMGraph g, int v_index, bool * visited) {
    printf(" %c ", g.v[v_index]);
    visited[v_index] = true;

    // 以数组代替队列，使用front 和 rear判断队列是否为空
    // 数组存储g.v的下标
    int queue[g.vertex_nums];
    int front = 0;   // 队首
    int rear = 0;    // 队尾
    for(int i = 0; i < g.vertex_nums; i++)
        queue[i] = -1;

    queue[front] = v_index;
    rear ++;

    while(front != rear) { // 队列非空
        // 从队首弹出一个下标
        int idx = queue[front];
        front ++;

        for(int i = 0; i < g.vertex_nums; i++) {
            if(g.adjacency_matrix[idx][i] == 1 && visited[i] == false) {
                // 边连通，且未被访问，则输出，并入队
                printf(" %c ", g.v[i]);
                visited[i] = true;
                queue[rear] = i;
                rear ++;
            }
        }

    }
}

void amg_bfs_traverse(AMGraph g, bool * visited) {
    for(int i = 0; i < g.vertex_nums; i++) {
        visited[i] = false;
    }
    for(int i = 0; i < g.vertex_nums; i++) {
        if(visited[i] == false) {
            amg_bfs(g, i, visited);
        }
    }
}

void amg_display(AMGraph g) {
    printf("     ");
    for(int i = 0; i < g.vertex_nums; i++) {
        printf("%6c ", g.v[i]);
    }
    putchar('\n');
    for(int i = 0; i < g.vertex_nums; i++) {

        if(i != 0) {
            putchar('\n');
            printf("%6c ", g.v[i]);
        }
        else {
            printf("%6c ", g.v[i]);
        }
        for(int j = 0; j < g.vertex_nums; j++) {
            printf("%6d ", g.adjacency_matrix[i][j]);
        }
    }
}