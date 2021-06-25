# Problem 9: Special Pythagorean triplet

> https://projecteuler.net/problem=9

A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

a<sup>2</sup> + b<sup>2</sup> = c<sup>2</sup>

For example, 3<sup>2</sup> + 4<sup>2</sup> = 9 + 16 = 25 = 5<sup>2</sup>.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.


## 分析
毕达哥拉斯三元组。求三个数a,b,c，满足a+b+c=1000, a<sup>2</sup> + b<sup>2</sup> = c<sup>2</sup>.

## 方法1 穷举法

思路很简单，a从1-1000遍历，b从 a 到 (1000-a) 遍历，判断 a<sup>2</sup> + b<sup>2</sup> == (1000-a-b)<sup>2</sup> 是否成立。

### C\C++

```cpp
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,a=0,b=0,c=0;

    for(i=1;i<1000;i++){
        for(j=i;j<1000-i;j++){
            if(i*i+j*j == (1000-i-j)*(1000-i-j)){
                a = i;b=j;c=1000-i-j;
                printf("a=%d,b=%d,c=%d,abc=%d \n",a,b,c,a*b*c);
                return 0;
            }
        }
    }

    return 0;
}
```

### Golang

```go
package main

import "fmt"

func main(){
	for i:=1; i<1000; i++ {
		for j:=i; j<1000-i; j++ {
            if i*i+j*j == (1000-i-j)*(1000-i-j) {
                // There exists exactly one Pythagorean triplet for which a + b + c = 1000.
                fmt.Printf("a=%d,b=%d,c=%d,abc=%d \n", i,j,1000-i-j, i * j * (1000-i-j) )
                return
            }
        }
    }
}
```

### Python

```python
# print a*b*c
print( [a * b * (1000-a-b) for a in range (1,1000) for b in range (a, 1000-a) if a**2 + b**2 == (1000-a-b)**2 ] )

# print a,b,c and a*b*c
#arr = [(a, b, (1000-a-b)) for a in range (1,1000) for b in range (a, 1000-a) if a**2 + b**2 == (1000-a-b)**2 ]
#print("a:", arr[0][0], "b:", arr[0][1], "c:", arr[0][2], "a*b*c:", arr[0][0] * arr[0][1] * arr[0][2])
```

## 答案
31875000