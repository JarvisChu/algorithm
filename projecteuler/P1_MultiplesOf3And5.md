# Problem 1: Multiples of 3 and 5

> https://projecteuler.net/problem=1

If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.

## 分析
欧拉计划第一题，入门，相当于其它OJ系统的a+b题目。题目虽简单，却不能就题论题，提交成功就收工。完成题目后，去论坛中研究各种高效、巧妙的实现方法才是真正的精华所在！本系列不仅有我自己的解法，还会将论坛中的精华方法摘录于此，我主要关注的是C\C++\Golang\Python实现。

## 思路1：遍历 1-1000，累加3和5的倍数

### CPP

```cpp
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i=0,sum = 0;
    for(i=1;i<1000;i++){
        if(i%3==0 ||i%5==0) sum+=i;
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
	i, sum := 0, 0
	for i = 0; i < 1000; i++ {
		if i % 3 == 0 || i % 5 == 0 {
			sum  += i
		}
	}
	fmt.Println(sum)
}
```

### Python
sum函数 + 列表推导

```python
print( sum( [x for x in range (1,1000) if x % 3 == 0 or x % 5 == 0]) )
```

使用列表推导，将(1,1000)中3和5的倍数形成一个列表，使用sum函数统计列表的和。

## 方法2：直接统计3和5的倍数，循环次数更少

### CPP

```cpp
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i=0, sum = 0;
    while( 3 * i < 1000){
        sum += 3 * i; i++; 
    }

    i = 0;
    while( 5 * i < 1000){
        if(5 * i % 3 != 0) sum += 5 * i;
        i++;
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
	i, sum := 0, 0
	for 3 * i < 1000 {
        sum += 3 * i
		i++
    }

    i = 0
    for 5 * i < 1000 {
        if 5 * i % 3 != 0 {
			sum += 5 * i
		}
        i++
    }
	fmt.Println(sum)
}
```

### Python 
sum函数 + set集合

```python
print( sum(set(range(0,1000,3))|set(range(0,1000,5))) )
```

Python 中set 是一个无序不重复的元素集合，支持集合的交（&）、并（|）、差（-）等操作。此处，使用步长为3的range，生成一个3的倍数的集合，同理生成5的倍数的集合。使用|求两个集合的并集。最后使用sum函数求和。

## 答案
233168

## 知识点
- Python 列表推导
- Python set集合