//
// Created by lisen on 24-9-12.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 排序数据类型 基数排序除外
#define MAXSIZE 6

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
        // 如果是正序 那么右端比枢轴小的 要交换位置 否则只移动指针high
        //      此时 compare返回值大于0 表示high位置比枢轴的大 不需要移动
        // 如果是倒序 那么右端比枢轴大的 要交换位置 否则只移动指针high
        //      此时 compare返回值大于0 表示high位置比枢轴的小 不需要移动
        while(low < high && compare(&list->recs[high].key, &pivot_value, asc) > 0)
            high --;
        list->recs[low] = list->recs[high];
        // 如果是正序 那么左端比枢轴大的 要交换位置 否则只移动指针low
        //      此时 compare返回值小于0 表示low位置比枢轴的小 不需要移动
        // 如果是倒序 那么左端比枢轴小的 要交换位置 否则只移动指针low
        //      此时 compare返回值小于0 表示low位置比枢轴的大 不需要移动
        while(low < high && compare(&list->recs[low].key, &pivot_value, asc) < 0)
            low ++;
        list->recs[high] = list->recs[low];
    }

    list->recs[low] = list->recs[0];

    return low;
}

// 快速排序 递归版
void quick_sort_recursive_process(SqList * list, int low, int high, bool asc) {
    if(low < high) {
        int pivot_loc = quick_sort_partitions(list, low, high, asc);
        quick_sort_recursive_process(list, low, pivot_loc - 1, asc);
        quick_sort_recursive_process(list, pivot_loc + 1, high, asc);
    }
}

// 快速排序
void quick_sort_recursive(SqList * list, bool asc) {
    quick_sort_recursive_process(list, 1, list->length, asc);
}

/*****************交换排序 end************************/

/*****************选择排序 start**********************/

// 简单选择排序
void simple_selection_sort(SqList * list, bool asc) {
    for(int i = 1; i < list->length; i++) {
        int k = i;  // 临时变量 记录此时的i值
        for(int j = i+1; j <= list->length; j++) {
            // 简单选择排序并不会在内层循环里 发生实际的交换 而是记录每次循环需要交换的下标
            // 正序排序时 每趟排序要找到当前未排序序列的最小值 compare(j, k) 需要 小于0 j-k < 0
            // 倒序排序时 每趟排序要找到当前未排序序列的最大值 compare(j, k) 需要 小于0 k-j < 0
            if(compare(&list->recs[j].key, &list->recs[k].key, asc) < 0)
                k = j;
        }
        if(k != i) {
            rec_type tmp = list->recs[k];
            list->recs[k] = list->recs[i];
            list->recs[i] = tmp;
        }
    }
}

// 堆排序调整函数
// 此时list[s+1:m]是堆 目的是将list[s:m]调整为堆
// 正序排序使用最大堆 倒序排序使用最小堆
void heap_adjust(SqList * list, int s, int m, bool asc) {
    // 堆调整函数
    // 以正序解释函数逻辑
    // 目的是将序列r[s...m]调整为堆 而r[s+1...m]已经是堆
    // 先取出s的左右结点的最大结点 判断s和该结点的大小关系
    //      如果根大于结点 说明已经是堆
    //      如果小于结点 则交换根和结点的位置
    // 再以该子树为树 重复过程

    // 保存旧根结点 如果需要更新 每次将子结点的值存到根的位置 退出循环后需要将该值放到找到的位置
    rec_type old_root = list->recs[s];

    for(int i = 2 * s; i <= m; i *= 2) {      // 查找s的子结点 但是要注意长度
        // 判断使用哪个子结点
        // 正序时使用最大堆 若compare < 0 说明 a < b 则应该使用b
        // 倒序时使用最小堆 若compare < 0 说明 a > b 则应该使用b
        if(i < m && compare(&list->recs[i].key, &list->recs[i+1], asc) < 0)
            i ++;

        // 判断r[s]和左右子树的关系 由于始终要调整的是r[s]的位置 而s又会变化 所以使用old_root变量
        // 正序时使用最大堆 若compare > 0 说明 a > b 说明此时已经是堆 退出
        // 倒序时使用最小堆 若compare > 0 说明 a < b 说明此时已经是堆 退出
        if(compare(&old_root.key, &list->recs[i].key, asc) > 0)
            break;

        // 将对应子树的值换到根部 同时更新s 保留初始r[s]应插入的位置
        // 继续循环 就是将i为根结点的子树调整为堆
        list->recs[s] = list->recs[i];
        s = i;
    }

    // 循环退出时的s就是最开始r[s]元素应该移动到的地方
    list->recs[s] = old_root;
}

// 堆排序建初堆
void heap_init(SqList * list, bool asc) {
    // 对于一个序列 因其是按照完全二叉树存储 根据完全二叉树性质 n/2后的都是叶结点
    // 因此这些结点都可认为是堆
    // 现在要做的 就是从n/2开始 将该结点和后面的结点一起初始化为堆
    for(int i = list->length / 2; i >= 1; i--)
        heap_adjust(list, i, list->length, asc);
}

// 堆排序
void heap_sort(SqList * list, bool asc) {
    // 建初堆
    heap_init(list, asc);

    // 每次循环 将堆首与当前循环的序列的最后一位交换位置
    for(int i = list->length; i > 1; i--) {
        rec_type tmp= list->recs[1];
        list->recs[1] = list->recs[i];
        list->recs[i] = tmp;

        heap_adjust(list, 1, i-1, asc);

    }
}

/*****************选择排序 end************************/

/*****************归并排序 start**********************/

// 二路归并排序 合并相邻子序列
void two_way_merge_sub_process(SqList * list, SqList * target, int low, int mid, int high, bool asc) {
    // 合并两个子序列 并将合并后的值存入target
    // low表示第一个子序列的开始，mid表示第一个子序列的结束
    // mid+1表示第二个子序列的开始，high表示第二个子序列的结束
    int i = low;
    int j = mid + 1;
    int target_idx = low;
    // 确保不越界
    while(i <= mid && j <= high) {
        // compare > 0 说明 a > b asc 或 a < b desc
        // 则都需要将b放入target里
        // 其他时 需要将a放到target里
        if(compare(&list->recs[i].key, &list->recs[j].key, asc) > 0)
            target->recs[target_idx++] = list->recs[j++];
        else
            target->recs[target_idx++] = list->recs[i++];
    }

    // 剩余的直接放入target
    // 两个while只会执行一个
    while(i <= mid)
        target->recs[target_idx++] = list->recs[i++];
    while(j <= high)
        target->recs[target_idx++] = list->recs[j++];
}

// 二路归并排序 递归过程
void two_way_merge_recursive_process(SqList * list, SqList * target, SqList * tmp, int low, int high, bool asc) {
    // 每次递归到low=high 将元素从list复制到tmp里
    if(low == high)
        tmp->recs[low] = list->recs[low];
    else {
        int mid = (low + high) / 2;
        two_way_merge_recursive_process(list, target, tmp, low, mid, asc);
        two_way_merge_recursive_process(list, target, tmp, mid + 1, high, asc);
        two_way_merge_sub_process(tmp, target, low, mid, high, asc);
        // 每次排序后 排序的子序列在target里 但是sub_process需要将有序的tmp和target合并
        // 所以此处按照target目前有序的长度，覆盖tmp
        for(int i = 1; i <= high; i++)
            tmp->recs[i] = target->recs[i];
    }
}

// 二路归并排序 递归
void two_way_merge_sort_recursive(SqList * list, bool asc) {
    SqList tmp;
    tmp.length = list->length;
    two_way_merge_recursive_process(list, list, &tmp,  1, list->length, asc);
}

// 二路归并排序 迭代
void two_way_merge_sort_iterative(SqList * list, bool asc) {
    SqList target;
    target.length = list->length;
    for(int sub_len = 1; sub_len < list->length; sub_len *= 2) {
        for (int i = 1; i <=list->length ; i = i + 2 * sub_len) {
            int mid = (i + sub_len - 1 <= list->length ? i + sub_len - 1 : list->length);
            int high = (i + 2*sub_len - 1 <= list->length ? i + 2*sub_len - 1 : list->length);

            two_way_merge_sub_process(list, &target, i, mid, high, asc);
        }
        for(int i = 1; i <= list->length; i++)
            list->recs[i] = target.recs[i];
    }
}

/*****************归并排序 end************************/

/*****************分配排序 start**********************/

// 基数排序数据类型
// 基数排序宏定义
#define MAXNUM_KEY 8
#define RADIX 10
#define MAX_SPACE 1000

// 静态链表结点类型
typedef struct {
    key_type keys[MAXNUM_KEY];
    int next;
} SLCell;

// 静态链表 类型
typedef struct {
    SLCell recs[MAX_SPACE];
    key_type nums[MAX_SPACE];
    int keys_length;                    // 存储关键字长度
    int rec_nums;                       // 存储记录总数
}SLList;

typedef int Radix_List[RADIX];          // 存储各个基数的数组 内容为下标

void generate_sllist(SLList *list) {
    srand(11); // 设置随机数种子 防止数据变化

    list->rec_nums = MAXSIZE;
    list->keys_length = 3;
    for(int i = 1; i < list->rec_nums; i++)
        for(int j = 0; j < 3; j++)
            list->recs[i].keys[j] = -1;


    int cnt = 1;

    while(cnt <= list->rec_nums) {
        bool dup_flag = false;
        int rand_int = rand() % 1000 + 1; // 随机生成1-1000的整数

        for(int i = 1; i <= cnt - 1; i++) {
            if(list->nums[i] == rand_int) {
                dup_flag = true;
                break;
            }
        }
        if(!dup_flag) {
            list->nums[cnt] = rand_int;
            cnt ++;
        }
    }

    for(int i = 1; i < list->rec_nums; i++) {
        int tmp = list->nums[i];
        int idx = 2;
        while(tmp != 0) {
            list->recs[i].keys[idx] = tmp % 10;
            idx --;
            tmp = tmp / 10;
        }
        if(list->recs[i].keys[1] == -1)
            list->recs[i].keys[1] = 0;
        if(list->recs[i].keys[0] == -1)
            list->recs[i].keys[0] = 0;
    }
}


// 基数排序 找到下一个下标
int sub_radix_sort_find_next_index(int cur_index) {
    return cur_index + 1;
}

// 基数排序 分配函数
void radix_sort_distribute(SLCell * recs, int radix_index, Radix_List  f, Radix_List  e) {
    // radix_index指向的是关键字的第几位 从低位到高位 此时为2到0 的顺序
    // f和e是分组数组 下标表示的是基数的范围 从0到9
    // f存储的是分组内第一个元素的下标 e存储的是最后一个元素的下标

    // 该函数使得每个分组内的元素彼此链接

    // 初始化f
    for(int i = 0; i < RADIX; i++)
        f[i] = 0;

    for(int p = recs[0].next; p; p = recs[p].next) {
        int j = recs[p].keys[radix_index];    // 对应下标
        if(f[j] == 0)                         // 如果此时f[j]没有指向 则指向p
            f[j] = p;
        else                                  // 如果有指向了 则更新最后一个元素的next 使其指向p
            recs[e[j]].next = p;
        e[j] = p;                             // 更新e数组
    }
}

// 基数排序 收集函数
void radix_sort_collect(SLCell * recs, int radix_index, const Radix_List  f, const Radix_List e) {
    // 该函数负责将各个非空的radix数组里的最后一个元素和第一个元素相连
    int j ;
    for(j = 0; f[j] == 0; j = sub_radix_sort_find_next_index(j));
    recs[0].next = f[j];
    int t = e[j];
    while(j < RADIX-1) {
        for(j = sub_radix_sort_find_next_index(j); j < RADIX - 1 && f[j] == 0; j = sub_radix_sort_find_next_index(j));
        if(f[j]) {
            recs[t].next = f[j];
            t = e[j];
        }
    }
    recs[t].next = 0;
}

// 基数排序
void radix_sort(SLList * list) {
    for(int i = 0; i < list->rec_nums; i++)
        list->recs[i].next = i+1;                // 更新next
    list->recs[list->rec_nums].next = 0;         // 最后一个元素 next需要为0
    Radix_List f;
    Radix_List e;
    for(int i = list->keys_length - 1; i >= 0; i--) {
        radix_sort_distribute(list->recs, i, f, e);
        radix_sort_collect(list->recs, i, f, e);
    }
}

/*****************分配排序 end************************/


int main() {
    // SqList list;
    // generate_sqlist(&list);
    // print_sqlist(list);
    //
    // two_way_merge_sort_recursive(&list, false);
    // print_sqlist(list);

    SLList list;
    generate_sllist(&list);
    for(int i = 1; i < list.rec_nums; i++)
        printf("%d ", list.nums[i]);
    putchar('\n');
    for(int i = 1; i < list.rec_nums; i++) {
        for(int j = 0; j < 3; j++)
            printf("%d", list.recs[i].keys[j]);
        putchar(' ');
    }
    putchar('\n');

    radix_sort(&list);

    int p = list.recs[0].next;

    while(p) {
        for(int i = 0; i < 3; i++)
            printf("%d", list.recs[p].keys[i]);
        putchar('\n');
        p = list.recs[p].next;
    }




    return 0;
}

