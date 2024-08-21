//
// Created by lisen on 24-8-21.
//
// 输入一个中缀算术表达式，求解表达式的值。运算符包括+、-、*、/、(、)、=，参加运算的数为double类型且为正数。
// （要求：直接针对中缀算术表达式进行计算，不能转换为后缀或前缀表达式再进行计算，只考虑二元运算即可。）

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


/*
 * macro definition
 */
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;

#define MAX_SIZE 100

struct sqstack_OPND {     // 操作数结构
    double * base;
    double * top;
    int     stack_size;
};

typedef struct sqstack_OPND ST_OPND;

struct sqstack_OPTR {     // 操作符结构
    char * base;
    char * top;
    int    stack_size;
};

typedef struct sqstack_OPTR ST_OPTR;

/*
 * function declare
 * C可以接收具有不同参数列表的同名函数
 */

// 初始化
Status expr_stack_init_OPND(ST_OPND * st);
Status expr_stack_init_OPTR(ST_OPTR * st);
// 是否为空
bool expr_stack_is_empty_OPND(ST_OPND st);
bool expr_stack_is_empty_OPTR(ST_OPTR st);
// 长度
int expr_stack_length_OPND(ST_OPND st);
int expr_stack_length_OPTR(ST_OPTR st);
// 栈顶元素
double expr_stack_get_top_OPND(ST_OPND st);
char expr_stack_get_top_OPTR(ST_OPTR st);
// 入栈
Status expr_stack_push_OPND(ST_OPND * st, double num);
Status expr_stack_push_OPTR(ST_OPTR * st, char c);
// 出栈
Status expr_stack_pop_OPND(ST_OPND * st, double * num);
Status expr_stack_pop_OPTR(ST_OPTR * st, char * c);

// 判断输入是否是操作符，是的话返回1，不是的话返回0
int In(char ch);
// 判断栈顶和当前输入的操作符的优先级
char Precede(char top, char ch);
// 加减乘除的计算
double Operate(double a, char c, double b);

// 中序表达式计算
double calc_inorder_expr(char ch);

/*
 * main function
 */
int main() {
    while(1) {
        char ch = getchar();
        if(ch == '=')
            break;
        if(ch != '\n') {
            double res = calc_inorder_expr(ch);
            printf("%.2lf\n", res);
        }
    }
}


/*
 * functions definition
 */

// 初始化
Status expr_stack_init_OPND(ST_OPND * st) {
    st->base = (double *)malloc(sizeof(double) * MAX_SIZE);
    if(st->base == NULL)
        exit(OVERFLOW);

    st->top = st->base;
    st->stack_size = MAX_SIZE;

    return OK;
}
Status expr_stack_init_OPTR(ST_OPTR * st) {
    st->base = (char *)malloc(sizeof(char) * MAX_SIZE);
    if(st->base == NULL)
        exit(OVERFLOW);

    st->top = st->base;
    st->stack_size = MAX_SIZE;

    return OK;
}
// 是否为空
bool expr_stack_is_empty_OPND(ST_OPND st) {
    return st.base == st.top ? true : false;
}
bool expr_stack_is_empty_OPTR(ST_OPTR st) {
    return st.base == st.top ? true : false;
}
// 长度
int expr_stack_length_OPND(ST_OPND st) {
    return st.top - st.base;
}
int expr_stack_length_OPTR(ST_OPTR st) {
    return st.top - st.base;
}
// 栈顶元素
double expr_stack_get_top_OPND(ST_OPND st) {
    if(st.top != st.base)
        return *(st.top - 1);
}
char expr_stack_get_top_OPTR(ST_OPTR st) {
    if(st.top != st.base)
        return *(st.top - 1);
    return ERROR;
}
// 入栈
Status expr_stack_push_OPND(ST_OPND * st, double num) {
    if(st->top - st->base == st->stack_size)
        return ERROR;

    *(st->top)= num;
    st->top ++;

    return OK;
}
Status expr_stack_push_OPTR(ST_OPTR * st, char c) {
    if(st->top - st->base == st->stack_size)
        return ERROR;

    *(st->top)= c;
    st->top ++;

    return OK;
}
// 出栈
Status expr_stack_pop_OPND(ST_OPND * st, double * num) {
    if(st->base == st->top)
        return ERROR;
    st->top --;
    *num = *(st->top);

    return OK;
}
Status expr_stack_pop_OPTR(ST_OPTR * st, char * c) {
    if(st->base == st->top)
        return ERROR;
    st->top --;
    *c = *(st->top);

    return OK;
}

// 判断输入是否是操作符，是的话返回1，不是的话返回0
int In(char ch) {
    const char optrs[] = "+-*/()=";
    char s[2] = {ch, '\0'};
    if (strstr(optrs, s) != NULL)
        return 1;
    return 0;
}
// 判断栈顶和当前输入的操作符的优先级
char Precede(char top, char ch) {
    char sym;
    switch (top) {
        case '+':
        case '-':
            switch (ch) {
                case '+':
                case '-':
                case ')':
                case '=': sym = '>'; break;
                case '*':
                case '/':
                case '(': sym = '<'; break;
            } break;

        case '*':
        case '/':
            switch (ch) {
                case '+':
                case '-':
                case '*':
                case '/':
                case ')':
                case '=': sym = '>'; break;
                case '(': sym = '<'; break;
            }break;
        case '(':
            switch (ch) {
                case '+':
                case '-':
                case '*':
                case '/':
                case '(': sym = '<'; break;
                case ')': sym = '='; break;
                case '=': sym = ' '; break;
            }break;
        case ')':
            switch (ch) {
                case '+':
                case '-':
                case '*':
                case '/':
                case ')':
                case '=': sym = '>'; break;
                case '(': sym = ' '; break;
            }break;
        case '=':
            switch (ch) {
                case '+':
                case '-':
                case '*':
                case '/':
                case '(': sym = '<'; break;
                case '=': sym = '='; break;
                case ')': sym = ' '; break;
            } break;
    }
    return sym;

}
// 加减乘除的计算
double Operate(double a, char c, double b) {
    double sum = 0;
    switch (c) {
        case '+': sum = a + b; break;
        case '-': sum = a - b; break;
        case '*': sum = a * b; break;
        case '/': sum = a / b; break;
    }
    return sum;
}

// 中序表达式计算
double calc_inorder_expr(char ch) {
    ST_OPND OPND;
    ST_OPTR OPTR;

    if(expr_stack_init_OPND(&OPND) != OK || expr_stack_init_OPTR(&OPTR) != OK)
        exit(OVERFLOW);

    expr_stack_push_OPTR(&OPTR, '=');

    // 对输入做判断
    while(ch != '=' || expr_stack_get_top_OPTR(OPTR) != '=') {  // 尚未遍历完表达式，或者没有计算完
        if(!In(ch)) {
            int i = 0;
            char digits[100];
            // 不填充初始值，会导致第n次循环中，如果数字长度不够覆盖n-1次的数字，导致获取数字异常
            memset(digits, '\0', sizeof(digits));
            double converted_digits;
            while((ch >= '0' && ch <= '9') || ch == '.') {
                digits[i] = ch;
                i ++;
                ch = getchar();
            }
            if(i != 0) {
                converted_digits = atof(digits);
                expr_stack_push_OPND(&OPND, converted_digits);
            }
        }
        else {
            double a, b, res_tmp;
            char c;
            Status sa, sb, sc;
            switch (Precede(expr_stack_get_top_OPTR(OPTR), ch)) {
                case '<':              // 栈顶符号优先级小于输入符号，则输入符号入栈，继续输入
                    expr_stack_push_OPTR(&OPTR, ch);
                    ch = getchar();
                    break;
                case '>':              // 栈顶符号优先级大于输入符号，则弹出两个操作数和一个符号，将运算后结果入栈，注意，此时不需要继续输入

                    //先弹出的操作数位于二元操作符的后面
                    sb = expr_stack_pop_OPND(&OPND, &b);
                    sa = expr_stack_pop_OPND(&OPND, &a);
                    sc = expr_stack_pop_OPTR(&OPTR, &c);
                    if((sa != OK) || (sb != OK) || (sc != OK))
                        exit(ERROR);
                    res_tmp = Operate(a, c, b);
                    expr_stack_push_OPND(&OPND, res_tmp);
                    break;
                case '=':              // 栈顶为=且输入符号为=，弹出括号
                    sc = expr_stack_pop_OPTR(&OPTR, &c);
                    if(sc != OK)
                        exit(ERROR);
                    ch = getchar();
                    break;
            }
        }
    }
    return expr_stack_get_top_OPND(OPND);
}