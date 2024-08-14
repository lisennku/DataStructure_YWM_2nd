1．选择题  
（1）顺序表中第一个元素的存储地址是100，每个元素的长度为2，则第5个元素的地址是(<font color=red> B </font>)  
&nbsp;&nbsp;&nbsp;&nbsp;A. 110  
&nbsp;&nbsp;&nbsp;&nbsp;B. 108  
&nbsp;&nbsp;&nbsp;&nbsp;C. 100  
&nbsp;&nbsp;&nbsp;&nbsp;D. 120  
（2）在含n个结点的顺序表中，算法的时间复杂度是O(1)的操作是(<font color=red> A </font>)  
&nbsp;&nbsp;&nbsp;&nbsp;A. 访问第i个结点（1≤i≤n）和求第i个结点的直接前驱（2≤i≤n）  
&nbsp;&nbsp;&nbsp;&nbsp;B. 在第i个结点后插入一个新结点（1≤i≤n）  
&nbsp;&nbsp;&nbsp;&nbsp;C. 删除第i个结点（1≤i≤n）  
&nbsp;&nbsp;&nbsp;&nbsp;D. 将n个结点从小到大排序  
（3）在一个有127个元素的顺序表中插入一个新元素并保持原来顺序不变，平均要移动的元素个数为(<font color=red> B </font>)  
&nbsp;&nbsp;&nbsp;&nbsp;A. 8  
&nbsp;&nbsp;&nbsp;&nbsp;B. 63.5  
&nbsp;&nbsp;&nbsp;&nbsp;C. 63   
&nbsp;&nbsp;&nbsp;&nbsp;D. 7  
（4）链接存储的存储结构所占存储空间(<font color=red> A </font>)  
&nbsp;&nbsp;&nbsp;&nbsp;A. 分为两部分，一部分存放结点值，另一部分存放表示结点间关系的指针  
&nbsp;&nbsp;&nbsp;&nbsp;B. 只有一部分，存放结点值  
&nbsp;&nbsp;&nbsp;&nbsp;C. 只有一部分，存储表示结点间关系的指针  
&nbsp;&nbsp;&nbsp;&nbsp;D. 分两部分，一部分存放结点值，另一部分存放结点所占单元数  
（5）线性表若采用链式存储结构，要求内存中可用存储单元的地址(<font color=red> D </font>)  
&nbsp;&nbsp;&nbsp;&nbsp;A. 必须是连续的  
&nbsp;&nbsp;&nbsp;&nbsp;B. 部分地址必须是连续的   
&nbsp;&nbsp;&nbsp;&nbsp;C. 一定是不连续的  
&nbsp;&nbsp;&nbsp;&nbsp;D. 连续或不连续都可以  
（6）线性表L在(<font color=red> B </font>)情况下适用于使用链式结构实现。  
&nbsp;&nbsp;&nbsp;&nbsp;A. 需经常修改L中的结点值  
&nbsp;&nbsp;&nbsp;&nbsp;B. 需不断对L进行删除、插入  
&nbsp;&nbsp;&nbsp;&nbsp;C. L中含有大量的结点  
&nbsp;&nbsp;&nbsp;&nbsp;D. L中结点结构复杂  
（7）单链表的存储密度(<font color=red> C </font>)  
&nbsp;&nbsp;&nbsp;&nbsp;A. 大于1  
&nbsp;&nbsp;&nbsp;&nbsp;B. 等于1  
&nbsp;&nbsp;&nbsp;&nbsp;C. 小于1  
&nbsp;&nbsp;&nbsp;&nbsp;D. 不能确定  
（8）将两个各有n个元素的有序表归并成一个有序表，其最少的比较次数是(<font color=red> A </font>)  
&nbsp;&nbsp;&nbsp;&nbsp;A. n  
&nbsp;&nbsp;&nbsp;&nbsp;B. 2n−1  
&nbsp;&nbsp;&nbsp;&nbsp;C. 2n  
&nbsp;&nbsp;&nbsp;&nbsp;D. n−1  
（9）在一个长度为n的顺序表中，在第i个元素（1≤i≤n+1）之前插入一个新元素时需向后移动(<font color=red> B </font>)个元素。  
&nbsp;&nbsp;&nbsp;&nbsp;A. n−i  
&nbsp;&nbsp;&nbsp;&nbsp;B. n−i+1   
&nbsp;&nbsp;&nbsp;&nbsp;C. n−i−1  
&nbsp;&nbsp;&nbsp;&nbsp;D. i  
（10）线性表L=(a1，a2,…，an)，下列陈述正确的是(<font color=red> D </font>)  
&nbsp;&nbsp;&nbsp;&nbsp;A. 每个元素都有一个直接前驱和一个直接后继   
&nbsp;&nbsp;&nbsp;&nbsp;B. 线性表中至少有一个元素   
&nbsp;&nbsp;&nbsp;&nbsp;C. 表中诸元素的排列必须是由小到大或由大到小   
&nbsp;&nbsp;&nbsp;&nbsp;D. 除第一个和最后一个元素外，其余每个元素都有一个且仅有一个直接前驱和直接后继  
（11）创建一个包括n个结点的有序单链表的时间复杂度是(<font color=red> C </font>)  
&nbsp;&nbsp;&nbsp;&nbsp;A. O(1)  
&nbsp;&nbsp;&nbsp;&nbsp;B. O(n)  
&nbsp;&nbsp;&nbsp;&nbsp;C. O(n2)  
&nbsp;&nbsp;&nbsp;&nbsp;D. O(nlog2n)  
（12）以下陈述错误的是(<font color=red> D </font>)  
&nbsp;&nbsp;&nbsp;&nbsp;A. 求表长、定位这两种运算在采用顺序存储结构时实现的效率不比采用链式存储结构时实现的效率低  
&nbsp;&nbsp;&nbsp;&nbsp;B. 顺序存储的线性表可以随机存取  
&nbsp;&nbsp;&nbsp;&nbsp;C. 由于顺序存储要求连续的存储区域，所以在存储管理上不够灵活  
&nbsp;&nbsp;&nbsp;&nbsp;D. 线性表的链式存储结构优于顺序存储结构  
（13）在单链表中，要将s所指结点插入到p所指结点之后，其语句应为(<font color=red> D </font>)  
&nbsp;&nbsp;&nbsp;&nbsp;A. s->next=p+1; p->next=s;  
&nbsp;&nbsp;&nbsp;&nbsp;B. (*p).next=s; (*s).next=(*p).next;  
&nbsp;&nbsp;&nbsp;&nbsp;C. s->next=p->next; p->next=s->next;  
&nbsp;&nbsp;&nbsp;&nbsp;D. s->next=p->next; p->next=s;  
（14）在双向链表存储结构中，删除p所指结点时修改指针的操作为(<font color=red> A </font>)  
&nbsp;&nbsp;&nbsp;&nbsp;A. p->next->prior=p->prior; p->prior->next=p->next;  
&nbsp;&nbsp;&nbsp;&nbsp;B. p->next=p->next->next; p->next->prior=p;  
&nbsp;&nbsp;&nbsp;&nbsp;C. p->prior->next=p; p->prior=p->prior->prior;  
&nbsp;&nbsp;&nbsp;&nbsp;D. p->prior=p->next->next; p->next=p->prior->prior;  
（15）在双向循环链表中，在p指针所指的结点后插入q所指向的新结点，其修改指针的操作是(<font color=red> C </font>)   
&nbsp;&nbsp;&nbsp;&nbsp;A. p->next=q; q->prior=p; p->next->prior=q; q->next=q;  
&nbsp;&nbsp;&nbsp;&nbsp;B. p->next=q; p->next->prior=q; q->prior=p; q->next=p->next;  
&nbsp;&nbsp;&nbsp;&nbsp;C. q->prior=p; q->next=p->next; p->next->prior=q; p->next=q;  
&nbsp;&nbsp;&nbsp;&nbsp;D. q->prior=p; q->next=p->next; p->next=q; p->next->prior=q;  
