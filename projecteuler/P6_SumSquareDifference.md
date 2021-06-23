# Problem 6: Sum square difference

> https://projecteuler.net/problem=6

The sum of the squares of the first ten natural numbers is,

1<sup>2</sup> + 2<sup>2</sup> + ... + 10<sup>2</sup> = 385 

The square of the sum of the first ten natural numbers is,

(1 + 2 + ... + 10)<sup>2</sup> = 55<sup>2</sup> = 3025

Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 - 385 = 2640.

Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.

## 分析

1~100 的 完全平方和与平方的和的差.

## 方法1：直接累加统计

### CPP

```cpp
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main()
{
   int64_t sum_of_square  = 0; // 完全平方和 1^2 + 2^2 + ... + 10^2
   int64_t square_of_sum  = 0; // 和的平方 (1 + 2 + ... + 10)^2
   for(int i=1;i<=100;i++){
        square_of_sum += i;
        sum_of_square += i*i;
    }
    square_of_sum *= square_of_sum;

    printf("%lld\n",square_of_sum - sum_of_square);
    return 0;
}
```

### Golang

```
package main

import "fmt"

func main(){
	sum_of_square  := int64(0) // 完全平方和 1^2 + 2^2 + ... + 10^2
	square_of_sum  := int64(0) // 和的平方 (1 + 2 + ... + 10)^2
	for i:=int64(1); i<=100; i++{
		square_of_sum += i
		sum_of_square += i*i
	}
	square_of_sum *= square_of_sum;
	
    fmt.Println(square_of_sum - sum_of_square);
}
```

### Python

```
sum_of_square = sum([x*x for x in range(1,101)])    # 完全平方和 1^2 + 2^2 + ... + 10^2
square_of_sum = sum([x for x in range(1,101)]) ** 2 # 和的平方 (1 + 2 + ... + 10)^2
print(square_of_sum - sum_of_square)
```

两个列表推导就okay了，十分简洁。这就是我喜欢Python的原因。

Keep it Simple but functional!

## 方法2 公式法（源自官方的pdf）

方法1 不适合 n 很大的情况，此时可以通过公式推导，直接得到完全平方和 以及 和的平方 与 n的关系。

对于和的平方： 

```
square_of_sum = (1 + 2 + ... + n)^2 = ( (n+1)*n / 2)^2
```

对于完全平方和：
设 f(n) = 1^2 + 2^2 + ... + n^2
我们只要找到 f(n) 的表达式即可

假设 f(n) = a*n^3 + b*n^2 + c*n + d，带入 n = 0,1,2,3 得到

```
f(0) = d = 0
f(1) = a+b+c+d = 1
f(2) = 8a+4b+2c+d = 5
f(3) = 27a+9b+3c+d = 14
```

计算可得：a = 1/3, b = 1/2, c = 1/6, d = 0
f(n) = 1/3 * n^3 + 1/2 * n^2 + 1/6 * n = 1/6 * (2n^3 + 3n^2 + n) = 1/6 * (2n+1) * (n+1)

下面需要证明 f(n+1) = f(n) + (n+1)^2

f(n+1) = 1/6 * ( 2(n+1)^3 + 9(n+1)^2 + 13(n+1) )
       = 1/6 * (2n^3 + 9n^2 + 13n)

f(n) + (n+1)^2 = 1/6 * (2n^3 + 3n^2 + n) + (n+1)^2
               = 1/6 * (2n^3 + 9n^2 + 13n)

可知：f(n+1) = f(n) + (n+1)^2
公式成立

所以对于完全平方和

```
sum_of_square = 1/6 * (2n+1) * (n+1)
```


故：

```
square_of_sum - sum_of_square = ( (n+1)*n / 2)^2 - 1/3 * n^3 + 1/2 * n^2 + 1/6 * n
                              = 1/4 * n^4 + 1/2 * n^3 + 1/4 * n^2 - 1/3 * n^3 - 1/2 * n^2 - 1/6 * n
                              = 1/4 * n^4 + 1/6 * n^3 - 1/4 * n^2 - 1/6 * n
```

有了上面这个结论后，给定 n 可以直接获取 square_of_sum - sum_of_square 的值，使用何种语言来实现已经无所谓了。

```python
def dif(n):
    return 1/4 * n**4 + 1/6 * n**3 - 1/4 * n**2 - 1/6 * n

print(dif(100))
```


## 答案
25164150