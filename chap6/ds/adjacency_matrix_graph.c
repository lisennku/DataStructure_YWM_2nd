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

// 创建一个有向网
void amg_create_directed_net(AMGraph * g) {
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

int amg_find_min_cost_index_closedge(int n, CEdge closedge[n]) {
    Edge tmp = INFINITE_WEIGHT;
    int idx ;
    for(int i = 0; i < n; i++) {
        if(closedge[i].low_cost == 0)
            continue;
        if(closedge[i].low_cost < tmp) {
            tmp = closedge[i].low_cost;
            idx = i;
        }
    }
    return idx;
}

void amg_minimum_span_tree_prim(AMGraph g, Vertex v) {
    int k = amg_locate_vertex(g, v);
    // 创建closedge数组
    CEdge closedge[g.vertex_nums];
    // 初始化closedge数组
    for(int i = 0; i < g.vertex_nums; i++) {
        if(i != k) {
            closedge[i].adjvex = v;
            closedge[i].low_cost = g.adjacency_matrix[k][i];
        }
    }
    closedge[k].adjvex = v;
    closedge[k].low_cost = 0;

    // 循环n-1次
    for(int i = 1; i < g.vertex_nums; i++) {
        k = amg_find_min_cost_index_closedge(g.vertex_nums, closedge);
        printf("%c %c \n", closedge[k].adjvex, g.v[k]);
        closedge[k].low_cost = 0;
        for(int i = 0; i < g.vertex_nums; i++) {
            if(g.adjacency_matrix[k][i] < closedge[i].low_cost) {
                closedge[i].adjvex = g.v[k];
                closedge[i].low_cost = g.adjacency_matrix[k][i];
            }
        }
    }
}

void amg_sort_edges(Edge_Collect * edges, int n) {
    Edge tmp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(edges[i].weight > edges[j].weight) {
                Edge_Collect tmp;
                tmp = edges[i];
                edges[i] = edges[j];
                edges[j] = tmp;
            }
        }
    }
}

void amg_minimum_span_tree_kruskal(AMGraph g) {
    // 创建Edge_Collect数组，赋值并排序
    Edge_Collect edges[g.edge_nums];
    int tmp_idx = 0;
    // 给edges数组赋值，因为是无向图，只扫描矩阵上三角部分即可
    for(int i = 0; i < g.vertex_nums; i++) {
        for(int j = i; j < g.vertex_nums; j++) {
            if(g.adjacency_matrix[i][j] != INFINITE_WEIGHT) {
                edges[tmp_idx].head = g.v[i];
                edges[tmp_idx].tail = g.v[j];
                edges[tmp_idx].weight = g.adjacency_matrix[i][j];
                tmp_idx ++;
            }
        }
    }

    amg_sort_edges(edges, g.edge_nums);

    // 创建连通分量数组，初始值为下标
    int vexset[g.vertex_nums];
    for(int i = 0; i < g.vertex_nums; i++)
        vexset[i] = i;

    // 算法开始
    // 依次从edges数组中选择权重最小的边，因为已经排序，所以直接从0开始遍历即可
    for(int i = 0; i < g.edge_nums; i++) {
        // 找出顶点的下标
        int idx1 = amg_locate_vertex(g, edges[i].head);
        int idx2 = amg_locate_vertex(g, edges[i].tail);
        // 找出顶点所属的连通分量
        int s1 = vexset[idx1];
        int s2 = vexset[idx2];
        // 属于不同连通分量时
        if(s1 != s2) {
            printf("%c %c\n", edges[i].head, edges[i].tail);
            // 更新连通分量
            // 因为可能存在一个连通分量有多个边，所以要循环
            for(int j = 0; j < g.vertex_nums; j ++) {
                if(vexset[j] == s2)
                    vexset[j] = s1;
            }
        }


    }
}

void amg_shortest_path_dijkstra(AMGraph g, int v_index, bool * s, Edge * d, int * path) {
    // step 1 初始化
    // 注意对v_index的特殊处理
    for(int i = 0; i < g.vertex_nums; i++) {
        s[i] = false;
        d[i] = g.adjacency_matrix[v_index][i];
        path[i] = d[i] < INFINITE_WEIGHT ? v_index : -1;
    }
    d[v_index] = 0;
    s[v_index] = true;

    // step 2 循环n-1次
    for(int i = 1; i < g.vertex_nums; i++) {
        Edge tmp = INFINITE_WEIGHT;
        int idx;
        // 找到当前数组D中最小的权重，注意，要求对应的S为false
        for(int w = 0; w < g.vertex_nums; w++) {
            if(d[w] < tmp && s[w] == false) {
                tmp = d[w];
                idx = w;
            }
        }

        // 将找到的idx对应的s设置为true，相当于将idx对应的顶点加入S
        s[idx] = true;

        // 更新d和path
        for(int w = 0; w < g.vertex_nums; w++) {
            if((d[idx] + g.adjacency_matrix[idx][w] < d[w]) && s[w] == false) {
                d[w] = d[idx] + g.adjacency_matrix[idx][w];
                path[w] = idx;
            }
        }
    }

}


void amg_dijkstra_path_display(AMGraph g, int * path, int v_index) {
    // 根据path数组的内容，将源点v_index到其他顶点的路径输出
    for(int i = 0; i < g.vertex_nums; i++) {
        // 如果当前顶点是源点，不处理
        if(i != v_index) {
            if(path[i] != -1) {  // -1 表示源点到当前顶点无路径
                // tmp数组保存源点到当前顶点路径上的各个顶点，请注意，tmp数组的路径是从目标点到源点的顺序
                int tmp[g.vertex_nums];
                int idx_tmp = 0;

                tmp[idx_tmp] = i; // 先将目标点存入数组
                idx_tmp ++;

                int next = path[i];
                while(next != v_index) {  // 将path[i]的值存入数组
                    tmp[idx_tmp] = next;
                    idx_tmp ++;
                    next = path[next];
                }

                tmp[idx_tmp] = v_index;   // 增加源点，此处不在增加idx_tmp，因此下方循环从idx_tmp开始

                printf("path for %c and %c : ", g.v[v_index], g.v[i]);
                for(int w = idx_tmp; w >= 0; w--) {
                    printf("%c ", g.v[tmp[w]]);
                }
                putchar('\n');
            }
            else {
                printf("No path between %c and %c\n", g.v[v_index], g.v[i]);
            }
        }
    }
}

void amg_shortest_path_floyd(AMGraph g, int n, Edge d[n][n], int path[n][n]) {
    // 初始化二维数组d 和 二维数组path
    // d表示的是i到j的最短路径的长度，初始化为直接边的权重，无直接边则初始化为表示无穷的权重
    // path表示的是i到j的最短路径里，vj的前驱顶点，初始化为，如果i到j有直接边，则为i，否则为-1
    for(int i = 0; i < g.vertex_nums; i++) {
        for(int j = 0; j < g.vertex_nums; j++) {
            d[i][j] = g.adjacency_matrix[i][j];
            if(d[i][j] < INFINITE_WEIGHT)
                path[i][j] = i;             // 有直接边的时候，path里的前驱结点是i
            else
                path[i][j] = -1;            // i到j没有直接边，则初始化为-1
        }
    }

    // 循环
    // 最外层循环其实循环的是图的每个顶点
    // 内层两个循环，是遍历d和path的每个元素
    for(int k = 0; k < g.vertex_nums; k ++) {
        for(int i = 0; i < g.vertex_nums; i++) {
            for(int j = 0; j < g.vertex_nums; j++) {
                if(d[i][k] + d[k][j] < d[i][j]) {         // 表示的是i到k，k到j的距离 和 当前i到j的距离
                    d[i][j] = d[i][k] + d[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}

void amg_floyd_path_display(AMGraph g, int n, Edge d[n][n], int path[n][n]) {
    for(int i = 0; i < g.vertex_nums; i++) {
        for(int j = 0; j < g.vertex_nums; j++) {
            // 因为Floyd算法计算的是每对顶点之间的最小路径，因此对于有n个顶点的图
            // 共有n^2个路径
            // 创建数组保存i..j之间的路径，因为共有n个顶点，所以数组最长为n
            //      如果为-1，表示没有路径，继续循环
            //      i=j表示同一个顶点，没有这样的路径，继续循环
            if(path[i][j] != -1 && i != j) {
                int tmp[g.vertex_nums];
                int idx_tmp = 0;
                tmp[idx_tmp] = j;  // 数组首元素为j，因为每次读取到的下标，为前序顶点，因此tmp数组里的顶点下标，是从后向前的顺序
                idx_tmp ++;

                int next = path[i][j];
                while(next != i) {
                    tmp[idx_tmp] = next;
                    idx_tmp++;
                    next = path[i][next];
                }

                // 补充i
                tmp[idx_tmp] = i;

                printf("path for %c and %c : ", g.v[i], g.v[j]);
                for(int i = idx_tmp; i >= 1; i--) { // 因为每次要取i和i-1位置，所以循环判断条件为i>=1
                    printf("%c -> %c ", g.v[tmp[i]], g.v[tmp[i-1]]);
                }
                putchar('\n');
            }
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