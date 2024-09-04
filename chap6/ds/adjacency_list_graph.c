//
// Created by lisen on 24-8-30.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "adjacency_list_graph.h"

// 根据结点值，找到该结点在表头数组内的下标
// 找不到则返回-1
int alg_locate_vertex(const ALGraph g, const vertex v) {
    for(int i = 0; i < g.vertex_nums; i++) {
        if(g.hd[i].data == v)
            return i;
    }
    return -1;
}

// 创建一个无向图
void alg_create_undirected_graph(ALGraph * g) {
    // 确定图的顶点和边数
    printf("please input vertex numbers\n");
    scanf("%d", &g->vertex_nums);
    printf("please input edge numbers\n");
    scanf("%d", &g->edge_nums);

    // 输入图的顶点的值
    for(int i = 0; i < g->vertex_nums; i++) {
        printf("please input no. %d vertex value, no duplicated!\n", i);
        scanf(" %c", &(g->hd[i].data));
        // 因为hd数组中的各个元素是边链表的头结点，所以需要初始化first_arc指针为NULL
        g->hd[i].first_arc = NULL;
    }

    // 根据边的数量，输入边两端的顶点的值
    for(int i = 0; i < g->edge_nums; i++) {
        vertex v1, v2;
        int idx1, idx2;
        do {
            printf("please input a pair of vertex value for no. %d edge\n", i);
            scanf(" %c %c", &v1, &v2);
            idx1 = alg_locate_vertex(*g, v1);
            idx2 = alg_locate_vertex(*g, v2);
            if(idx1 != -1 && idx2 != -1) {
                // 为了方便，边链表的新结点在表头处插入，也即放到顶点所表示的头结点后
                // 因为是无向图
                // 先处理 v1 -> v2 的边
                Arc_Node * arn1 = (Arc_Node *) malloc(sizeof(Arc_Node));
                // 更新索引值
                arn1->adj_idx = idx2;     // 需要注意存储的是指向的位置的索引
                // 找到v1对应的表头结点，将当前的first_arc的值，赋值给新结点的next_art
                arn1->next_arc = g->hd[idx1].first_arc;
                g->hd[idx1].first_arc = arn1;

                // 再处理 v2 -> v1 的边
                Arc_Node * arn2 = (Arc_Node *) malloc(sizeof(Arc_Node));
                arn2->adj_idx = idx1;     // 需要注意存储的是指向的位置的索引
                arn2->next_arc = g->hd[idx2].first_arc;
                g->hd[idx2].first_arc = arn2;
            }
            else {
                printf("vertex value not exist, please re-enter\n");
            }
        }while(idx1 == -1 || idx2 == -1);
    }
}

// 创建一个无向网
void alg_create_undirected_net(ALGraph * g);

// 创建一个有向图
void alg_create_directed_graph(ALGraph * g) {
    // 确定图的顶点和边数
    printf("please input vertex numbers\n");
    scanf("%d", &g->vertex_nums);
    printf("please input edge numbers\n");
    scanf("%d", &g->edge_nums);

    // 输入图的顶点的值
    for(int i = 0; i < g->vertex_nums; i++) {
        printf("please input no. %d vertex value, no duplicated!\n", i);
        scanf(" %c", &(g->hd[i].data));
        // 因为hd数组中的各个元素是边链表的头结点，所以需要初始化first_arc指针为NULL
        g->hd[i].first_arc = NULL;
    }

    // 根据边的数量，输入边两端的顶点的值
    for(int i = 0; i < g->edge_nums; i++) {
        vertex v1, v2;
        int idx1, idx2;
        do {
            printf("please input a pair of vertex value for no. %d edge\n", i);
            scanf(" %c %c", &v1, &v2);
            idx1 = alg_locate_vertex(*g, v1);
            idx2 = alg_locate_vertex(*g, v2);
            if(idx1 != -1 && idx2 != -1) {
                // 为了方便，边链表的新结点在表头处插入，也即放到顶点所表示的头结点后
                // 因为是有向图
                // 只处理 v1 -> v2 的边
                Arc_Node * arn1 = (Arc_Node *) malloc(sizeof(Arc_Node));
                // 更新索引值
                arn1->adj_idx = idx2;     // 需要注意存储的是指向的位置的索引
                // 找到v1对应的表头结点，将当前的first_arc的值，赋值给新结点的next_art
                arn1->next_arc = g->hd[idx1].first_arc;
                g->hd[idx1].first_arc = arn1;
            }
            else {
                printf("vertex value not exist, please re-enter\n");
            }
        }while(idx1 == -1 || idx2 == -1);
    }
}

// void alg_topo_sort_find_zero_in_degree(int * in_degree, int degree_len, int * stack, int * rear) {
//     for(int i = 0; i < degree_len; i++) {
//         if(in_degree[i] == 0) {
//             stack[*rear] = i;
//             (*rear) ++;
//         }
//     }
// }

// 拓扑排序
bool alg_directed_net_topo_sort(ALGraph g, int * topo) {
    // 创建一维数组indegree，计算每个顶点的入度
    int in_degree[g.vertex_nums];
    for(int i = 0; i < g.vertex_nums; i++) {  // 将in_degree初始为0
        in_degree[i] = 0;
    }

    for(int i = 0; i < g.vertex_nums; i++) {  // 计算各个顶点的入度
        Arc_Node * p = g.hd[i].first_arc;
        while (p != NULL) {
            in_degree[p->adj_idx] += 1;
            p = p->next_arc;
        }
    }

    // 栈，此处使用数组代替，因为整个图的顶点是g.vertex_nums，所以数组长度最长为vertex_nums
    int stack[g.vertex_nums];
    int rear = 0;   // rear为0，表示栈为空，每次插入元素后+1

    for(int i = 0; i < g.vertex_nums; i++) {
        if(in_degree[i] == 0) {
            stack[rear] = i;
            (rear) ++;
        }
    }

    int topo_idx = 0;

    while(rear != 0) {
        // 弹出栈顶元素，注意rear先减一
        int idx = stack[--rear];

        // 将idx保存到topo数组里
        topo[topo_idx] = idx;
        topo_idx++;

        // 更新in_degree的数据
        // 找到idx所在hd的边链表，对链表里的弧头的adj_idx，在in_degree[adj_idx]-1
        Arc_Node * p = g.hd[idx].first_arc;
        while(p != NULL) {
            in_degree[p->adj_idx] -- ;

            // 判断如果此时入度为0 入栈
            if(in_degree[p->adj_idx] == 0)
                stack[rear++] = p->adj_idx;

            p = p->next_arc;
        }
    }



    return topo_idx == g.vertex_nums ? true : false;

}

void alg_create_directed_graph_w_inverse(ALGraph * g, ALGraph * ig) {
    // 确定图的顶点和边数
    printf("please input vertex numbers\n");
    int v_nums;
    scanf("%d", &v_nums);
    g->vertex_nums = v_nums;
    ig->vertex_nums = v_nums;

    printf("please input edge numbers\n");
    int e_nums;
    scanf("%d", &e_nums);
    g->edge_nums = e_nums;
    ig->edge_nums = e_nums;

    // 输入图的顶点的值
    for(int i = 0; i < g->vertex_nums; i++) {
        printf("please input no. %d vertex value, no duplicated!\n", i);
        // 更新邻接表表头和逆邻接表表头
        char tmp;
        scanf(" %c", &tmp);
        g->hd[i].data = tmp;
        ig->hd[i].data = tmp;
        // 因为hd数组中的各个元素是边链表的头结点，所以需要初始化first_arc指针为NULL
        g->hd[i].first_arc = NULL;
        ig->hd[i].first_arc = NULL;
    }

    // 根据边的数量，输入边两端的顶点的值
    for(int i = 0; i < g->edge_nums; i++) {
        vertex v1, v2;
        int idx1, idx2;
        do {
            printf("please input a pair of vertex value for no. %d edge\n", i);
            scanf(" %c %c", &v1, &v2);
            idx1 = alg_locate_vertex(*g, v1);
            idx2 = alg_locate_vertex(*g, v2);
            if(idx1 != -1 && idx2 != -1) {
                // 为了方便，边链表的新结点在表头处插入，也即放到顶点所表示的头结点后
                // 因为是有向图
                // 只处理 v1 -> v2 的边
                Arc_Node * arn1 = (Arc_Node *) malloc(sizeof(Arc_Node));
                // 更新索引值
                arn1->adj_idx = idx2;     // 需要注意存储的是指向的位置的索引
                // 找到v1对应的表头结点，将当前的first_arc的值，赋值给新结点的next_art
                arn1->next_arc = g->hd[idx1].first_arc;
                g->hd[idx1].first_arc = arn1;

                // 处理逆邻接表
                Arc_Node * arn2 = (Arc_Node *) malloc(sizeof(Arc_Node));
                arn2->adj_idx = idx1;     // 需要注意存储的是指向的位置的索引
                arn2->next_arc = ig->hd[idx2].first_arc;
                ig->hd[idx2].first_arc = arn2;
            }
            else {
                printf("vertex value not exist, please re-enter\n");
            }
        }while(idx1 == -1 || idx2 == -1);
    }
}

void alg_dfs(ALGraph g, int v_index, bool * visited) {
    printf(" %c ", g.hd[v_index].data);
    visited[v_index] = true;

    Arc_Node * p = g.hd[v_index].first_arc;
    while(p != NULL) {
        if(visited[p->adj_idx] == false)
            alg_dfs(g, p->adj_idx, visited);
        p = p->next_arc;
    }
}

void alg_dfs_traverse(ALGraph g, bool * visited) {
    for(int i = 0; i < g.vertex_nums; i++)
        visited[i] = false;
    for(int i = 0; i < g.vertex_nums; i++) {
        if(visited[i] == false)
            alg_dfs(g, i, visited);
    }
}

void alg_bfs(ALGraph g, int v_index, bool * visited) {
    printf(" %c ", g.hd[v_index].data);
    visited[v_index] = true;

    // 使用数组代替队列，front表示队首，rear表示队尾
    // 数组存储g.hd的下标
    int queue[g.vertex_nums];
    int front = 0, rear = 0;
    for(int i = 0; i < g.vertex_nums; i++)
        queue[i] = -1;

    // v_index 入队
    queue[rear] = v_index;
    rear ++;

    while(front != rear) { // 队列非空
        // 弹出队首元素
        int idx = queue[front];
        front ++;

        Arc_Node * p = g.hd[idx].first_arc;
        while(p != NULL) {
            // 如果未访问过，则访问该边结点，并将下标入队
            if(visited[p->adj_idx] == false) {
                printf(" %c ", g.hd[p->adj_idx].data);
                visited[p->adj_idx] = true;

                queue[rear] = p->adj_idx;
                rear ++;
            }
            p = p->next_arc;
        }
    }


}

void alg_bfs_traverse(ALGraph g, bool * visited) {
    for(int i = 0; i < g.vertex_nums; i++)
        visited[i] = false;
    for(int i = 0; i < g.vertex_nums; i++) {
        if(visited[i] == false)
            alg_bfs(g, i, visited);
    }
}


void alg_display(ALGraph g) {
    for(int i = 0; i < g.vertex_nums; i++) {
        printf("%c:", g.hd[i].data);
        Arc_Node * p = g.hd[i].first_arc;
        while(p) {
            printf(" -> %c", g.hd[p->adj_idx].data);
            p = p->next_arc;
        }
        putchar('\n');
    }
}