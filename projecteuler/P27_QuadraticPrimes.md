# [Problem 27: Quadratic primes](https://projecteuler.net/problem=27)

Euler discovered the remarkable quadratic formula:

**n² + n + 41**

It turns out that the formula will produce 40 primes for the consecutive integer values 0 <= n <= 39. However, when n = 40, 40² + 40 + 41 = 40(40+1) + 41 is divisible by 41, and certainly when n = 41, 41² + 41 + 41 is clearly divisible by 41.

The incredible formula **n² - 79n + 1601** was discovered, which produces 80 primes for the consecutive values 0 <= n <= 79. The product of the coefficients, −79 and 1601, is −126479.

Considering quadratics of the form:

n² + an + b, where |a| < 1000 and  |b| <= 1000

where |n| is the modulus/absolute value of n
e.g. |11| = 11 and |-4| = 4

Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive values of n, starting with n = 0.


## 分析

二次质数。欧拉发现了著名的二次方程：n² + n + 41。当n=0~39时，这个方程能够连续产生40个质数。但是，当n=40时，402 + 40 + 41 = 40(40 + 1) + 41可以被41整除，当然，还有当n = 41, 41² + 41 + 41 可以被41整除。

发现了更奇妙的方程： n² - 79n + 1601，当n=1~79时，它能够连续产生80个质数。方程系数的积为 –79 * 1601 = -126479.

考虑二次方程的形式：

n² + an + b,   |a| < 1000 且 |b| <= 1000

|n| 是n 的绝对值。

找到系数a和b，当n从0开始连续递增时，可以产生最多的质数。 给出a*b的值。

## 方法1 穷举法

穷举遍历。a=-1000~1000，b=-1000~1000，对每组a,b, 从n=0开始往上递增，判断f = n*n+a*n+b是否是质数，如果是，则n++,cnt++,如果不是则结束，此时a,b能产生的最多质数就是cnt个。

### CPP

```cpp
#include <stdio.h>

/************************************************************************
* 判断n是否是质数
************************************************************************/
bool isPrime(int n)
{
    if(n <= 1 ) return false;
    if(n == 2 || n == 3) return true;
    if(n % 2 == 0) return false;

    // 关于质数分布的规律：大于等于5的质数一定和6的倍数相邻
    // 即大于等于5的质数一定是 6x-1 和 6x+1，6x+2 ~ 6x+4 一定不是质数
    // 即大于等于5的质数一定满足 n%6==1 or n%6==5
    // https://blog.csdn.net/songyunli1111/article/details/78690447
    if(n % 6 != 1 && n % 6 != 5 ) return false;

    // 从 [5, sqrt(n)] 遍历寻找是否是其因数
    for(int i=5; i * i <= n; i++){
        if( n % i == 0 ) return false;
    }
    return true;
}

/************************************************************************
* 返回 n*n + a*n + b，n 从 0 开始，能连续产生的质数的个数
************************************************************************/
int f(int a, int b)
{
    int cnt = 0;
    for (int i=0;;i++){
        if ( isPrime(i*i+a*i+b) ) {
            cnt ++;
        }else break;
    }
    return cnt;
}

int main()
{
    int max_a,max_b,max_primes=0;

    for (int a = -1000; a < 1000; a++){
        for(int b = -1000; b < 1000; b++){
            if( f(a,b) > max_primes){
                max_a = a;
                max_b = b;
                max_primes = f(a,b);
            }
        }
    }

    printf("a=%d, b=%d, a*b=%d, 连续质数个数为：%d\n", max_a, max_b, max_a * max_b, max_primes);

    return 0;
}
```

### Golang

```go
package main

import "fmt"

func isPrime(n int64) bool {
	if n <= 1 {
		return false
	}

	if n == 2 || n == 3 {
		return true
	}

	if n%2 == 0 {
		return false
	}

	// 关于质数分布的规律：大于等于5的质数一定和6的倍数相邻
	// 即大于等于5的质数一定是 6x-1 和 6x+1，6x+2 ~ 6x+4 一定不是质数
	// 即大于等于5的质数一定满足 n%6==1 or n%6==5
	// https://blog.csdn.net/songyunli1111/article/details/78690447
	if n%6 != 1 && n%6 != 5 {
		return false
	}

	// 从 [5, sqrt(n)] 遍历寻找是否是其因数
	for i := int64(5); i*i <= n; i++ {
		if n%i == 0 {
			return false
		}
	}

	return true
}

/************************************************************************
* 返回 n*n + a*n + b，n 从 0 开始，能连续产生的质数的个数
************************************************************************/
func f(a, b int) int {
	cnt := 0
	for i := 0; ; i++ {
		if isPrime(int64(i*i + a*i + b)) {
			cnt++
		} else {
			break
		}
	}
	return cnt
}

func main() {

	maxA, maxB, maxPrimes := 0, 0, 0

	for a := -1000; a < 1000; a++ {
		for b := -1000; b < 1000; b++ {
			if f(a, b) > maxPrimes {
				maxA = a
				maxB = b
				maxPrimes = f(a, b)
			}
		}
	}

	fmt.Printf("a=%d, b=%d, a*b=%d, 连续质数个数为：%d\n", maxA, maxB, maxA*maxB, maxPrimes)
}

```

### Python

```python
from math import sqrt

def isPrime(n): 
    if n <= 1 : return False
    if n == 2 or n == 3 : return True
    if n % 2 == 0 : return False

    # 关于质数分布的规律：大于等于5的质数一定和6的倍数相邻
    # 即大于等于5的质数一定是 6x-1 和 6x+1，6x+2 ~ 6x+4 一定不是质数
    # 即大于等于5的质数一定满足 n%6==1 or n%6==5
    # https://blog.csdn.net/songyunli1111/article/details/78690447
    if n % 6 != 1 and n % 6 != 5 : return False

    # 从 [5, sqrt(n)] 遍历寻找是否是其因数
    for i in range(5, int(sqrt(n)) + 1):
        if n % i == 0 : return False

    return True

def f(a,b):
    '''return the count of consecutive primes n*n + a*n + b can produce'''

    i, cnt = 0, 0
    while True:
        if isPrime(i*i+a*i+b):
            cnt += 1
            i += 1
        else:
            break
    return cnt

#just one line
#print max((f(a,b),a,b,a*b) for a in range(-1000,1000) for b in range(-1000,1000)) #(71, -61, 971, -59231)

#or several lines in detail
max_a, max_b, max_primes, max_product = 0, 0, 0, 0
for a in range(-1000,1000):
    for b in range(-1000,1000):
        if f(a,b) > max_primes:
            max_a, max_b, max_product, max_primes = a, b, a * b, f(a,b)
print(max_a, max_b, max_product, max_primes)
```

## 方法2 不编程，纯数学计算

> 来自论坛第一页用户 hk 的答案

hk的原答案如下：

```
I did not use a computer to solve this problem.
The formula n^2-79n+1601 is nothing more than (n-40)^2+n-40+41 
so that all the forty primes of n^2+n+41 are met twice that's why 80 primes are found, but only 40 different ones.
So what I did was:
take (n-p)^2+n-p+41, working out this formula gives:
n^2-(2p-1)n+p^2-p+41.
Now |2p-1|<1000 and |p^2-p+41|<1000.
The second condition gives -30<=p<=31
The value p=31 gives the most primes.
So the numbers are -(2*31-1)=-61 and 31^2-31+41=971.
See also: http://mathworld.wolfram.com/Prime-GeneratingPolynomial.html 
``` 

## 答案
-59231