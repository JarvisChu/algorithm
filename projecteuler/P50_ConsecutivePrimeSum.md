# Problem 50: Consecutive prime sum

> https://projecteuler.net/problem=50

The prime 41, can be written as the sum of six consecutive primes:

41 = 2 + 3 + 5 + 7 + 11 + 13
This is the longest sum of consecutive primes that adds to a prime below one-hundred.

The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most consecutive primes?

## 分析

找到小于1000000的一个质数，它能被写成连续的质数的和，并且这个连续的质数最长

## 方法1 遍历累加

保存1000000以下的所有质数到 primes，然后遍历 primes 统计最长的连续质数和

### CPP

```cpp
#include <iostream>
#include <vector>

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
    // 获取小于1,000,000的所有质数
    std::vector<int> primes;
    primes.push_back(2);
    for(int i = 3; i < 1000000; i+=2 ){
        if(isPrime(i)){
            primes.push_back(i);
        }
    }

    int curMaxLength = 0;  // 当前的最大长度
    int curStartPrime = 0; // 当前的最大长度时，起始的质数
    int curMaxSum = 0;     // 当前的最大长度时，连续质数的和

    // 遍历寻找
    for(int i = 0; i < primes.size(); i++){
        int len = 1, primeSum = primes[i], sum = primes[i];

        for(int j = i+1; j < primes.size() ;j++){
            sum += primes[j];
            if(sum > 1000000) break;
            if(isPrime(sum)){
                len = j - i + 1;
                primeSum = sum;
            }
        }

        // 如果找到更长的链，记录
        if(len > curMaxLength){
            curMaxLength = len;
            curStartPrime = primes[i];
            curMaxSum = primeSum;

            printf("find a longer one, start at %d, length is %d, sum is %d\n", curStartPrime, curMaxLength, curMaxSum);
        }
    }

    return 0;
}
```

### Golang

```go
package main

import "fmt"

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

	// 获取小于1,000,000的所有质数
	primes := []int{2}
	for i := 3; i < 1000000; i += 2 {
		if isPrime(i) {
			primes = append(primes, i)
		}
	}

	curMaxLength := 0  // 当前的最大长度
	curStartPrime := 0 // 当前的最大长度时，起始的质数
	curMaxSum := 0     // 当前的最大长度时，连续质数的和

	// 遍历寻找
	for i := 0; i < len(primes); i++ {
		length, primeSum, sum := 1, primes[i], primes[i]

		for j := i + 1; j < len(primes); j++ {
			sum += primes[j]
			if sum > 1000000 {
				break
			}
			if isPrime(sum) {
				length = j - i + 1
				primeSum = sum
			}
		}

		// 如果找到更长的链，记录
		if length > curMaxLength {
			curMaxLength = length
			curStartPrime = primes[i]
			curMaxSum = primeSum

			fmt.Printf("find a longer one, start at %d, length is %d, sum is %d\n", curStartPrime, curMaxLength, curMaxSum)
		}
	}
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
    for i in range(5, int(math.sqrt(n)) + 1):
        if n % i == 0 : return False

    return True

# 获取小于1,000,000的所有质数
primes = [2]
for i in range(3, 1000000, 2) : 
    if isPrime(i) :
        primes.append(i)

curMaxLength = 0  # 当前的最大长度
curStartPrime = 0 # 当前的最大长度时，起始的质数
curMaxSum = 0     # 当前的最大长度时，连续质数的和

# 遍历寻找
for i in range(0, len(primes)) :
    length, primeSum, sum = 1, primes[i], primes[i]
    for j in range(i + 1, len(primes)) :
        sum += primes[j]
        if sum > 1000000 :
            break
        if isPrime(sum) :
            length = j - i + 1
            primeSum = sum

    # 如果找到更长的链，记录
    if length > curMaxLength :
        curMaxLength = length
        curStartPrime = primes[i]
        curMaxSum = primeSum
        print("find a longer one, start at", curStartPrime, "length is", curMaxLength, "sum is", curMaxSum)
```

## 答案

997651

```
find a longer one, start at 2, length is 536, sum is 958577
find a longer one, start at 5, length is 539, sum is 978037
find a longer one, start at 7, length is 543, sum is 997651
```