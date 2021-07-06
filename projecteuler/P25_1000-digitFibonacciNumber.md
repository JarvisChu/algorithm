# Problem 25: 1000-digit Fibonacci number

The Fibonacci sequence is defined by the recurrence relation:

F<sub>n</sub> = F<sub>n−1</sub> + F<sub>n−2</sub>, where F<sub>1</sub> = 1 and F<sub>2</sub>= 1.

Hence the first 12 terms will be:

- F<sub>1</sub> = 1
- F<sub>2</sub> = 1
- F<sub>3</sub> = 2
- F<sub>4</sub> = 3
- F<sub>5</sub> = 5
- F<sub>6</sub> = 8
- F<sub>7</sub> = 13
- F<sub>8</sub> = 21
- F<sub>9</sub> = 34
- F<sub>10</sub> = 55
- F<sub>11</sub> = 89
- F<sub>12</sub> = 144

The 12th term, F<sub>12</sub>, is the first term to contain three digits.

What is the index of the first term in the Fibonacci sequence to contain 1000 digits?


## 分析
求Fibonacci数列的第一个包含1000位数字的项对应的序号。

本质还是大数问题，和 [Problem 16 Power digit sum](http://zhujiangtao.com/problem-16-power-digit-sum/) 相同。所以可以直接复用 Problem 16 中的方法。

### 方法1 使用字符串实现乘法，适用于C++

> 详见 [Problem 16 Power digit sum](http://zhujiangtao.com/problem-16-power-digit-sum/) ，复用其中的add/mul等函数即可，此处不再赘述。

### CPP

```cpp
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main()
{
    std::vector<char> f1; // f1 = 1
    f1.push_back('1');

    std::vector<char> f2; // f2 = 1
    f2.push_back('1');

    int seq = 3;
    while(true){
        std::vector<char> f3 = add(f1, f2); // 复用 Problem 16 中的add
        if (f3.size() >= 1000){
            printf("seq:%d\n", seq);
            for(int i=0; i < f3.size(); i++) printf("%d", f3[i]);
            break;
        }

        f1 = std::move(f2);
        f2 = std::move(f3);
        seq ++;
    }

    return 0;
}
```

## 方法2 使用大数包，适用于golang

```go
package main

import (
	"fmt"
	"math/big"
)

func main() {

	f1 := big.NewInt(1) // f1 = 1
	f2 := big.NewInt(1) // f2 = 1

	seq := 3
	for {
		f3 := f1.Add(f1,f2)
		if len(f3.String()) >= 1000 {
			fmt.Println(seq)
			fmt.Println(f3.String())
			break
		}
		f1 = f2
		f2 = f3
		seq ++
	}
}
```

## 方法3 直接计算，适用于python

```python
f1, f2, seq = 1, 1, 3 # f1 = 1, f2 = 1
while True:
    f3 = f1 + f2
    if len(str(f3)) >= 1000:
        print(seq, f3)
        break
    seq = seq + 1
    f1, f2 = f2, f3
```

## 答案
4782