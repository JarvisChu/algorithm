# Problem 10: Summation of primes

> https://projecteuler.net/problem=10

The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.

## 分析
2百万以内的所有质数的和。

这题考察的重点应该是大数的存储，因为2百万以内所有质数的和是个非常大的数，超过了int型能表示的范围。如果是C\C++就需要使用更大的数据类型，当然Python就不用考虑这些了。至于判断质数的方法，和 [Problem 7](http://zhujiangtao.com/problem-7-10001st-prime/) 是相同的，使用了一种高效的算法。

## 方法 遍历穷举法

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
    if(n % 6 != 1 && n % 6 != 5 ) return false;
    for(int i=5; i * i <= n; i+=6){
        if( n % i == 0  || n % (i+2) == 0) return false;
    }
    return true;
}

int main()
{
    int64_t sum = 5; // 2 + 3
    for(int64_t i = 1; 6*i <= 2000000; i ++){ // start from 5
        
        if(isPrime(i * 6 - 1)) {
            sum += i * 6 - 1;
        }

        if(isPrime(i * 6 + 1)) {
           sum += i * 6 + 1;
        }
    }

    printf("sum:%lld\n", sum);
    
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

	if n % 6 != 1 && n % 6 != 5 {
		return false
	}

	// 从 [5, sqrt(n)] 遍历寻找是否是其因数
	for i:=int64(5); i * i <= n; i+=6 {
		if n % i == 0 || n % (i+2) == 0 {
			return false
		}
	}

	return true
}

func main(){
	sum := int64(5) // 2 + 3
	for i := int64(1); 6*i <= 2000000; i ++ { // start from 5

		if isPrime(i * 6 - 1) {
			sum += i * 6 - 1
		}

		if isPrime(i * 6 + 1) {
			sum += i * 6 + 1
		}
	}

    fmt.Println(sum)
}
```

### Python

```python
import math

def isPrime(n): 
    if n <= 1 : return False
    if n == 2 or n == 3 : return True
    if n % 2 == 0 : return False
    if n % 6 != 1 and n % 6 != 5 : return False
    for i in range(5, int(math.sqrt(n)) + 1):
        if n % i == 0 : return False
    return True

i, sum = 1, 5
while i * 6 <= 2000000:
    if isPrime(i * 6 - 1) :
        sum = sum + i * 6 - 1
    if isPrime(i * 6 + 1) :
        sum = sum + i * 6 + 1
    i = i + 1

print(sum)
```

## 答案
142913828922