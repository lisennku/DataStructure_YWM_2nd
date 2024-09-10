//
// Created by lisen on 24-9-10.
//
#include <stdio.h>
#include <stdlib.h>

#define ORDER 3                  // 定义B树的阶

typedef int key_type;

// 定义B树的结点结构
struct b_tree_node {
    int key_nums;                      // 定义关键字的个数 ceil(ORDER/2) - 1 <= key_nums <= ORDER - 1
    key_type keys[ORDER];              // 定义关键字数组 0位不用 循环时使用key_nums控制，而非ORDER
    struct b_tree_node * ptrs[ORDER];  // 定义指向子树的指针数组 此时有ORDER个指针元素 0位是要使用的
    struct b_tree_node * parent;       // 指向父结点的指针
};

typedef struct b_tree_node BTree_Node; // B树结点
typedef struct b_tree_node * BTree;    // B树本身

// 定义查找返回结构
struct ret_search {
    BTree_Node * node;                 // 结点指针 如果找到 指向所在的结点 没找到 指向叶结点的父结点
    int key_index;                     // 关键值数组的索引 使得keys[key_index] <= key < keys[key_index+1]
    int find_tag;                      // 是否找到的标记为 0没找到 1找到
};

typedef struct ret_search Result;

// 在结点的keys数组中查找key
// 并返回第一个满足使得keys[i] <= key < keys[i+1]的位置
int b_tree_search_keys_in_node(BTree_Node * node, key_type key);

// 在B树中搜索指定关键字
// 返回Result类型
Result b_tree_search(BTree t, key_type key);






int main() {


    return 0;
}
