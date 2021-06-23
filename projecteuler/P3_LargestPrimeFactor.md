# Problem 3: Largest prime factor

> https://projecteuler.net/problem=3

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?

## 分析
最大质因数问题。求600851475143的最大质因数。

## 方法1 暴力求解

从 N=600851475143, N=a*i，i从1开始，计算a，判断a是否为质数，是则返回结束

### CPP

C\C++ 中int类型（包括long int类型）的最大值为2147483647，所以600851475143不能使用int类型表示。可以使用int64_t类型来表示，包含在stdint.h头文件下，这是一个long long int，足以表示600851475143。


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
    int64_t number = 600851475143LL;

    // number = a * i.  when i increasing, a decreasing, if a is prime, stop
    for(int i = 1; i * i < number; i ++ ){
        if(number % i == 0 && isPrime( number/i ) ){ // find a factor, and the factor is prime
            printf("%lld\n", number / i);
            return 0;
        }
    }

    return 0;
}
```

可以关注下 isPrime() 的实现，是一种高效的判断质数的方法。

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
    
	var number int64 = 600851475143
	// number = a * i.  when i increasing, a decreasing, if a is prime, stop
    for i := int64(1); i <= number; i ++ {
        if number % i == 0 && isPrime( number/i ) { // find a factor, and the factor is prime
			fmt.Println(number / i)
            return
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

number = 600851475143
# number = a * i.  when i increasing, a decreasing, if a is prime, stop
for i in range(1, number):
    if number % i == 0 and isPrime( number/i ):  # find a factor, and the factor is prime
        print( int(number / i) )
        break

```


## 方法2

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    int64_t number = 600851475143LL;
    int64_t divisor = 2;
    
    while (number > 1) {
        if (0 == (number % divisor)) {
            number /= divisor;
            divisor--;
        }
        divisor++;
    }
    printf("%lld\n",divisor);

    return 0;
}
```

## 答案
6857

## 知识点
- 判断质数
- 最大质因数
- int64_t 类型