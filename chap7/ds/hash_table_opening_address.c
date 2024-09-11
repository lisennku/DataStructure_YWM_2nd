//
// Created by lisen on 24-9-11.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
    哈希表采用除留取余法创建 指定哈希表长度为HASH_LENGTH 模为HASH_MODULO
    冲突处理以开放地址法中的顺序探测(Linear)和二次探测(Quadratic)为准
#endif

#define HASH_LENGTH 16
#define HASH_MODULO 13
#define NULL_MARKER -1

typedef int key_type;

struct hash_map {
    int len;
    int modulo;
    key_type * map;
};

typedef struct hash_map HMap;

// 初始化哈希表
void oa_hash_map_init(HMap *hm) {
    hm->len = HASH_LENGTH;                                                // 哈希表长度
    hm->modulo = HASH_MODULO;                                             // 哈希计算取模
    hm->map = (key_type *) malloc(sizeof(key_type) * HASH_LENGTH);    // 哈希表
    if(hm->map == NULL)
        exit(EXIT_FAILURE);
    memset(hm->map, NULL_MARKER, hm->len * sizeof(key_type));      // 哈希表每个元素初始化为-1
}

// 采用线性探测法进行查找
key_type oa_hashmap_search_linear(HMap hm, key_type key) {
    int index = key % hm.modulo;

    if(hm.map[index] == NULL_MARKER)
        return -1;

    if(hm.map[index] == key)
        return index;

    for(int i = 1; i < hm.len; i++) {
        index = (index + i) % hm.len;
        if(hm.map[index] == NULL_MARKER)
            return -1;
        if(hm.map[index] == key)
            return index;
    }

    return -1;

}

// 采用线性探测法进行插入
// 插入是希望找到哈希表中某个为NULL的位置 将记录放在里面
// 每次增量di为1...len-1 需要注意探测次数不能超过哈希表长度
// 线性探测的公式是Hi = (H(key) + di) % len
void oa_hash_map_insert_linear(HMap * hm, key_type key) {
    key_type ret_idx = oa_hashmap_search_linear(*hm, key);
    if(ret_idx != -1) {
        printf("duplicated key value inserted\n");
        return ;
    }
    int index = key % hm->modulo;
    int count = 0;
    while(hm->map[index]!= NULL_MARKER) {
        if(count == hm->len) {
            printf("hash map is full!\n");
            return ;
        }
        count++;
        index = (index + 1) % hm->len;
    }
    hm->map[index] = key;
}

void oa_hash_map_insert_quadratic(HMap * hm, key_type key);

key_type oa_hashmap_search_quadratic(HMap hm, key_type key);

void oa_hash_map_create(HMap * hm, key_type * arr, int len) {
    for(int i = 0; i < len; i++) {
        oa_hash_map_insert_linear(hm, arr[i]);
    }
}

void oa_hash_map_calc_success_asl_linear(HMap hm, int * searches, int * used) {
    // 计算线性探测法，成功的平均查找次数
    // searches是长度和哈希表相同的数组
    //  对于哈希表中空的位置 对应位置是0 对于哈希表中非空的位置 对应位置是查找次数
    // used是哈希表非空元素数量
    // 计算逻辑
    //  如果位置为空 则为0
    //  非空 相当于用当前位置的数据再插入一次表 记录比较的次数
    for(int i = 0; i < hm.len; i++) {
        if (hm.map[i] == NULL_MARKER)
            searches[i] = 0;
        else {
            key_type key = hm.map[i];
            int index = key % hm.modulo;
            if(hm.map[index] == key)                 // 如果存的是该数据，返回1
                searches[i] = 1;
            else {
                for(int j = 1; j < hm.len; j++) {    // 线性探测 无需考虑无位置的情况
                    index = (index + 1) % hm.len;
                    if(hm.map[index] == key)
                        searches[i] = j + 1;
                }
            }
        }
    }
}

void oa_hash_map_calc_fail_asl_linear(HMap hm, int * fails) {
    // 计算线性探测法 查找失败的平均次数
    // 数组fails的长度是HASH_MODULO 因为查找失败的情况发生在0-HASH_MODULO-1的入口处
    // 计算逻辑
    // 如果哈希表位置为空 说明查找失败 当前位置为1
    // 如果哈希表位置不为空 从该位置向后找到第一个为空的位置 记录比较次数

    for(int i = 0; i < hm.modulo; i++) {
        if(hm.map[i] == NULL_MARKER)
            fails[i] = 1;
        else {
            int cnt = 1;
            int j = i + 1;
            while(j < hm.len) {
                cnt++;
                if(hm.map[j] == NULL_MARKER) {
                    fails[i] = cnt;
                    break;
                }
                j ++;
            }
            if(j == hm.len)
                fails[i] = cnt;
        }
    }
}

int main() {
    key_type arr[] = {19, 14, 23, 1, 68, 20, 84, 27, 55, 11, 10, 79};
    HMap hm;
    oa_hash_map_init(&hm);

    oa_hash_map_create(&hm, arr, sizeof(arr) / sizeof(key_type));

    for(int i = 0; i < hm.len; i++)
        printf("%d ", hm.map[i]);

    putchar('\n');

    int searches[hm.len];
    int used;
    oa_hash_map_calc_success_asl_linear(hm, searches, &used);
    for(int i = 0; i < hm.len; i++)
        printf("%d ", searches[i]);

    putchar('\n');

    int fails[hm.modulo];
    oa_hash_map_calc_fail_asl_linear(hm, fails);
    for(int i = 0; i < hm.modulo; i++)
        printf("%d ", fails[i]);

    return 0;
}