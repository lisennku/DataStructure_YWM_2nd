//
// Created by lisen on 24-9-6.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_SIZE 101    // 顺序表数组长度为101，但是0位不用，所以实际上只能存储100个数组元素

// 查找表 项
struct elem_type {
    int key;
    char info;
};

typedef struct elem_type Elem_Type;

// 查找表
struct sequence_table {
    Elem_Type * sq_table;  // 0位不存储顺序表内的实际数据，从1位开始存储
    unsigned int length;
};

typedef struct sequence_table SSTable;

// 分块查找索引表 项
struct index_item {
    Elem_Type key;
    int position;
    int block_lens;
};

typedef struct index_item Index_Item;

// 数组正向排序 二分查找使用
void array_asc_sort(int * arr, int n) {
    for(int top = 0; top < n - 1; top++) {
        for(int seek = top + 1; seek < n; seek++) {
            int tmp ;
            if(arr[top] > arr[seek]) {
                tmp = arr[top];
                arr[top] = arr[seek];
                arr[seek] = tmp;
            }
        }
    }
}

// 数组是否正向排序 二分查找使用
bool is_array_asc_sort(int * arr, int n) {
    if(n == 1)
        return true;
    for(int i = 0; i < n - 1; i++)
        if(arr[i] > arr[i + 1])
            return false;
    return true;
}

// 初始化查找表
void init(SSTable * s) {
    s->sq_table = (Elem_Type *) malloc(sizeof(Elem_Type) * MAX_SIZE);
    if(s->sq_table == NULL)
        exit(-1);

    s->length = 0;
}

// 将数组复制到查找表内
bool array_copy_to_sstable(SSTable * s, const int * arr, int n) {
    if(n > MAX_SIZE - 1)
        return false;
    for(int i = 1; i <= n; i++) {
        s->sq_table[i].key = arr[i-1];
        s->sq_table[i].info = '\0';    // info成员初始化为空
        s->length ++;
    }

    return true;
}

// 普通顺序查找
int sstable_normal_sequence_search(SSTable s, int target) {
    for(int i = 1; i < s.length; i++)
        if(s.sq_table[i].key == target)
            return i;
    return 0; // 查找不到返回0
}

// 哨兵顺序查找
int sstable_sentry_sequence_search(SSTable s, int target) {
    // sstable_normal_sequence_search方法中
    // for循环有两步操作
    //  1 是每次都要检测循环进入的条件表达式
    //  2 是每次都要用当前的顺序表的key成员是否和target相等
    // 设置哨兵可以减少循环里的操作，以便缩短时间
    s.sq_table[0].key = target; // 借助0位
    int i;
    // 因为借助的是0位，所以要从后往前查找
    for (i = s.length; s.sq_table[i].key != target; i--);

    return i;
}

// 迭代二分查找
int sstable_iterative_binary_search(SSTable s, int target) {
    /*
     * 该函数以数组按照正序排序后进行查找为基础
     */
    int low = 1;
    int high = s.length;

    while(low <= high) {
        int mid = (low + high) / 2;
        if(s.sq_table[mid].key == target)
            return mid;
        if(s.sq_table[mid].key < target) {
            low = mid + 1;
        }
        else
            high = mid - 1;
    }

    return 0;
}

// 递归二分查找
int sstable_recursive_binary_search(SSTable s, int target, int low, int high){
    if (low > high)  // 递归基准条件
        return 0;

    int mid = (low + high) / 2;

    if(s.sq_table[mid].key == target)
        return mid;
    if(s.sq_table[mid].key < target)
        return sstable_recursive_binary_search(s, target, mid+1, high);
    else
        return sstable_recursive_binary_search(s, target, low, mid-1);
}

// 分块查找 索引表排序函数 在sqrt中使用
int sub_block_search_index_table_cmp(const void * a, const void *b) {
    return (*(Index_Item *)a).key.key < (*(Index_Item *)b).key.key ? -1 : 1;
}

// 分块查找 索引表二分查找
int sstable_block_search_with_binary(SSTable s, int target) {
    // 分块 按照索引表表长的平方根确定分块的数量
    int blocks_nums = (int)sqrt(s.length);                         // 块数
    int blocks_lens = (int)(s.length / blocks_nums);               // 块长
    int last_blocks_lens = s.length - (blocks_nums - 1) * blocks_lens;   // 最后一个块长

    // 初始化索引表
    Index_Item index[blocks_nums];
    for(int i = 0; i < blocks_nums; i++) {
        int start_position = i * blocks_lens + 1;  // 每个分块 在查找表中的起始位置下标
        index[i].position = start_position;        // 每个块的起始位置
        index[i].block_lens = (i == blocks_nums - 1 ? last_blocks_lens : blocks_lens);  // 每个块的大小

        // 求解每个块中最大的关键值
        Elem_Type tmp = s.sq_table[start_position];   // 临时变量，初始为每个块在查找表中的起始元素
        for(int j = 1; j < index[i].block_lens; j ++) {
            if(tmp.key < s.sq_table[j+start_position].key)
                tmp = s.sq_table[j+start_position];
        }

        index[i].key = tmp;
    }

    // 对索引表进行正排
    qsort(index, blocks_nums, sizeof(Index_Item), sub_block_search_index_table_cmp);

    // for(int i = 0; i < blocks_nums; i++) {
    //     printf("No. %d block\n", i);
    //     printf("block starts from %d, length is %d, item value is %d\n", index[i].position, index[i].block_lens, index[i].key.key);
    // }

    // 索引表查找 二分法
    int low = 0;
    int high = blocks_nums - 1;

    // 存在两种情况
    // 一种是正好可以找到target 则使用mid即可
    // 一种是找不到target 此时low大于high，而我们要找的是第一个大于target的位置 所以使用low
    while(low <= high) {
        int mid = (low + high) / 2;
        if(index[mid].key.key == target) { // 找到该值 则将low赋值为mid 使用low是为了配合找不到值时 使用low
            low = mid;
            break;
        }
        if(index[mid].key.key < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    // 对于在索引表中找不到target时 需要判断是否大于索引表长度 大于表示查找表中直接没有该元素
    if(low >= blocks_nums)
        return 0;

    // 顺序查找子表
    for(int i = index[low].position; i < index[low].block_lens + index[low].position; i++) {
        if(s.sq_table[i].key == target)
            return i;
    }

    return 0;   // 找不到
}

// 分块查找 索引表顺序查找
int sstable_block_search_with_sequence(SSTable s, int target) {
// 分块 按照索引表表长的平方根确定分块的数量
    int blocks_nums = (int)sqrt(s.length);                         // 块数
    int blocks_lens = (int)(s.length / blocks_nums);               // 块长
    int last_blocks_lens = s.length - (blocks_nums - 1) * blocks_lens;   // 最后一个块长

    // 初始化索引表
    Index_Item index[blocks_nums];
    for(int i = 0; i < blocks_nums; i++) {
        int start_position = i * blocks_lens + 1;  // 每个分块 在查找表中的起始位置下标
        index[i].position = start_position;        // 每个块的起始位置
        index[i].block_lens = (i == blocks_nums - 1 ? last_blocks_lens : blocks_lens);  // 每个块的大小

        // 求解每个块中最大的关键值
        Elem_Type tmp = s.sq_table[start_position];   // 临时变量，初始为每个块在查找表中的起始元素
        for(int j = 1; j < index[i].block_lens; j ++) {
            if(tmp.key < s.sq_table[j+start_position].key)
                tmp = s.sq_table[j+start_position];
        }

        index[i].key = tmp;
    }

    // 对索引表进行正排
    qsort(index, blocks_nums, sizeof(Index_Item), sub_block_search_index_table_cmp);

    // for(int i = 0; i < blocks_nums; i++) {
    //     printf("No. %d block\n", i);
    //     printf("block starts from %d, length is %d, item value is %d\n", index[i].position, index[i].block_lens, index[i].key.key);
    // }

    // 索引表查找 顺序查找
    int low = -1;
    for(int i = 0; i < blocks_nums; i++) {
        if(target <= index[i].key.key) {
            low = i;
            break;
        }
    }

    // 如果在索引表中找不到位置，则说明查找表中无该元素
    if (low == -1)
        return 0;

    // 顺序查找子表
    for(int i = index[low].position; i < index[low].block_lens + index[low].position; i++) {
        if(s.sq_table[i].key == target)
            return i;
    }

    return 0;   // 找不到
}

int main() {
    SSTable s;
    init(&s);

    int arr[10] = {2, 5, 10, 100, 42, 45, 90, 54, 99, 88};

#if 0
    // 顺序表的顺序查找
    array_copy_to_sstable(&s, arr, 10);

    for(int i = 1; i <= s.length; i++)
        printf("%d ", s.sq_table[i].key);
    putchar('\n');

    int target = 42;
    // int pos = sstable_normal_sequence_search(s, target);
    int pos = sstable_sentry_sequence_search(s, target);
    if(pos)
        printf("target %d found! position is %d\n", target, pos);
    else
        printf("target %d not found\n", target);
#endif
#if 0
    // 二分查找
    array_asc_sort(arr, 10);
    array_copy_to_sstable(&s, arr, 10);
    for(int i = 1; i <= s.length; i++)
        printf("%d ",s.sq_table[i].key);
    putchar('\n');
    if(is_array_asc_sort(arr, 10)) {
        int target = 88;
        // int pos = sstable_iterative_binary_search(s, target);
        int pos = sstable_recursive_binary_search(s, target, 1, 10);
        if(pos)
            printf("target %d found! position is %d\n", target, pos);
        else
            printf("target %d not found\n", target);
    }
    else
        printf("array is not sorted yet\n");
#endif
#if 0
    int target = -10000;
    array_copy_to_sstable(&s, arr, 10);
    int pos = sstable_block_search_with_binary(s, target);
    // int pos = sstable_block_search_with_sequence(s, target);
    if(pos)
        printf("target %d found! position is %d\n", target, pos);
    else
        printf("target %d not found\n", target);
#endif
    return 0;
}
