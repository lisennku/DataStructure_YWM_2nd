#include <stdio.h>

#include <stdlib.h>

// 将编号为n的圆盘从A移到C
// m为总移动次数
int m=0;
void move(char A,int n,char C) {
    printf("%d,%d,%c,%c\n", ++m, n, A, C);

}

// 表示将A上的n个圆盘挪到C上，B为辅助
void Hanoi(int n,char A,char B,char C)
{//将塔座A上的n个圆盘按规则搬到C上，B做辅助塔
    if(n==1) move(A,1,C);                //将编号为1的圆盘从A移到C
    else
    {
        Hanoi(n-1,A,C,B);                 //将A上编号为1至n-1的圆盘移到B，C做辅助塔
        move(A,n,C);                    //将编号为n的圆盘从A移到C
        Hanoi(n-1,B,A, C);                //将B上编号为1至n-1的圆盘移到C，A做辅助塔
    }
}
int main(void)
{
    char A = 'A', B = 'B', C = 'C';
    Hanoi(4, A, B, C);
}
