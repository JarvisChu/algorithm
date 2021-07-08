# Problem 37: Truncatable primes

> https://projecteuler.net/problem=37

The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.

## 分析

可截断的质数。一个质数，从左向右截断和从右向左截断的结果也是质数，则称这个数是可截断的质数。如3797，从左向右截断结果3797, 797, 97, 7 都是质数，从右向左结果3797, 379, 37, 3 也都是质数。
仅仅有11个数满足这个特性，找到这个11个数的和。

问题的核心是从左向右截断和从右向左截断的实现。有两种方法:

 (1) 将数字转换为字符串：s = str(n), 从左向右截断 s = s[1:]，从右向左截断 s = s[:-1]
 
 (2) 通过数字运算，如：3797，从左向右截断，3797 / 10 = 379， 379 / 10 = 79， 79/10 = 9； 从右向左截断，3797%1000 = 797；3797%100 = 97；97%10 = 7；核心代码如下：

 ```cpp
// 判断 n 是否满足条件，即从左往右和从右往左截断，都是质数
bool isTruncatable(int n)
{
    if(!isPrime(n)) return false;

    // 从左向右截断 3797, 3797%1000=797, 3797%100=97, 3797%10=7
    int mod = 10;
    while(true){
        int v = n % mod; // v: 7, 97, 797
        if (v == n) break;
        mod *= 10;
        if(!isPrime(v)) return false;
    }

    // 从右向左截断 3797, 3797/10=379, 379/10=79, 79/10=9
    int cpy = n;
    while(cpy > 0){
        cpy /= 10;
        if(cpy > 0 && !isPrime(cpy)) return false;
    }

    return true;
}
```
 
## 方法 遍历处理

 通过上面分析中的方法，从10 开始往上遍历，找到11个满足条件的数则截止。统计该11个数的和。

### CPP

3797, 3797%10=7, 3797%100=97, 3797%1000=797

```cpp
#include <stdio.h>

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

// 判断 n 是否满足条件，即从左往右和从右往左截断，都是质数
bool isTruncatable(int n)
{
    if(!isPrime(n)) return false;

    // 从左向右截断 3797, 3797%1000=797, 3797%100=97, 3797%10=7
    int mod = 10;
    while(true){
        int v = n % mod; // v: 7, 97, 797
        if (v == n) break;
        mod *= 10;
        if(!isPrime(v)) return false;
    }

    // 从右向左截断 3797, 3797/10=379, 379/10=79, 79/10=9
    int cpy = n;
    while(cpy > 0){
        cpy /= 10;
        if(cpy > 0 && !isPrime(cpy)) return false;
    }

    return true;
}

int main()
{
    int cnt = 0;
    int sum = 0;
    for(int64_t i = 10; ; i++){
        if(isTruncatable(i)){
            printf("%d\n", i);
            sum += i;
            cnt++;
        }

        if(cnt == 11) break;
    }

    printf("sum=%d\n", sum);
    return 0;
}
```

3797, 3797%1000=797, 3797%100=97, 3797%10=7

```cpp
// 判断 n 是否满足条件，即从左往右和从右往左截断，都是质数
bool isTruncatable(int n)
{
    if(!isPrime(n)) return false;

    // 从左向右截断 3797, 3797%1000=797, 3797%100=97, 3797%10=7
    int cpy = n;
    int mod = 1;    // n=3797: mod=1000, n=123456: mod=100000
    while(cpy > 0){
        cpy /= 10;
        mod *= 10;
    }

    cpy = n;
    while(cpy > 0){
        cpy = cpy % mod; // v: 3797%1000 = 797, 3797%100 = 97, 97%10 = 7
        mod /= 10;
        if(cpy > 0 && !isPrime(cpy)) return false;
    }

    // 从右向左截断 3797, 3797/10=379, 379/10=79, 79/10=9
    cpy = n;
    while(cpy > 0){
        cpy /= 10;
        if(cpy > 0 && !isPrime(cpy)) return false;
    }

    return true;
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

// 判断 n 是否满足条件，即从左往右和从右往左截断，都是质数
func isTruncatable(n int) bool {
	if !isPrime(n) {
		return false
	}

	// 从左向右截断 3797, 797, 97, 7
	mod := 10
	for {
		v := n % mod // v: 7, 97, 797
		if v == n {
			break
		}
		mod *= 10
		if !isPrime(v) {
			return false
		}
	}

	// 从右向左截断 3797, 3797/10=379, 379/10=79, 79/10=9
	cpy := n
	for cpy > 0 {
		cpy /= 10
		if cpy > 0 && !isPrime(cpy) {
			return false
		}
	}

	return true
}

func main() {
	cnt, sum := 0, 0
	for i := 10; ; i++ {
		if isTruncatable(i) {
			fmt.Println(i)
			sum += i
			cnt++
		}

		if cnt == 11 {
			break
		}
	}

	fmt.Println(sum)

}
```

### Python

直接使用str的处理

```python

import math

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
    for i in range(5, int(math.sqrt(n)) + 1):
        if n % i == 0 : return False

    return True

# 判断 n 是否满足条件，即从左往右和从右往左截断，都是质数
def isTruncatable(n) :
    if not isPrime(n) :
        return False

    # 从左向右截断 3797, 797, 97, 7
    # 从右向左截断 3797, 379, 79, 9
    sz = len(str(n))
    for i in range(1, sz):
        l2r = str(n)[i:]  # left 2 right
        r2l = str(n)[:-i] # right 2 left

        if (not isPrime(int(l2r))) or (not isPrime(int(r2l))):
            return False
    return True

i, cnt, sum = 10, 0, 0
while True:
    if isTruncatable(i):
        print(i)
        sum += i
        cnt = cnt + 1
    if cnt == 11 :
        break
    i = i + 1

print(sum)

```

## 答案

748317

这11个数为：23, 37, 53, 73, 313, 317, 373, 797, 3137, 3797, 739397