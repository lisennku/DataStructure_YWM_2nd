//
// Created by lisen on 24-9-10.
//
#include <stdio.h>
#include <stdlib.h>

#include "chap5/ds/btnode.h"

#define ORDER 5                  // 定义B树的阶

typedef int key_type;

// 定义B树的结点结构
struct b_tree_node {
    int key_nums;                      // 定义关键字的个数 ceil(ORDER/2) - 1 <= key_nums <= ORDER - 1
    key_type keys[ORDER];              // 定义关键字数组 0位不用 循环时使用key_nums控制，而非ORDER
    struct b_tree_node * ptrs[ORDER];  // 定义指向子树的指针数组 此时有ORDER个指针元素 0位是要使用的
    struct b_tree_node * parent;       // 指向父结点的指针
};

typedef struct b_tree_node BMTree_Node; // B树结点
typedef struct b_tree_node * BMTree;    // B树本身

// 定义查找返回结构
struct ret_search {
    BMTree_Node * node;                 // 结点指针 如果找到 指向所在的结点 没找到 指向叶结点的父结点
    int key_index;                     // 关键值数组的索引 使得keys[key_index] <= key < keys[key_index+1]
    int find_tag;                      // 是否找到的标记为 0没找到 1找到
};

typedef struct ret_search Result;

// 在结点的keys数组中查找key
// 并返回第一个满足使得keys[i] <= key < keys[i+1]的位置
int b_tree_search_keys_in_node(BMTree_Node * node, key_type key) {
    // 使用顺序查找确定位置 也可以采取折半查找
    int i;
    for(i = 0; i < node->key_nums && node->keys[i+1] <= key; i++);

    return i;
}

// 在B树中搜索指定关键字
// 返回Result类型
Result b_tree_search(BMTree t, key_type key) {
    Result res;
    BMTree_Node * p = t;                // 指向树
    BMTree_Node * q = NULL;             // 初始化为NULL 后续指向p的父结点
    int key_index = 0;                  // 0位在keys中没有使用 此处用作标记
    int find_flag = 0;


    while(p != NULL && find_flag == 0) {
        key_index = b_tree_search_keys_in_node(p, key);  // 找到此时key在当前结点内返回的位置
        if(key_index > 0 && p->keys[key_index] == key)   // 如果key在当前结点内 则find_flag为1
            find_flag = 1;
        else {
            q = p;
            p = p->ptrs[key_index];                       // 如果不在当前结点内 查找指定的子树
        }
    }

    // 结束循环时判断是否找到
    if(find_flag) {
        res.node = p;                                     // 找到时在p内
        res.key_index = key_index;
        res.find_tag = find_flag;
    }
    else {
        res.node = q;                                     // 没有找到时 p指向虚拟的叶结点 需要返回其父结点
        res.key_index = key_index;
        res.find_tag = find_flag;
    }

    return res;
}






int main() {


    return 0;
}
