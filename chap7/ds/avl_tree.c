//
// Created by lisen on 24-9-9.
//
// AVL树严蔚敏版本的数据结构谈到的内容个人感觉较为晦涩
// 可以参考哈哈哈哈栋的公众号文章和B站视频
// B站视频 https://b23.tv/m7OOlv3
// 公众号文章 https://mp.weixin.qq.com/s/mc0_UPNDDrD-rz1LbMBYcA

#include <stdio.h>
#include <stdlib.h>


#define MAX_SIZE 10
typedef int key_type;

struct avl_node {
    key_type key;                  // 关键值
    struct avl_node * left;        // 左子树
    struct avl_node * right;       // 右子树
    int height;                    // 结点最新的树高 新建结点时为1 如果结点为空则为0 但此时无需创建结点
};

typedef struct avl_node AVL_Node;         // 结点类型
typedef struct avl_node * AVL_Tree;       // avl树类型

// 定义AVL树的结点，返回指向该结点的指针
// 内存分配失败直接退出
AVL_Node * avl_tree_create_node(key_type key) {
    AVL_Node * new = (AVL_Node *) malloc(sizeof(AVL_Node));
    if(!new)
        exit(-1);               // 内存分配失败直接退出
    new->key = key;                  // 关键字
    new->left = new->right = NULL;   // 初始化左右子树为NULL
    new->height = 1;                 // 单个结点树高为1

    return new;
}

// 返回传入结点的树高
int avl_tree_get_node_height(AVL_Node * node) {
    if(node == NULL)            // 空结点 返回0
        return 0;
    return node->height;        // 否则返回height成员
}

void avl_tree_update_node_height(AVL_Node * node) {
    int left_height = avl_tree_get_node_height(node->left);
    int right_height = avl_tree_get_node_height(node->right);

    node->height = (left_height > right_height ? left_height : right_height) + 1;
}

// 返回传入结点的平衡因子
int avl_tree_get_balance_factor(AVL_Node * node) {
    int left_height = avl_tree_get_node_height(node->left);
    int right_height = avl_tree_get_node_height(node->right);
    return left_height - right_height;
}

// 左旋操作 对应RR类型/LR类型第一步/RL类型第二步
// 返回新根的指针
AVL_Node * avl_tree_left_rotate(AVL_Node * root) {
    /*
     * 左旋操作
     *  旧根结点，作为新根结点的左子树
     *  旧根结点的右子树，作为新根结点
     *  如果新根结点原来有左子树，则该左子树作为旧根结点的右子树(不会发生冲突，因为旧根结点的右子树已经是新根了)
     */
    AVL_Node * new_root = root->right;        // 创建新根结点的指针，将其指向参数结点的右子树
    root->right = new_root->left;             // 更新参数结点的右子树为新根的左子树
    new_root->left = root;                    // 更新新根的左子树为参数结点

    // 更新树高
    // 先更新参数结点，也即旧根结点的树高，然后再更新新根的树高
    // root的左子树没动，右子树为新根的左子树，也没动，所以直接计算即可
    avl_tree_update_node_height(root);
    // new_root的左子树为更新后的root，右子树没动，所以要先更新root的树高，再更新new_root的树高
    avl_tree_update_node_height(new_root);

    return new_root;

}

// 右旋操作 对应LL类型/LR类型第二步/RL类型第一步
// 返回新根的指针
AVL_Node * avl_tree_right_rotate(AVL_Node * root) {
    /*
     * 右旋操作
     *  旧根结点，作为新根结点的右子树
     *  旧根结点的左子树，作为新根结点
     *  如果新根结点有右子树，则该右子树作为旧根结点的左子树(不会发生冲突，因为旧根结点的左子树已经是新根了)
     */
    AVL_Node * new_root = root->left;         // 创建新根结点的指针，将其指向参数结点的左子树
    root->left = new_root->right;             // 参数结点的左子树指向新根结点的右子树
    new_root->right = root;                   // 新根结点的右子树为参数结点

    // 更新树高
    // 先更新参数结点，也即旧根结点的树高，然后再更新新根的树高
    // root的右子树没动，左子树为新根的右子树，也没动，所以直接计算即可
    avl_tree_update_node_height(root);
    // new_root的右子树为更新后的root，左子树没动，所以要先更新root的树高，再更新new_root的树高
    avl_tree_update_node_height(new_root);

    return new_root;
}

// avl树搜索操作
// 返回指向查找结点的指针
// 找不到返回NULL
AVL_Node * avl_tree_search(AVL_Tree t, key_type key) {
    AVL_Node * find = t;
    while(find != NULL) {
        if(find->key == key)
            return find;
        if(find->key < key)
            find = find->right;
        else
            find = find->left;
    }

    return find;
}

// avl树插入操作
// 每次传入根结点
// 函数最终返回指向最新的avl树的根结点的指针
// 函数使用递归依次更新各自的树高和平衡因子 从而进行旋转调整
AVL_Node * avl_tree_insert(AVL_Node * node, key_type key) {
    // 递归基准条件 如果当前node为NULL，说明找到了正确插入的位置，或者是第一次插入
    if(node == NULL)
        return avl_tree_create_node(key);

    // 递归查找位置
    // 如果相等直接返回
    if(node->key < key)
        node->right = avl_tree_insert(node->right, key);
    else if(node->key > key)
        node->left = avl_tree_insert(node->left, key);
    else
        return node;

    // 插入后要更新树高并计算平衡因子
    // 需要计算的是node的树高 因为是在node的左或右进行插入
    avl_tree_update_node_height(node);
    int bf = avl_tree_get_balance_factor(node);

    // 综合bf和插入位置 判断插入类型
    // LL bf > 1  且 插入位置在左子树的左子树上 也即 node.left.key > key
    // RR bf < -1 且 插入位置在右子树的右子树上 也即 node.right.key < key
    // LR bf > 1  且 插入位置在左子树的右子树上 也即 node.left.key < key
    // RL bf < -1 且 插入位置在右子树的左子树上 也即 node.right.key > key

    // LL
    if(bf > 1 && node->left->key > key) {
        // LL类型需要右旋
        return avl_tree_right_rotate(node);
    }
    // RR
    if(bf < -1 && node->right->key < key) {
        // RR类型需要左旋
        return avl_tree_left_rotate(node);
    }
    // LR
    if(bf > 1 && node->left->key < key) {
        // LR类型
        // 第一步 将node的左子树进行左旋 将新根结点作为node的左子树 变成LL类型
        // 第二步 将node进行右旋
        node->left = avl_tree_left_rotate(node->left);
        return avl_tree_right_rotate(node);
    }
    // RL
    if(bf < -1 && node->right->key > key) {
        // RL类型
        // 第一步 将node的右子树进行右旋 将新根结点作为node的右子树 变成RR类型
        // 第二步 将node进行左旋
        node->right = avl_tree_right_rotate(node->right);
        return avl_tree_left_rotate(node);
    }

    return node;       // 如果不需要进行旋转 也要返回
}

void avl_tree_create(AVL_Tree * avl, const key_type * arr, int len) {
    *avl = NULL;   // 需要初始化 否则异常
    for(int i = 0; i < len; i ++)
        *avl = avl_tree_insert(*avl, arr[i]);
}

void avl_tree_in_order(AVL_Tree t, key_type * out_arr, int * ret_size, int * idx) {
    if(t) {
        avl_tree_in_order(t->left, out_arr, ret_size, idx);
        out_arr[*idx] = t->key;
        (*idx)++;
        (*ret_size)++;
        avl_tree_in_order(t->right, out_arr,ret_size , idx);
    }
}

int main() {
    srand(1); // 设置随机种子

    key_type arr[MAX_SIZE];
    for(int i = 0; i < MAX_SIZE; i ++)
        arr[i] = rand() % 100 + 1;     // 1-100之间的随机数

    printf("array_list is\n");
    for(int i = 0; i < MAX_SIZE; i ++)
        printf("%d ", arr[i]);
    putchar('\n');

    AVL_Tree t;
    avl_tree_create(&t, arr, MAX_SIZE);

    key_type out_arr[MAX_SIZE];
    int ret_size = 0;
    int idx = 0;
    avl_tree_in_order(t, out_arr, &ret_size, &idx);
    for(int i = 0; i < ret_size; i ++)
        printf("%d ", out_arr[i]);
}


