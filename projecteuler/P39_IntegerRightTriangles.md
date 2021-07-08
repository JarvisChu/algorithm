# Problem 39: Integer right triangles

> https://projecteuler.net/problem=39

If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.

{20,48,52}, {24,45,51}, {30,40,50}

For which value of p ≤ 1000, is the number of solutions maximised?

## 分析

p 是直角三角形的周长，边为{a,b,c}。p =120 的直角三角形只有三种：{20,48,52}, {24,45,51}, {30,40,50}。

p ≤ 1000，找到一个p ，它的直角三角形种类最多。

若 {a,b,c} 能形成周长为p的直角三角形，则 

- a + b + c = p； 
- a² + b² = c²。

假设 a ≤  b < c， 则 a < p/3，b < p/2，有了a和b的范围之后，就可以遍历求解了

## 方法1 遍历求解

### CPP

```cpp
#include <stdio.h>

int main()
{
    int maxCnt = 0, maxP = 0;
    for(int p = 3; p < 1000; p++){
        
        int cnt = 0;
        for(int a = 1; a <= p/3; a++ ){
            for(int b = a; b <= p/2; b++){
                if(a*a + b*b == (p-a-b)*(p-a-b)){
                    //printf("(%d,%d,%d), p=%d\n", a,b,p-a-b,p);
                    cnt ++;
                }
            }    
        }

        if(cnt > maxCnt){
            maxCnt = cnt;
            maxP = p;
        }
    }

    printf("maxP:%d\n", maxP);
    return 0;
}
```

### Golang

```go
package main

import (
	"fmt"
)

func main() {

	maxCnt, maxP := 0, 0
	for p := 3; p < 1000; p++ {

		cnt := 0
		for a := 1; a <= p/3; a++ {
			for b := a; b <= p/2; b++ {
				if a*a+b*b == (p-a-b)*(p-a-b) {
					//fmt.Printf("(%d,%d,%d), p=%d\n", a, b, p-a-b, p)
					cnt++
				}
			}
		}

		if cnt > maxCnt {
			maxCnt = cnt
			maxP = p
		}
	}

	fmt.Printf("maxP:%d\n", maxP)
}

```

### Python

```python
maxCnt, maxP = 0, 0
for p in range(3,1000) :
	cnt = 0
	for a in range(1, int(p/3)) :
		for b in range(a, int(p/2)) :
			if a*a+b*b == (p-a-b)*(p-a-b) :
				#print(a, b, p-a-b, p)
				cnt = cnt + 1
	if cnt > maxCnt :
		maxCnt = cnt
		maxP = p

print("maxP:", maxP)
```

## 答案

840

p=840，共有8种。分别为：

40  399 401
56  390 394
105 360 375
120 350 370
140 336 364
168 315 357
210 280 350

## 知识点

如果：a² + b² =c²，则(a,b,c) 称为 **毕达哥拉斯三元组(Pythagorean Triple)**。

> [毕达哥拉斯三元组 (Pythagorean Triple)](https://mathworld.wolfram.com/PythagoreanTriple.html)
>
> [百度百科](https://baike.baidu.com/item/%E6%AF%95%E8%BE%BE%E5%93%A5%E6%8B%89%E6%96%AF%E4%B8%89%E5%85%83%E6%95%B0%E7%BB%84/4539845)
