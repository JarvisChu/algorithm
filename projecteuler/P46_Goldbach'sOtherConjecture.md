# Problem 46: Goldbach's other conjecture

> https://projecteuler.net/problem=46

It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

- 9 = 7 + 2×1<sup>2</sup>
- 15 = 7 + 2×2<sup>2</sup>
- 21 = 3 + 2×3<sup>2</sup>
- 25 = 7 + 2×3<sup>2</sup>
- 27 = 19 + 2×2<sup>2</sup>
- 33 = 31 + 2×1<sup>2</sup>

It turns out that the conjecture was false.

What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?

## 分析

哥德巴赫的另一个猜想：一个既是奇数又是合数的数，可以写成一个质数以及一个平方数的2倍的和，即 c = prime + 2*n²，这个猜想被证明是错误的，那么最小的一个不满足该猜想的数是多少？


## 方法，直接遍历统计

c 从 9 开始往上遍历，c+=2 保证每次判断的都是奇数。 对于每一个c，先判断其是不是质数，是质数则跳过。不是质数，则继续，遍历 n 判断 c - 2*n² 是不是质数，如果是质数，则 c 满足猜想，继续判断下一个c。 如果对于所有的n，都不满足，则结束，输出c。


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
    // c = prime + 2*n²
    for(int c = 9; ; c +=2 ){
        
        // c is odd, composite nubmer
        if(isPrime(c)) continue;
        
        bool satisfy = false;
        for(int n = 1; ;n++){
            // prime = c - 2*n²
            int prime = c - 2*n*n;
            if(prime <= 0) break;
            if(isPrime(prime)) {
                satisfy = true;
                break;
            }
        }

        if(!satisfy){
            printf("%d\n", c);
            break;
        }
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

	if n%6 != 1 && n%6 != 5 {
		return false
	}

	for i := 5; i*i <= n; i++ {
		if n%i == 0 {
			return false
		}
	}

	return true
}

func main() {

	// c = prime + 2*n²
	for c := 9; ; c += 2 {

		// c is odd, composite nubmer
		if isPrime(c) {
			continue
		}

		satisfy := false
		for n := 1; ; n++ {
			// prime = c - 2*n²
			prime := c - 2*n*n
			if prime <= 0 {
				break
			}

			if isPrime(prime) {
				satisfy = true
				break
			}
		}

		if !satisfy {
			fmt.Println(c)
			break
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
    if n % 6 != 1 and n % 6 != 5 : return False
    for i in range(5, int(math.sqrt(n)) + 1):
        if n % i == 0 : return False

    return True

# c = prime + 2*n²
c = 9
while True:
    # c is odd, composite nubmer
    if isPrime(c) :
        c += 2
        continue
    satisfy = False
    n = 1
    while True:
        # prime = c - 2*n²
        prime = c - 2*n*n
        if prime <= 0 :
            break

        if isPrime(prime) :
            satisfy = True
            break
        n = n + 1

    if not satisfy :
        print(c)
        break

    c += 2
```


## 答案

5777