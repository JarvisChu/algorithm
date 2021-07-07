# Problem 34: Digit factorials

> https://projecteuler.net/problem=34

145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of their digits.

Note: As 1! = 1 and 2! = 2 are not sums they are not included.

## 分析

一个数等于它各位数字阶乘的和。求所有这样的数的和。

每增加一位数字，阶乘最多增加9！= 362,880。对于一个满足条件的数：

- 如果它是6位数，阶乘之和最大为 6*9！ = 2177280 > 最大的6位数999,999，所以可能
- 如果它是7位数，阶乘之和最大为 7*9！ = 2540160 < 最小的7位数1,000,000，所以不可能

所以满足条件的数，最多是个6位数

## 方法 穷举遍历

有了上面的分析，就可以穷举遍历了。对与每个i = 3~999,999，计算其各位数字阶乘之和，如果等于i，则满足条件，进行累加。

### CPP

```cpp
#include <iostream>
#include <vector>

int main()
{
    // 保存所有数字的阶乘，用于查表。
    int A[10]; // A[n] 表示 n!；
    A[0] = 1;
    for(int i = 1; i < 10; i++){
        A[i] = A[i-1] * i;
    }

    int sum = 0; // 存储所有满足条件的数的和

    // 遍历 3 ~ 999,999，判断是否满足条件
    for(int i = 3; i <= 999999; i++){
        int sumOfI = 0;

        // 获取i的每一位数字的阶乘
        int n = i;
        while(n > 0){
            sumOfI += A[n % 10];
            n /= 10;
        }

        if(sumOfI == i) {
            std::cout << i << std::endl;
            sum += i;
        }
    }
    
    std::cout << "answer is: " << sum << std::endl;
    return 0;
}
```

### Golang

```go
package main

import "fmt"

func main() {

	// 保存所有数字的阶乘，用于查表。
	A := [10]int{} // A[n] 表示 n!；
	A[0] = 1
	for i := 1; i < 10; i++ {
		A[i] = A[i-1] * i
	}

	sum := 0 // 存储所有满足条件的数的和

	// 遍历 3 ~ 999,999，判断是否满足条件
	for i := 3; i <= 999999; i++ {
		sumOfI := 0

		// 获取i的每一位数字的阶乘
		n := i
		for n > 0 {
			sumOfI += A[n%10]
			n /= 10
		}

		if sumOfI == i {
			fmt.Println(i)
			sum += i
		}
	}

	fmt.Printf("answer is: %v", sum)
}
```

### Python

```python

# 保存所有数字的阶乘，用于查表。
A = [] # A[n] 表示 n!；
A.append(1) # A[0] = 1
for i in range(1,10) :
    A.append(A[i-1] * i)

result = []
for n in range(3,999999):
    sm = sum([A[int(i)] for i in str(n)])
    if sm == n:
        result.append(n)
print(result)
print(sum(result))
```

## 答案
40730

两个符合条件的数为 145, 40585