//
// Created by lisen on 24-10-12.
//
// https://leetcode.cn/problems/lru-cache/?envType=problem-list-v2&envId=hash-table

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 采取哈希表+双向链表的形式构造LRUCache的数据结构
 * 哈希表以数组形式体现 按照key值进行哈希 存储的元素是Node类型
 *  需要注意 因为要判断某个key是否在哈希表中 因此需要初始化 根据题意此处初始化为-1 -> int会被初始化为-1 指针会是fffffff...
 *  判断Cache是否已满 使用length属性和capacity属性
 * 双向链表用来存储key的最近访问情况 使用头结点和尾结点的形式
 *  每访问(get/put)一个key 需要将对应key插入或者移动到header的下一个位置
 *      get成功才可以 失败不需要移动
 */

#define  HASH_SIZE 10001


typedef struct node{
    int key;
    int val;
    struct node * prev;
    struct node * next;
}LRUCacheNode;

typedef struct {
    LRUCacheNode * hash_map;               // 哈希表
    LRUCacheNode * head;          // 指向双向链表的头指针
    LRUCacheNode * tail;          // 指向双向链表的尾指针
    int capacity;                 // LRU容量
    int length; // 当前LRU长度
} LRUCache;

// 将新结点插入到头位置
void nodeInsertToHead(LRUCache * obj, LRUCacheNode * node) {
    node->prev = obj->head;
    node->next = obj->head->next;

    obj->head->next->prev = node;
    obj->head->next = node;
}

// 将已存在的结点插入到头位置
void nodeMoveToHead(LRUCache * obj, LRUCacheNode * node) {
    // 将待挪动结点的前后结点的指针更新
    node->prev->next = node->next;
    node->next->prev = node->prev;

    nodeInsertToHead(obj, node);
}

// 移除尾部结点(尾指针前一个结点)
void nodeRemoveFromTail(LRUCache * obj) {
    LRUCacheNode * node = obj->tail->prev;
    node->prev->next = node->next;
    node->next->prev = node->prev;

}

LRUCache* lRUCacheCreate(int capacity) {
    if(capacity <= 0)
        return NULL;

    // 创建
    LRUCache * lru = (LRUCache *) malloc(sizeof(LRUCache));
    if(lru == NULL)
        exit(EXIT_FAILURE);

    /*
    * 初始化哈希表
    * 哈希表用于存储缓存 初始化长度为key的值范围 使用size和capacity的大小关系 确认Cache是否已满
    * 使用key的值作为哈希值
    */
    lru->hash_map = malloc(sizeof(LRUCacheNode) * HASH_SIZE);
    if(lru->hash_map == NULL)
        exit(EXIT_FAILURE);
    // 初始化的缓存区 每项的key/val都是-1
    memset(lru->hash_map, -1, HASH_SIZE * sizeof(LRUCacheNode));   //

    /*
     * 初始化头尾指针 分别指向头结点/尾结点
     * 注意 不是实际存储的结点
     */
    lru->head = malloc(sizeof(LRUCacheNode));
    lru->head->key = lru->head->val = -1;


    lru->tail = malloc(sizeof(LRUCacheNode));
    lru->tail->key = lru->tail->val = -1;


    lru->head->prev = NULL;
    lru->head->next = lru->tail;
    lru->tail->next = NULL;
    lru->tail->prev = lru->head;

    lru->capacity = capacity;
    lru->length = 0;


    // 返回
    return lru;

}

int lRUCacheGet(LRUCache* obj, int key) {
    LRUCacheNode node = obj->hash_map[key];
    if(node.key == -1)
        return -1;
    nodeMoveToHead(obj, &obj->hash_map[key]);
    return node.val;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    if(lRUCacheGet(obj, key) != -1) {  // 缓存已存在
        obj->hash_map[key].val = value;
        nodeMoveToHead(obj, &obj->hash_map[key]);
    }
    else { // 缓存不存在
        obj->hash_map[key].key = key;
        obj->hash_map[key].val = value;

        nodeInsertToHead(obj, &obj->hash_map[key]);
        obj->length ++;

        if(obj->length > obj->capacity) {
            LRUCacheNode * del_node = obj->tail->prev;

            nodeRemoveFromTail(obj);

            int idx = del_node->key;

            obj->hash_map[idx].key = obj->hash_map[idx].val = -1;
            obj->hash_map[idx].next = obj->hash_map[idx].prev = NULL;

            obj->length --;
        }

    }
}

void lRUCacheFree(LRUCache* obj) {
    free(obj->hash_map);
}

void display_cache(LRUCache obj) {
    LRUCacheNode *node = obj.head->next;

    while(node != obj.tail) {
        printf("key: %d; value: %d\n", node->key, node->val);
        node = node->next;
    }
}



int main() {
    LRUCache * lru = lRUCacheCreate(2048);
    lRUCachePut(lru, 1178,3401);
    lRUCachePut(lru, 903, 6060);
    lRUCachePut(lru, 1127,3054);
    lRUCachePut(lru, 1377,1290);
    lRUCachePut(lru, 2584,232);

    display_cache(*lru);

    return 0;
}
