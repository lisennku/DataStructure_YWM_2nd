1. n个数依次入栈，可以通过数学公式计算出栈序列的种数  
> $h(n) = C(2n, n) / (n + 1)$

设函数$f(n)$为表示n个数的出栈序列的种数，假设第一个出栈的序数是k，则k将1-n的序列分成两个序列，其中一个是1-(k-1)，序列个数为k-1，另一个是(k+1) - n，序列个数是n-k  
则，$f(n)=f(k-1)*f(n-k)$  
又因为k为1-n的数，所以$f(n)=f(0)f(n) + f(1)f(n-1) ... f(n)f(0)$  
而该函数恰为卡特兰数的递推式