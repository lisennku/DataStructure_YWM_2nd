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

/*****************辅助函数 start**********************/
// 生成序列
void generate_sqlist(SqList *sq_list);
// 关键值比较 控制正序倒叙
int compare(void * a, void * b, bool asc);

/*****************辅助函数 start**********************/

/*****************插入排序 start**********************/
// 直接插入排序
void asc_straight_insertion_sort_normal(SqList * list);    // 普通
void asc_straight_insertion_sort_sentinel(SqList * list);  // 哨兵
void straight_insertion_sort(SqList * list, bool asc);     // 参数控制正序倒叙

/*****************插入排序 end************************/

int main() {
    SqList list;
    generate_sqlist(&list);

    for(int i = 1; i <= list.length; i++)
        printf("%d ", list.recs[i].key);

    putchar('\n');

    straight_insertion_sort(&list, false);
    for(int i = 1; i <= list.length; i++)
        printf("%d ", list.recs[i].key);

    return 0;
}

/*****************辅助函数 start**********************/
// 生成序列
void generate_sqlist(SqList *sq_list) {
    srand(11); // 设置随机数种子 防止数据变化

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

// 关键值比较 控制正序倒叙
// 返回值大于0 表示需要调换位置
int compare(void * a, void * b, bool asc) {
    /*
     * 函数根据asc参数 针对正序倒序统一控制返回值符号
     *      如果返回 正数 表示需要调换 a b 位置
     *      如果返回 其他 表示不需要
     * 参数 a b是空指针类型 函数内转为需要的类型
     * 参数 asc控制正序或者倒叙
     * 如果是正序 返回 a - b
     *      返回正数 说明 a > b
     *      返回0   说明 a = b
     *      返回负数 说明 a < b
     * 如果是倒叙 返回 b - a
     *      返回正数 说明 a < b
     *      返回0   说明 a = b
     *      返回负数 说明 a > b
    */

    key_type aa = *((key_type *) a);   // 参数a是空指针类型 先转为key_type类型的指针 然后取值
    key_type bb = *((key_type *) b);   // 参数b是空指针类型 先转为key_type类型的指针 然后取值
    return asc ? aa - bb : bb - aa;
}

/*****************辅助函数 start**********************/


/*****************插入排序 start**********************/
// 正序直接插入排序 普通
void asc_straight_insertion_sort_normal(SqList * list) {
        for(int i = 2; i <= list->length; i++)                            // 循环从第二位开始，默认第一位是一个有序序列
            if(list->recs[i-1].key > list->recs[i].key) {                 // [i]为当前要插入有序序列的值 和其前一位比较
                rec_type tmp = list->recs[i];
                int j;

                for(j = i-1; j >= 1; j--) {                               // 移动有序序列 需要注意遇到不需要移动的就要结束循环
                    if(list->recs[j].key > tmp.key)                       // 如果前一位大于 表示需要移动
                        list->recs[j+1] = list->recs[j];
                    else                                                  // 此时不大于 表示不需要移动
                        break;
                }

                // 上述for循环可优化为如下代码 其实就是使用了哨兵方式
                // for的循环条件为假则跳出循环 不会执行j-- 类似于else部分的break
                // for(j = i-1; j >= 1 && tmp.key < list->recs[j].key; j--)  // 移动有序序列 需要注意遇到不需要移动的就要结束循环
                //     list->recs[j+1] = list->recs[j];

                // 当结束循环时 j的位置表示的是不需要移动的位置
                // 意味插入的位置应该是j后面的一位
                list->recs[j+1] = tmp;
            }
}

// 正序直接插入排序 哨兵
void asc_straight_insertion_sort_sentinel(SqList * list) {
    for(int i = 2; i <= list->length; i++)
        if(list->recs[i-1].key > list->recs[i].key) {
            list->recs[0] = list->recs[i];                                  // 0位作为哨兵使用
            int j ;
            for(j = i - 1; j >= 1 && list->recs[0].key < list->recs[j].key; j--)
                list->recs[j+1] = list->recs[j];
            list->recs[j+1] = list->recs[0];
        }
}

// 参数控制正序倒叙
void straight_insertion_sort(SqList * list, bool asc) {
    for(int i = 2; i <= list->length; i++) {     // 从无序序列第一位开始
        // 设置哨兵
        list->recs[0] = list->recs[i];
        int j = i - 1;                          // 有序序列最后一位
        // j >= 1控制循环到有序序列第一位
        // compare > 0 说明需要交换位置
        while(j >= 1 && compare(&list->recs[j].key, &list->recs[0].key, asc) > 0) {
            list->recs[j+1] = list->recs[j];
            j -- ;
        }
        list->recs[j+1] = list->recs[0];
    }

}

/*****************插入排序 end************************/