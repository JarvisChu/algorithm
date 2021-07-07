# Problem 30: Digit fifth powers

> https://projecteuler.net/problem=30

Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

- 1634 = 1<sup>4</sup> + 6<sup>4</sup> + 3<sup>4</sup> + 4<sup>4</sup>
- 8208 = 8<sup>4</sup> + 2<sup>4</sup> + 0<sup>4</sup> + 8<sup>4</sup>
- 9474 = 9<sup>4</sup> + 4<sup>4</sup> + 7<sup>4</sup> + 4<sup>4</sup>

As 1 = 1<sup>4</sup> is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.

## 分析

一个数等于它所有位上的数字的5次方之和，找出满足这个条件的所有数的和。

肯定是需要遍历，但首先需要通过分析给出遍历的上界。

如果是一个6位数，各位数字5次方之和最大为 6 * 9<sup>5</sup> = 354294，是一个6位数，所以6位数是有可能满足的。

如果是一个7位数，各位数字5次方之和最大为 7 * 9<sup>5</sup> = 413343，是一个6位数，不可能等于7位数自身，所以7位数是有可能满足的。

这就得到了一个上界。1位数（1~9，1排除了）也是不可能的，那么就可以从10~999999遍历。

## 方法 遍历10~999999统计

### CPP

```cpp
#include <stdio.h>

// 统计n的每个位的5次方之和
int sumOfDigits(int n)
{
    int sum = 0;
    while(n > 0) {
        int d = n%10;
        sum += d*d*d*d*d; // pow(d,5)
        n = n/10;
    }

    return sum;
}

int main()
{
    int sum = 0;
    for (int i = 10; i < 999999;i ++){
        if (sumOfDigits(i) == i){
            sum += i;
        }
    }
    printf("%d\n",sum);
    return 0;
}
```

### Golang

```go
package main

import "fmt"

// 统计n的每个位的5次方之和
func sumOfDigits(n int) int {
	sum := 0
	for n > 0 {
		d := n % 10
		sum += d * d * d * d * d // pow(d,5)
		n = n / 10
	}

	return sum
}

func main() {
	sum := 0
	for i := 10; i < 999999; i++ {
		if sumOfDigits(i) == i {
			sum += i
		}
	}
	fmt.Println(sum)
}

```

### Python

一行代码。 遍历10~999999，对每个数都计算各位5次方之和，如果相等，放入列表中，使用sum对列表求和。

```python
print( sum([i for i in range(10, 999999) if sum([int(ch) ** 5 for ch in str(i)]) == i]) )
```

i从10~999999遍历，对每个i，先转换为string类型，str(i)，然后遍历str(i) 的每一位字符并转换为数字，再做5次方，成为列表一项，使用sum([int(ch) ** 5 for ch in str(i)]) 即可得到各位数字5次方之和，如果和i相等，则满足条件，放到外层的一个列表中，最后使用sum()函数统计满足条件的所有数之和。

## 答案
443839