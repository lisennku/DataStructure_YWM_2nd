1．串是一种特殊的线性表，其特殊性体现在(<font color=green>  B  </font>)。  
> 串的特殊性体现在内容受限

&emsp;A．可以顺序存储  
&emsp;B．数据元素是一个字符  
&emsp;C．可以链式存储  
&emsp;D．数据元素可以是多个字符  
2．下面关于串的叙述中，(<font color=green>  B  </font>)是不正确的。  
> 空串是指包括零个字符的串，只有空格的串是空格串

&emsp;A．串是字符的有限序列  
&emsp;B．空串是由空格构成的串  
&emsp;C．模式匹配是串的一种重要运算  
&emsp;D．串既可以采用顺序存储，也可以采用链式存储  
3．串“ababaaababaa”的next数组为(<font color=green>  C  </font>)。  
&emsp;A．012345678999  
&emsp;B．012121111212  
&emsp;C．011234223456  
&emsp;D．0123012322345  
4．串“ababaabab”的nextval数组为(<font color=red>  A  </font>)。   错误选择D  
&emsp;A．010104101  
&emsp;B．010102101  
&emsp;C．010100011  
&emsp;D．010101011  
5．串的长度是指(<font color=green>  B  </font>)。  
&emsp;A．串中所含不同字母的个数  
&emsp;B．串中所含字符的个数  
&emsp;C．串中所含不同字符的个数  
&emsp;D．串中所含非空格字符的个数  
6．假设以行序为主序存储二维数组A=array[1，…，100，1，…，100]，设每个数据元素占2个存储单元，基地址为10，则LOC[5,5]=(<font color=red>  B  </font>)。  错误选择A  
> 起始地址是10
> 设二维数组A[s...m, t...n]以行序存储，起始地址是Loc(s,t)，则Loc(i, j) = Loc(s, t) + ((i-s)(n-t+1)+(j-t))*L

&emsp;A．808  
&emsp;B．818  
&emsp;C．1010  
&emsp;D．1020  
7．设有数组A[i,j]，数组的每个元素长度为3字节，i的值为1到8，j的值为1到10，数组从内存首地址BA开始顺序存放，当用以列为主存放时，元素A[5,8]的存储首地址为(<font color=green>  B  </font>)。  
&emsp;A．BA+141  
&emsp;B．BA+180  
&emsp;C．BA+222  
&emsp;D．BA+225  
8．设有一个10阶的对称矩阵A，采用压缩存储方式，以行序为主存储，a11为第一元素，其存储地址为1，每个元素占一个地址空间，则a85的地址为(<font color=green>  C  </font>)。  
&emsp;A．13  
&emsp;B．32  
&emsp;C．33  
&emsp;D．40  
9．若对n阶对称矩阵A以行序为主序方式将其下三角形的元素（包括主对角线上所有元素）依次存放于一维数组B[1...(n(n+1))/2]中，则在B中确定aij（i<j）的位置k的关系为(<font color=red>  B  </font>)。  错误选择A 
> 选项A是aij(i>=j)时的公式，也即下三角，题目要求**上三角**  
> 因为对称矩阵中， aij = aji，所以替换公式中的ij即可

&emsp;A．i*(i-1)/2+j  
&emsp;B．j*(j-1)/2+i  
&emsp;C．i*(i+1)/2+j  
&emsp;D．j*(j+1)/2+i  
10．二维数组A的每个元素是由10个字符组成的串，其行下标i=0，1，…，8，列下标j=1，2，…，10。若A按行先存储，元素A[8,5]的起始地址与当A按列先存储时的元素(<font color=green>  B  </font>)的起始地址相同。设每个字符占1字节。  
&emsp;A．A[8,5]  
&emsp;B．A[3,10]  
&emsp;C．A[5,8]  
&emsp;D．A[0,9]  
11．二维数组A[1，…，m，1，…，n]（即m行n列）按行存储在数组B[1，…，m*n]中，则二维数组元素A[i,j]在一维数组B中的下标为(<font color=red>  A  </font>)。  错误选择B  
> 数组从1开始，而不是0，所以不需要减1

&emsp;A．(i-1)*n+j  
&emsp;B．(i-1)*n+j-1  
&emsp;C．i*(j-1)  
&emsp;D．j*m+i-1  
12.[0，…，4，-1，…，-3，5，…，7]中含有元素的个数(<font color=red>  B  </font>)。  
> [0，…，4，-1，…，-3，5，…，7]表示的是三维数组，各维度长度为4-0+1; -1-(-3) +1; 7-5+1

&emsp;A．55  
&emsp;B．45  
&emsp;C．36  
&emsp;D．16  
13．广义表A=(a,b,(c,d),(e,(f,g)))，则Head(Tail(Head(Tail(Tail(A)))))的值为(<font color=red>  D  </font>)。  错误选择B  
&emsp;A．(g)  
&emsp;B．(d)  
&emsp;C．c  
&emsp;D．d  
14．广义表((a,b,c,d))的表头是(<font color=green>  C  </font>)，表尾是(<font color=green>  B  </font>)。  
&emsp;A．a  
&emsp;B．( )  
&emsp;C．(a,b,c,d)  
&emsp;D．(b,c,d)  
15．设广义表L=((a,b,c))，则L的长度和深度分别为(<font color=green>  C  </font>)。  
> 深度是指广义表中括号的层数

&emsp;A．1和1  
&emsp;B．1和3  
&emsp;C．1和2  
&emsp;D．2和3  
16.【2015年第8题】已知字符串s为“abaabaabacacaabaabcc”，模式串t为“abaabc”。采用KMP算法进行匹配，第一次出现“失配”（s[i]!=t[j]）时，i=j=5，则下次开始匹配时，i和j的值分别是(<font color=green>  C  </font>)。  
&emsp;A．i=1，j=0  
&emsp;B．i=5，j=0  
&emsp;C．i=5，j=2  
&emsp;D．i=6，j=2  
17.【2016年第4题】有一个100阶的`三对角矩阵`M，其元素mi,j(1≤i≤100，1≤j≤100)按行优先次序压缩存入下标从0开始的一维数组Ⅳ中。元素m30,30在N中的下标是(<font color=red>  B  </font>)。  
> 三对角矩阵，指的是三条对角线上非零，其他都是0
> n对角矩阵，意味着首尾两行，有n-1个元素，其余行为n个
> 所以，三对角矩阵，首行有2个元素，m3030，前面有29行，所以共 28*3+2 = 86个元素，又因为m3030是第二个元素，所以是第88个元素
> 又因为数组从0开始，所以下标是87

&emsp;A．86  
&emsp;B．87  
&emsp;C．88  
&emsp;D．89  
18．对于KMP算法，在模式匹配时指示主串匹配位置的指针(<font color=green>  B  </font>)。  
&emsp;A．不会变大  
&emsp;B．不会变小  
&emsp;C．都有可能  
&emsp;D．无法判断  
19．设主串的长度为n，子串的长度为m，那么BF算法的时间复杂度为(<font color=green>  C  </font>)，KMP算法的时间复杂度为(<font color=green>  D  </font>)。  
&emsp;A．O(m)  
&emsp;B．O(n)  
&emsp;C．O(n×m)  
&emsp;D．O(n+m)  
20．设有两个串S1和S2，求S2在S1中首次出现的位置的运算称作(<font color=green>  C  </font>)。  
&emsp;A．求子串  
&emsp;B．判断是否相等  
&emsp;C．模式匹配  
&emsp;D．连接  
21．若串S=“software”，其子串的数目是(<font color=red>  B  </font>)。  错误选择C  
> 空串是任何字符串的子串，所以有37个子串

&emsp;A．8  
&emsp;B．37  
&emsp;C．36  
&emsp;D．9  
22．将三对角矩阵A[1，…，100，1，…，100]按行优先存入一维数组B[1，…，298]中，A中元素A[66,65]在B中的位置K为(<font color=red>  B  </font>)。  
> 仍然是三对角矩阵，而不是对称矩阵
> 64*3+2+1 = 195

&emsp;A．198  
&emsp;B．195  
&emsp;C．197  
&emsp;D．199  
23．二维数组A的元素都是6个字符组成的串，行下标i的范围从0到8，列下标j的范围从1到10，从供选择的答案中分别选出正确答案。  
&emsp;（1）存放A至少需要(<font color=green>  D  </font>)字节；  
&emsp;（2）A的第8列和第5行共占(<font color=red>  A  </font>)字节。  错误选择B  
> 第8列有9个元素，第5行有10个元素，但第8列和第5行重复计算了一个元素！！！！

&emsp;供选择的答案：  
&emsp;（1）  
&emsp;&emsp; A.90  
&emsp;&emsp; B.180  
&emsp;&emsp; C.270  
&emsp;&emsp; D.540  
&emsp;（2）  
&emsp;&emsp; A.108  
&emsp;&emsp; B.114  
&emsp;&emsp; C.54  
&emsp;&emsp; D.60  
24．多维数组之所以有行优先顺序和列优先顺序两种存储方式是因为(<font color=green>  D  </font>)。  
&emsp;A．数组的元素处在行和列两个关系中  
&emsp;B．数组的元素必须从左到右顺序排列  
&emsp;C．数组的元素之间存在次序关系  
&emsp;D．数组是多维结构，内存是一维结构  
25．对特殊矩阵采用压缩存储的主要目的是(<font color=green>  D  </font>)。  
&emsp;A．表达变得简单  
&emsp;B．对矩阵元素的存取变得简单  
&emsp;C．去掉矩阵中多余的元素  
&emsp;D．减少不必要的存储空间  
26．对n阶对称矩阵压缩存储时，需要表长为(<font color=green>  C  </font>)的顺序表。  
&emsp;A．n/2  
&emsp;B．n2/2  
&emsp;C．n(n+1)/2  
&emsp;D．n(n-1)/2  
27．设有一个n*n的对称矩阵A，将其下三角部分按行存放在一维数组B中，而A[0][0]存放于B[0]中，那么，第i行对角线元素A[i][i]存放于B中(<font color=red>  A  </font>)处。  错误选择B  
> 矩阵行列号从0开始  
> 有(1 + i + 1) * (i + 1) / 2 - 1  
> 化简后即为A

&emsp;A．(i+3)i/2  
&emsp;B．(i+1)i/2  
&emsp;C．(2n-i+1)i/2  
&emsp;D．(2n-i-1)i/2  
28．下列说法正确的是(<font color=green>  B  </font>)。  
&emsp;（1）稀疏矩阵压缩存储后，必会失去随机存取功能。  
&emsp;（2）若一个广义表的表头为空表，则此广义表亦为空表。  
&emsp;（3）广义表的取表尾运算，其结果通常是个表，但有时也可是个单元素值。  
&emsp;（4）从逻辑结构上看，n维数组是由多个n-1维的数组构成。  
&emsp;A．仅（1）（2）  
&emsp;B．仅（1）（4）  
&emsp;C．仅（2）（3）  
&emsp;D．仅（3）（4）  
29．下面说法不正确的是(<font color=green>  A  </font>)。  
&emsp;A．广义表的表头总是一个广义表  
&emsp;B．广义表的表尾总是一个广义表  
&emsp;C．广义表难以用顺序存储结构  
&emsp;D．广义表可以是一个多层次的结构  
30．广义表L=(a,(b,c))，进行Tail(L)操作后的结果为(<font color=green>  D  </font>)。  
&emsp;A．c  
&emsp;B．b,c  
&emsp;C．(b,c)  
&emsp;D．((b,c))