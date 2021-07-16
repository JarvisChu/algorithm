# Problem 58: Spiral primes

> https://projecteuler.net/problem=58

Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side length 7 is formed.

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/project_euler_58_1.png)

It is interesting to note that the odd squares lie along the bottom right diagonal, but what is more interesting is that 8 out of the 13 numbers lying along both diagonals are prime; that is, a ratio of 8/13 ≈ 62%.

If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be formed. If this process is continued, what is the side length of the square spiral for which the ratio of primes along both diagonals first falls below 10%?

## 分析
统计对角线上的所有数中质数的占比。 求当正方形的长度时多少时，质数的占比会小于10%

**思路**

由于是逆时针旋转的，对于每一层，只要知道其右上角的数字之后，这一层所有的数字就可以知道了。

以 **1** 为第1层，往外一圈一圈扩展，则：

- 第 2 层四个角的数字：3，5，7，9      差值为 2 = 2*2 - 2
- 第 3 层四个角的数字：13，17，21，25  差值为 4 = 2*3 - 2
- 第 4 层四个角的数字：31，37，43，49  差值为 6 = 2*4 - 2
- 第 n 层四个角的数字：x1,x2,x3,x4    差值为 2n - 2

假设：Edge(n) 表示第 n 层的边长，TR(n) (i.e. top-right) 表示第 n 层右上角的数字，同理有 TL(n), BL(n), BR(n)
则:

```
边长：Edge(n) = 2n-1
右上角数：TR(n)
左上角数：TL(n) = TR(n) + Edge(n) - 1 = TR(n)+2n-2
左下角数：BL(n) = TL(n) + Edge(n) - 1 = TR(n)+4n-4
右下角数：BR(n) = BL(n) + Edge(n) - 1 = TR(n)+6n-6

TR(n+1) = BR(n) + Edge(n+1) - 1 = TR(n)+6n-6+2n+1-1 = TR(n)+8n-6

即：TR(n) = TR(n-1)+8n-14
```

其中 TR(1) = 1, TR(2) = 3, TR(3) = 13, TR(4) = 31, ...

至此，我们可以知道每层的四个角的数，继而可以遍历判断质数。


## 方法 根据分析中的公式，遍历判断质数

### CPP

```cpp
#include <stdio.h>

bool isPrime(int n)
{
    if(n <= 1 ) return false;
    if(n == 2 || n == 3) return true;
    if(n % 2 == 0) return false;
    if(n % 6 != 1 && n % 6 != 5 ) return false;
    for(int i=5; i * i <= n; i++){
        if( n % i == 0 ) return false;
    }
    return true;
}

int main()
{
    int totalCnt = 1; // 第一层的 1
    int primeCnt = 0;
    int prevTR = 1; // TR(1)

    // 循环判断第 n 圈的四个数
    for(int n = 2; ; n++){
        int tr = prevTR + 8*n - 14; // TR(n) = TR(n-1) + 8n - 14
        totalCnt += 4;

        if(isPrime(tr)) primeCnt++;       // 右上角数：TR(n)
        if(isPrime(tr+2*n-2)) primeCnt++; // 左上角数：TL(n) = TR(n)+2n-2
        if(isPrime(tr+4*n-4)) primeCnt++; // 左下角数：BL(n) = TL(n) + Edge(n) - 1 = TR(n)+4n-4
        if(isPrime(tr+6*n-6)) primeCnt++; // 右下角数：BR(n) = BL(n) + Edge(n) - 1 = TR(n)+6n-6

        //printf("n=%d, %d,%d,%d,%d, [%d/%d]\n", n, tr, tr+2*n-2, tr+4*n-4, tr+6*n-6, primeCnt, totalCnt);

        if( (float)primeCnt / (float)totalCnt  < 0.1){
            printf("%d\n", 2*n-1);// Edge(n) = 2n-1
            break;
        }
        prevTR = tr;
    }

    return 0;
}
```

### Golang

```go
package main

import (
	"fmt"
)

func isPrime(n int) bool {
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
	for i := 5; i*i <= n; i++ {
		if n%i == 0 {
			return false
		}
	}

	return true
}

func main() {
	totalCnt := 1 // 第一层的 1
	primeCnt := 0
	prevTR := 1 // TR(1)

	// 循环判断第 n 圈的四个数
	for n := 2; ; n++ {
		tr := prevTR + 8*n - 14 // TR(n) = TR(n-1) + 8n - 14
		totalCnt += 4

		if isPrime(tr) { // 右上角数：TR(n)
			primeCnt++
		}
		if isPrime(tr + 2*n - 2) { // 左上角数：TL(n) = TR(n)+2n-2
			primeCnt++
		}
		if isPrime(tr + 4*n - 4) { // 左下角数：BL(n) = TL(n) + Edge(n) - 1 = TR(n)+4n-4
			primeCnt++
		}
		if isPrime(tr + 6*n - 6) { // 右下角数：BR(n) = BL(n) + Edge(n) - 1 = TR(n)+6n-6
			primeCnt++
		}

		if float32(primeCnt)/float32(totalCnt) < 0.1 {
			fmt.Println(2*n - 1) // Edge(n) = 2n-1
			break
		}
		prevTR = tr
	}
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


totalCnt = 1 # 第一层的 1
primeCnt = 0
prevTR = 1  # TR(1)

# 循环判断第 n 圈的四个数
n = 2
while True:
    tr = prevTR + 8*n - 14 # TR(n) = TR(n-1) + 8n - 14
    totalCnt += 4

    if isPrime(tr) : # 右上角数：TR(n)
        primeCnt += 1

    if isPrime(tr + 2*n - 2) : # 左上角数：TL(n) = TR(n)+2n-2
        primeCnt += 1

    if isPrime(tr + 4*n - 4) : # 左下角数：BL(n) = TL(n) + Edge(n) - 1 = TR(n)+4n-4
        primeCnt += 1

    if isPrime(tr + 6*n - 6) : # 右下角数：BR(n) = BL(n) + Edge(n) - 1 = TR(n)+6n-6
        primeCnt += 1

    if primeCnt/totalCnt < 0.1 :
        print(2*n - 1) # Edge(n) = 2n-1
        break

    prevTR = tr
    n += 1
```

## 答案

26241