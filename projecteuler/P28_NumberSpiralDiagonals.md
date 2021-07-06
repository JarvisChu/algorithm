# Problem 28: Number spiral diagonals

> https://projecteuler.net/problem=28

Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/project_euler_28_1.png)

It can be verified that the sum of the numbers on the diagonals is 101.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?


## 分析
数字螺旋对角线。求1001 x 1001的数字矩阵中，对角线数的和。

## 方法 找规律

n x n 表示数字矩阵，diff是每一层四个数字之间的差距(右下角开始，逆时针)。

- n = 1, diff = n-1 = 0,  该层所有数为 1
- n = 3, diff = n-1 = 2,  该层所有数为 3,5,7,9     [3=1+2]
- n = 5, diff = n-1 = 4,  该层所有数为 13,17,21,25 [13=9+4]
- n = 7, diff = n-1 = 6,  该层所有数为 31,37,43,49 [31=25+6]

所以规律为：n层的四个数字，其差距 diff=n-1

所以，根据规律，依次累加每一层的四个数即可

### CPP

```cpp
#include <stdio.h>

int main()
{
    int sum = 1;
    int last = 1; // 前面一层的最后一个数
    for( int n = 3; n <= 1001; n += 2){
        sum += last+(n-1) + last+2*(n-1) + last+3*(n-1) + last+4* (n-1); //每行四个数(右下角 + 左下角 + 左上角 + 右上角)
        last += 4*(n-1);
    }
    printf("%d\n",sum);
    return 0;
}
```

### Golang

```go
package main

import "fmt"

func main() {
	sum, last := 1, 1 // last 前面一层的最后一个数
	for n := 3; n <= 1001; n += 2 {
		sum += last + (n - 1) + last + 2*(n-1) + last + 3*(n-1) + last + 4*(n-1) //每行四个数(右下角 + 左下角 + 左上角 + 右上角)
		last += 4 * (n - 1)
	}
	fmt.Println(sum)
}

```


### Python

```python
last, sum = 1, 1
for n in range(3, 10002, 2):
    sum += last+(n-1) + last+2*(n-1) + last+3*(n-1) + last+4* (n-1); # four number each cycle
    last += 4 * (n - 1)
print(sum)
```

## 答案
666916710001