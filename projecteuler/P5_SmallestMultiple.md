# Problem 5: Smallest multiple

2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

## 分析
能整除1~20的最小正整数，即 1~20的最小公倍数

能被11~20 整除的数，肯定能被1~10 整除。所以问题可以转换为求能被11~20连续整除的数。

## 方法1 暴力求解

### CPP

```cpp
#include <stdio.h>
#include <string.h>
#include <stdint.h>


bool isDivisible(int64_t n)
{
    for(int i=11; i<=20; i++){
        if( n%i != 0) return false;
    }
    return true;
}

int main()
{
    for(int64_t i = 20; ; i++){
        if(isDivisible(i)){
            printf("%lld\n", i);
            return 0;
        }
    }
    
    return 0;
}
```

### Golang

```go
package main

import "fmt"

func isDivisible(n int64) bool{
	for i:=int64(11); i<=20; i++ {
		if n % i != 0 {
			return false
		}
	}
	return true
}

func main(){
	for i := int64(20); ; i++ {
		if isDivisible(i){
			fmt.Println(i)
			return
		}
	}
}
```

### Python

```python
def isDivisible(n):
    for i in range(11,21) :
        if n % i != 0 :
            return False
    return True

i = 20
while True:
    if isDivisible(i):
        print(i)
        break
    i = i+1
```

我的笔记本上运行了足足近30秒之久，才出的结果。也可以对比出C\C++与Python代码效率之间的差别。

## 方法2 更高效的算法

> 来自论坛中 lassevk 的方法

算法的思想如下：

- 从 n = 1 开始，往上寻找能被 1~20 整除的数
- 如果 n 能被 k 整除，其中 k 属于[1,21)，则继续判断 n 能否被 k+1 整除；当 n 能被 k=20 整除时，n就是要寻找的数
- 如果 n 不能被 k 整除，则需要往后找下一个 n. 为了提高效率，不是简单的将 n++，而是通过算法将n尽量往后移动。这里也是**算法的核心**。

如果尽可能的往后移动呢？ 那就是尽可能的利用已知的信息。

当 n 不能被 k 整除时，**n 是可以被 [1, k-1] 整除的**，n 是[1,k-1]的最小公倍数
比如 下一个 n 的值是 m，那么 m 也必然能被 [1,k-1] 整除，即 m 也是[1,k-1]的公倍数，则 m = a*n, a为正整数。
所以依次检测 m = 2*n, 3*n, ... 直到 m 可以被k 整除，即 m 是[1,k]的最小公倍数，此时，继续下一轮，判断 m 是否能被 k+1 整除。

### CPP

```cpp
#include <stdio.h>

int main()
{
    int n = 1;
    for( int k=1; k <= 20; k++ ){
        if( n % k == 0) continue;

        for(int i = 2; i< 21; i++){
            if( (n * i) % k == 0){
                n *= i;
                break;
            }
        }
    }

    printf("%d\n", n);
    return 0;
}

```

### Golang

```go
package main

import "fmt"

func main(){
	n := 1
	for k:=1; k <= 20; k++ {
		if n % k == 0 {
			continue;
		}

        for i := 2; i < 21; i++ {
            if (n * i) % k == 0 {
                n *= i;
                break;
            }
        }
    }

    fmt.Println(n);
}
```

### Python

```python
n = 1 # 是要寻找的能被 1~20 整除的数
for k in range(1, 21):

    # 运行到这里时，表明 n 已经可以被 1~k-1 整除了

    # 判断 n 能否被 k 整除
    if n % k == 0:
        continue # n 能被k整除，继续下一轮，判断能否被 k+1 整除

    # n 不能被 k 整除
    # 为了提高效率，不是简单的将 n++，而是尽量的将 n 往后移动
    # 因为此时 n 已经能被 1~k-1 整除了，因为要寻找的下一个 n 也必然要满足能被 1~k-1 整除，那么 下一个 n 必然是当前 n 的整数倍
    # 所以 依次将 n 扩大 1~N倍，判断是否能被 k 整除
    # 因为 k 的范围是 [1,21)，所以最多只需要扩大[1,21) 倍就可以了。
    # 当扩大到某个倍数后，如 n * j，能被 k 整除，则 n = n*i，继续判断 k+1
    if n % k > 0:
        for i in range(2, 21):
            if (n*i) % k == 0:
                n *= i
                break
print(n)
```

## 答案
232792560