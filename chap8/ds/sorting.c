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

// 打印序列
void print_sqlist(SqList list) {
    for(int i = 1; i <= list.length; i++)
        printf("%d ", list.recs[i].key);
    putchar('\n');
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

// 折半插入排序
void binary_insertion_sort(SqList * list, bool asc) {
    for(int i = 2; i <= list->length; i++) {
        list->recs[0] = list->recs[i];    // 设置哨兵位
        int low = 1;
        int high = i - 1;

        // 折半查找插入位置
        while(low <= high) {
            int mid = (low + high) / 2;
            // compare函数
            // 正序时 返回值大于0 表示a>b 此时需要查找左侧 因为已排序部分是正序
            // 倒叙时 返回值大于0 表示a<b 此时需要查找左侧 因为已排序部分是倒叙
            if(compare(&list->recs[mid].key, &list->recs[0].key, asc) > 0)
                high = mid - 1;
            else
                low = mid + 1;
        }

        for(int j = i-1; j > high; j--)
            list->recs[j+1] = list->recs[j];

        list->recs[high + 1] = list->recs[0];

    }
}

// 希尔排序
void shell_sort(SqList * list, bool asc) {
    // 根据长度 自动生成每次增量
    for(int di = list->length / 2; di >= 1; di /= 2) {
        // 从di+1开始 表示两个含义
        //      1. 前di个元素 每个元素为一个分组 1和di+1 2和di+2 等等为一组
        //      2. 每个分组内认为有序 因为每个分组只有一个元素
        // 每次循环 比较对应有序分组内的最后一个元素 和无序分组内的待插入的元素
        // 每次移动 都是针对整个有序分组
        for(int i = di+1; i <= list->length; i++) {
            list->recs[0] = list->recs[i];
            int j = i - di;
            // j > 0 是因为每次j的递减量是di 而不是1 但是如果用j>=1应该也可以
            while(j > 0 && compare(&list->recs[j].key, &list->recs[0].key, asc) > 0) {
                list->recs[j+di] = list->recs[j];
                j -= di;
            }
            list->recs[j+di] = list->recs[0];
        }
    }

}
/*****************插入排序 end************************/

/*****************交换排序 start**********************/
// 冒泡排序 未优化的双循环
void bubble_sort_normal(SqList * list, bool asc) {
    // 基本冒泡排序的逻辑
    //  冒泡排序使用序列的末尾作为有序序列部分
    //  每趟排序过程 将符合要求的元素 放到有序序列的首位
    //  因此 对于第i趟排序 符合要求的元素应该放到n-i+1的位置
    // 外层循环控制无序序列 每次长度减掉1 每结束一次循环 表示当前序列的最后一位已经确定
    // 内层循环 从无序序列首位开始 两两比较 最后一次循环 应该是无序序列的倒数第二位
    // 函数存在一个问题 如果序列已经完全有序 虽然没发生交换 但是仍然会继续循环 因此存在优化空间
    for(int i = list->length; i >= 1; i--){
        for(int j = 1; j <= i - 1; j++) {
            if(compare(&list->recs[j].key, &list->recs[j+1].key, asc) > 0) {
                rec_type tmp = list->recs[j+1];
                list->recs[j+1] = list->recs[j];
                list->recs[j] = tmp;
            }
        }
    }
}

// 冒泡排序 优化
void bubble_sort_optimized(SqList * list, bool asc) {
    // 设置标记位 表示当前循环是否发生交换 如果没有发生则直接结束
    bool is_swap = true;
    for(int i = list->length; i >= 1 && is_swap;i--) {
        // 每次循环重置is_swap变量为false 发生交换 赋值为true
        is_swap = false;
        for(int j = 1; j <= i - 1; j++) {
            if(compare(&list->recs[j].key, &list->recs[j+1].key, asc) > 0) {
                is_swap = true;
                rec_type tmp = list->recs[j+1];
                list->recs[j+1] = list->recs[j];
                list->recs[j] = tmp;
            }
        }
    }
}

// 快速排序中每趟排序
// 返回枢轴最终的位置
int quick_sort_partitions(SqList * list, int low, int high, bool asc) {
    // 用于快排中的每趟排序
    // 以左端为枢轴
    list->recs[0] = list->recs[low];
    key_type pivot_value = list->recs[0].key;

    // 先从右端开始 找到和pivot_value比较后需要交换位置的地方
    //      找到后和枢轴所在位置进行交换 初次在low位 后续的交换也都在low位
    // 再从左端开始 找到和pivot_value比较后需要交换位置的地方
    //      找到后和high位交换 因为上边执行后可能会交换 交换后在high位
    // 如果第一步没交换 说明有序 有序则第二步也不会发生交换
    // 交替进行 直到low == high
    while(low < high) {
        while(low < high && compare(&list->recs[high].key, &pivot_value, asc) > 0)
            high --;
        list->recs[low] = list->recs[high];

        while(low < high && compare(&list->recs[low].key, &pivot_value, asc) < 0)
            low ++;
        list->recs[high] = list->recs[low];
    }

    list->recs[low] = list->recs[0];

    return low;
}

// 快速排序 递归版
void quick_sort_recursive(SqList * list, int low, int high, bool asc) {
    if(low < high) {
        int pivot_loc = quick_sort_partitions(list, low, high, asc);
        quick_sort_recursive(list, low, pivot_loc - 1, asc);
        quick_sort_recursive(list, pivot_loc + 1, high, asc);
    }
}
/*****************交换排序 end************************/

int main() {
    SqList list;
    generate_sqlist(&list);
    print_sqlist(list);

    quick_sort_recursive(&list, 1, 20, true);
    print_sqlist(list);


    return 0;
}

