//
// Created by lisen on 24-9-12.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXSIZE 20

typedef int key_type;                 // 关键字

typedef struct {                      // 记录类型 暂时只有一个成员
    key_type key;
} rec_type;

typedef struct seq_list {             // 顺序表类型
    rec_type recs[MAXSIZE + 1];       // 0位不用 或为哨兵位
    int length;                       // 顺序表长度
} SqList;

void generate_sqlist(SqList *sq_list);

/*****************插入排序 start**********************/
// 直接插入排序
void straight_insertion_sort_normal(SqList * list, bool asc);
void straight_insertion_sort_sentinel(SqList * list, bool asc);

/*****************插入排序 end************************/

int main() {
    SqList list;
    generate_sqlist(&list);

    for(int i = 1; i <= list.length; i++)
        printf("%d ", list.recs[i].key);

    return 0;
}

void generate_sqlist(SqList *sq_list) {
    srand(1); // 设置随机数种子 防止数据变化

    sq_list->length = MAXSIZE;

    int cnt = 1;

    while(cnt <= sq_list->length) {
        bool dup_flag = false;
        int rand_int = rand() % 100 + 1; // 随机生成1-100的整数
        for(int i = 1; i <= cnt - 1; i++) {
            if(sq_list->recs[i].key == rand_int) {
                dup_flag = true;
                break;
            }
        }
        if(!dup_flag) {
            sq_list->recs[cnt].key = rand_int;
            cnt ++;
        }
    }
}

/*****************插入排序 start**********************/
// 直接插入排序
void straight_insertion_sort_normal(SqList * list, bool asc) {
    if(asc) {
        for(int i = 2; i <= list->length; i++) {
            if(list->recs[i-1].key > list->recs[i].key) {
                rec_type tmp = list->recs[i];
                for(int j = i-1; j >= 1; j--) {
                    if(list->recs[j].key > tmp.key)

                }
            }

        }
    }
    else {

    }
}
void straight_insertion_sort_sentinel(SqList * list, bool asc);

/*****************插入排序 end************************/