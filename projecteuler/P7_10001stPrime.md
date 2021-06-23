# Problem 7: 10001st prime

> https://projecteuler.net/problem=7

By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10 001st prime number?

## 分析
第10001个质数.

## 方法1 递增遍历寻找质数

在 [Problem 3 Largest Prime Factor](./P3_LargestPrimeFactor.md) 题目中，我们有提到过一个质数分布的规律：


> 关于质数分布的规律：大于等于5的质数一定和6的倍数相邻
> 即大于等于5的质数一定是 6x-1 和 6x+1，6x+2 ~ 6x+4 一定不是质数
> 即大于等于5的质数一定满足 n%6==1 or n%6==5
> https://blog.csdn.net/songyunli1111/article/details/78690447

所以，我们递增遍历时，不必遍历所有的数，**只需遍历 6 的倍数相邻的数**，判断是否是质数即可。

另外，关于质数判断的函数 isPrime 也可以直接从 Problem 3 中复制过来使用

### CPP

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

int main()
{
    int cnt = 2; // 2,3
    for(int64_t i = 1; ; i ++){ // start from 5
        
        if(isPrime(i * 6 - 1)) {
            cnt ++;
            if(cnt == 10001) {
                printf("10001st prime is: %lld\n", i * 6 - 1);
                return 0;
            }
        }

        if(isPrime(i * 6 + 1)) {
            cnt ++;
            if(cnt == 10001) {
                printf("10001st prime is: %lld\n", i * 6 + 1);
                return 0;
            }
        }
    }
    
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

	if n % 2 == 0 {
		return false
	}

	// 关于质数分布的规律：大于等于5的质数一定和6的倍数相邻
	// 即大于等于5的质数一定是 6x-1 和 6x+1，6x+2 ~ 6x+4 一定不是质数
	// 即大于等于5的质数一定满足 n%6==1 or n%6==5
	// https://blog.csdn.net/songyunli1111/article/details/78690447
	if n % 6 != 1 && n % 6 != 5 {
		return false
	}

	// 从 [5, sqrt(n)] 遍历寻找是否是其因数
	for i:=int64(5); i * i <= n; i++ {
		if n % i == 0 {
			return false
		}
	}

	return true
}

func main(){
	cnt := 2 // 2,3
	for i := int64(1); ; i ++ { // start from 5

		if isPrime(i * 6 - 1) {
			cnt ++
			if cnt == 10001 {
				fmt.Printf("10001st prime is: %v\n", i * 6 - 1)
				return
			}
		}

		if isPrime(i * 6 + 1) {
			cnt ++
			if cnt == 10001 {
				fmt.Printf("10001st prime is: %v\n", i * 6 + 1)
				return
			}
		}
	}
	
	return
}
```

### Python

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
    for i in range(5, int(math.sqrt(n))):
        if n % i == 0 : return False

    return True

cnt = 2 # 2,3
i = 1
while True:
    if isPrime(i * 6 - 1) :
        cnt = cnt + 1
        if cnt == 10001 :
            print("10001st prime is: ", i * 6 - 1)
            exit(0)
        
    if isPrime(i * 6 + 1) :
        cnt = cnt + 1
        if cnt == 10001 :
            print("10001st prime is: ", i * 6 + 1)
            exit(0)
    i = i + 1

```

## 方法2 查表

> 来自论坛中 bitRAKE 的方法

论坛第一个帖子中 bitRAKE 提出了 [Prime Pages](https://primes.utm.edu/lists/small/)，从这个页面进去，可以直接找到第10001个质数。

## 答案
104743

## 知识点
高效的判断素数