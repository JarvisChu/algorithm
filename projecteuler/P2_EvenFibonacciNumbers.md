# Problem 2: Even Fibonacci numbers

> https://projecteuler.net/problem=2

Each new term in the Fibonacci sequence is generated by adding the previous two terms. By starting with 1 and 2, the first 10 terms will be:

1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.

## 分析
Fibonacci数列中小于4百万的所有的偶数的和。

## 方法1：一边生成Fibonacci数列，一边累加其中的偶数

### CPP

```cpp
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a=1, b=2, sum=2;
    
    int c = a+b;
    while(c <= 4000000){
        if(c%2 == 0) sum += c;
        a = b;
        b = c;
        c = a+b;
    }

    printf("%d\n",sum);
    return 0;
}
```

### Golang

```go
package main

import "fmt"

func main(){
    a, b, sum := 1, 2, 2

	c := a + b
	for c <= 4000000 {
		if c % 2 == 0 {
			sum += c
		}
		a, b = b, c
		c = a + b
	}

	fmt.Println(sum)
}
```
### Python

```python
a, b, sum = 1, 2, 2

c = a + b
while c <= 4000000:
    if c % 2 == 0:
        sum = sum + c
    a = b
    b = c
    c = a + b 
print(sum)    
 
```

## 方法2 观察数列，找到规律每隔两个奇数出现一个偶数
> 来自论坛中 Begoner 的方法

Fibonacci数列：

1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610...

用O表示奇数，用E表示偶数，则数列可表示为：

O, O, E, O, O, E, O, O, E, O, O, E, O, O, E...

设开始的两个奇数为x,y，则数列为：

x, y, **x+y**, x+2y, 2x+3y, **3x+5y**…

```python
x = y = 1
s = 0
while y < 4000000:
    s = s + x + y
    x, y = x + 2 * y, 2 * x + 3 * y
print(s)
```

相当于三个数字一组，累加每组的第三个数字。前后两组的关系如下：

```
x,    y     -> **x+y**
x+2y, 2x+3y -> **3x+5y**
```


## 答案
4613732
