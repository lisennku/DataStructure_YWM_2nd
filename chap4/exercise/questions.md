1. 已知模式串t=“abcaabbabcab”写出用KMP法求得的每个字符对应的next和nextval函数值。    
- next
  - 令next[1] = 0， next[2] = 1
  - 从第三位，记为j，开始，使用j-1位置的字符和k=next[j-1]位置的字符比较，如果相等，则next[j] = next[j-1]+1，
  - 否则，k=next[k]，继续刚才的步骤，直到k为0，此时next[j] = 1
  - j=3    此时t[2] = b, t[next[2]] = a，不等，则k=next[next[2]] = 0，此时next[3] = 1；
  - j=4    此时t[3] = c, t[next[3]] = a，不等，则k=next[next[3]] = 0，此时next[4] = 1;
  - j=5    此时t[4] = a, t[next[4]] = a，相等，则next[5] = next[4] + 1 = 2;
  - j=6    此时t[5] = a, t[next[5]] = b，不相等，则k=next[next[5]] = 1，t[1] = a，相等，则next[6] = next[1] + 1 = 2;
  - j=7    此时t[6] = b, t[next[6]] = b，相等，则next[7] = next[6] + 1 = 3;
  - j=8    此时t[7] = b, t[next[7]] = c，不相等，则k=next[next[7]]= 1，t[1] = a，不相等，则k=next[1] =0，则next[8] = 1;
  - j=9    此时t[8] = a, t[next[8]] = a，相等，则next[9] = next[8]+1 = 2;
  - j=10   此时t[9] = b, t[next[9]] = b，相等，则next[10] = next[9]+1 = 3;
  - j=11   此时t[10] = c, t[next[10]] = c，相等，则next[11] = next[10] + 1 = 4;
  - j=12   此时t[11] = a, t[next[11]] = a，相等，则next[12] = next[11] + 1 = 5;
 
- nextval
  - nextval的计算需要根据next的值进行计算。
  - 第一位值为1，nextval[1]=0。
  - 从第二位开始，若要求第i位的nextval[i]，将next[i]的值对应的位的值与i的值进行比较
  - （例如，当i=3时，next[3]=1对应的位数下的字符为‘a’，第i位的值为‘a’）
    - 若当前字符的值与当前字符下next值所对应位数的值不同，则当前字符的nextval值为当前字符对应的next值
- 若当前字符的值与当前字符下next值所对应位数的值相同，则当前字符的nextval值为当前字符对应next值的nextval值    

| position | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
|----------|---|---|---|---|---|---|---|---|---|----|----|----|
| pattern  | a | b | c | a | a | b | b | a | b | c  | a  | b  |
| next     | 0 | 1 | 1 | 1 | 2 | 2 | 3 | 1 | 2 | 3  | 4  | 5  |
| nextval  | 0 | 1 | 1 | 0 | 2 | 1 | 3 | 0 | 1 | 1  | 0  | 5  |

2. 2．设目标为t=“abcaabbabcabaacbacba”，模式为p=“abcabaa”。    
&emsp;（1）计算模式p的naxtval函数值；   

| position | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------|---|---|---|---|---|---|---|
| pattern  | a | b | c | a | b | a | a |
| next     | 0 | 1 | 1 | 1 | 2 | 3 | 2 |
| nextval  | 0 | 1 | 1 | 0 | 1 | 3 | 2 |

&emsp;（2）画出利用KMP算法进行模式匹配时每一趟的匹配过程。   
&emsp;&emsp;第一趟：  
&emsp;&emsp;abcaabbabcabaacbacba  
&emsp;&emsp;abcab i = 5, j = 5  
&emsp;&emsp;第二趟：  
&emsp;&emsp;abcaabbabcabaacbacba  
&emsp;&emsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;abc i = 7, j = 3  
&emsp;&emsp;第三趟：  
&emsp;&emsp;abcaabbabcabaacbacba  
&emsp;&emsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;a i = 7, j = 1  
&emsp;&emsp;第四趟：  
&emsp;&emsp;abcaabbabcabaacbacba  
&emsp;&emsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; abcabaa


3. 数组A中，每个元素A[i,j]的长度均为32个二进位，行下标从-1到9，列下标从1到11，从首地址S开始连续存放主存储器中，主存储器字长为16位。求：  
&emsp;（1）存放该数组所需多少单元？  242  
&emsp;（2）存放数组第4列所有元素至少需多少单元？  22  
&emsp;（3）数组按行存放时，元素A[7,4]的起始地址是多少？  S+182  
&emsp;（4）数组按列存放时，元素A[4,7]的起始地址是多少？  S+142

4. 请将香蕉banana用工具H( )—Head( )，T( )—Tail( )从L中取出。
&emsp;L=(apple, (orange, (strawberry, (banana)), peach), pear)。  
T(L) = ((orange, (strawberry, (banana)), peach), pear)  
H(T(L)) = (orange, (strawberry, (banana)), peach)  
T(H(T(L))) = ((strawberry, (banana)), peach)  
H(T(H(T(L)))) = (strawberry, (banana))  
T(H(T(H(T(L))))) = ((banana))  
H(T(H(T(H(T(L)))))) = (banana)  
H(H(T(H(T(H(T(L))))))) = banana  