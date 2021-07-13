# Problem 48: Self powers

> https://projecteuler.net/problem=48

The series, 1<sup>1</sup> + 2<sup>2</sup> + 3<sup>3</sup> + ... + 10<sup>10</sup> = 10405071317.

Find the last ten digits of the series, 1<sup>1</sup> + 2<sup>2</sup> + 3<sup>3</sup> + ... + 1000<sup>1000</sup>.

## 分析

求  1<sup>1</sup> + 2<sup>2</sup> + 3<sup>3</sup> + ... + 1000<sup>1000</sup> 结果的最后10位数字

Python的一行代码即可。但是 c\c++\golang 处理起来就比较麻烦了。但是题目只要求给出结果的最后10位数字即可，问题就简单了，在整个计算过程中，只保留结果的最低10位数字即可，因为高位对结果不影响。保留低10位可以通过对10,000,000,000取模实现。


## 方法 对10,000,000,000取模

### CPP

```cpp
#include <stdio.h>
#include <stdint.h>

// 返回 n^p 的低10位
int64_t pow(int64_t n, int64_t p)
{
    int64_t mul = 1;
    for(int64_t i = 0; i < p; i++){
        mul *= n;
        mul %= 10000000000;
    }
    return mul;
}

int main()
{
    int64_t sum = 0;
    for(int64_t i = 1; i <= 1000; i++){
        sum += pow(i,i);
        sum %= 10000000000;
    }

    printf("%lld\n", sum);
    return 0;
}
```

### Golang

```go
package main

import "fmt"

// 返回 n^p 的低10位
func pow(n, p int64) int64 {
	mul := int64(1)
	for i := int64(0); i < p; i++ {
		mul *= n
		mul %= 10000000000
	}
	return mul
}

func main() {
	sum := int64(0)
	for i := int64(1); i <= 1000; i++ {
		sum += pow(i, i)
		sum %= 10000000000
	}

	fmt.Println(sum)
}
```

## 方法2 直接计算 [适合python]

```python
print( str( sum([i**i for i in range(1,1001)]) )[-10:] )
```

## 答案
9110846700

