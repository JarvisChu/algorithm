# Problem 24: Lexicographic permutations

> https://projecteuler.net/problem=24

A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:

012   021   102   120   201   210

What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?

## 分析
将数字0-9 按照字典顺序排列，求第1,000,000个排列


## 方法1 根据全排列数，依次往后寻找 [包括递归和递推两者解法]

0-9的全排列有10！ = 3,628,800种。不可能把所有的排列都遍历一边找第1,000,000个。但是由于是按字典顺序的，所以可以从0位开始往后找。

每个数放在第0位，后面都有9!种排列。每个数放在第1位，后面都有8!种排列。后面的同理。

- 第0位 是数字 0，第一个排列是0123456789，即整体的第1个排列。
- 第0位 是数字 1，第一个排列是1023456789，即整体的第 9! + 1 个排列。后面的同理。

所以，若第一位数字是n，则n要满足n的第一个排列比1,000,000 小，n+1的第一个排列比1,000,000大。即 n*9!+1 <1,000,000 && (n+1)*9! + 1 >1,000,000。

第0位数字p0确定后，再确定第1位的数字p1。

p0打头的第一个排列的次序是 p0 * 9! +1。 所以第1,000,000个数，也就是p1开头的 第remain = 1,000,000 -  (p0 * 9! +1) 个数。

此时相当于 从0~9（除去p0）中挑选出第n个数，满足

n*8!+1 <remain && (n+1)*8! +1 >remain.

依次类推，确定获得每一位。

> **总结下规律**： remain = 1,000,000，确定第 n 位的数字时，求 i，满足 `i*(9-n)! + 1 <remain && (i+1)*(9-n)! + 1 > remain` ，然后从0~9中按顺序找到第i个数字，作为第 n 位的数字，然后，remain –= i*(9-n)!; i++; 再同理确定下一位。


### CPP

**递归实现**

```cpp
#include <stdio.h>

int perm[10]; // 存放最终的排列
int flag[10]; // 标志0-9是否已使用，0 未使用，1 已使用

// n!
int A(int n)
{
    int rel=1;
    for(int i=1; i<=n; i++) rel *= i;
    return rel;
}

// 递归实现
// 设置perm数列的第 n 位, n 属于 0~9
// remain 表示当前距离目标排列还有多远。初始时为 1000000
void setPermN(int n, int remain)
{    
    // 说明 perm的 0~9 位都已找完，表明找到了目标排列，打印出来
    if(n > 9) {     
        printf("perm: ");
        for(int i = 0; i <= 9; i++){
            printf("%d ", perm[i]);
        }
        printf("\n");
        return;
    }

    int a = A(9-n);

    // 确定 perm[n] 应该填什么数字
    for(int i = 0; i <= 9; i++){

        if ( i*a + 1 <= remain && (i+1)*a +1 > remain ){
            // 第 n 位，应该填 剩下所有未使用的数字中的第 i 个数字 (0~9 排序)

            int cnt = 0;
            for(int k = 0; k <= 9; k++){
                if(flag[k] == 0) cnt ++;
                if(cnt == i + 1){
                    // 第 n 位 应该填k
                    perm[n] = k;
                    flag[k] = 1;

                    // 继续设置数列的n+1位
                    setPermN(n+1, remain - i*a);
                    return;
                }
            }

            return;
        }
    }

    return;
}

int main()
{
    for (int i=0;i<10;i++) flag[i]=0; //初始化所有数字都未使用

    setPermN(0, 1000000);

    return 0;
}
```

**递推实现**

```cpp
#include <stdio.h>

int perm[10]; // 存放最终的排列
int flag[10]; // 标志0-9是否已使用，0 未使用，1 已使用

// n!
int A(int n)
{
    int rel=1;
    for(int i=1; i<=n; i++) rel *= i;
    return rel;
}

// 递推实现
// 设置perm数列的每一位
// remain 表示当前距离目标排列还有多远。初始时为 1000000
void setPerm(int remain)
{
    // 10次循环，依次确定 perm 的第 0~9 位的数字
    for (int n=0; n<10; n++){

        int a = A(9-n);

        //第n位数字的次序
        int i = 0;
        for(i=0; i<=9; i++){
            if ( i*a + 1 <= remain && (i+1)*a +1 > remain ){
                // 第 n 位，应该填 剩下未使用的的数字中的第 i 个数字 (0~9 排序)
                // cout<<"n="<<n<<" i="<<i<<", "<<i*a + 1<<" "<<remain<<" "<<(i+1)*a +1;
                remain -= i*a;
                break;
            }
        }

        // 至此，我们知道 perm 的第 n 位，应该填剩下未使用的的数字中的第 i 个数字 (0~9 排序)

        int cnt=0;
        for(int k=0;k<10;k++){
            if(flag[k] == 0) cnt++;
            if(cnt==i+1){
                perm[n] = k;
                flag[k] = 1;
                break;
            }
        }
    }

    // 打印结果
    printf("perm: ");
    for(int i = 0; i <= 9; i++){
        printf("%d ", perm[i]);
    }
    printf("\n");
}

int main()
{
    for (int i=0;i<10;i++) flag[i]=0; //初始化所有数字都未使用

    setPerm(1000000);

    return 0;
}
```

### Golang

**递归实现**

```go
package main

import (
	"fmt"
)

var perm = [10]int{} // 存放最终的排列
var flag = [10]int{} // 标志0-9是否已使用，0 未使用，1 已使用

// n!
func A(n int) int {
	rel := 1
	for i := 1; i <= n; i++ {
		rel *= i
	}
	return rel
}

// 递归实现
// 设置perm数列的第 n 位, n 属于 0~9
// remain 表示当前距离目标排列还有多远。初始时为 1000000
func setPermN(n, remain int) {
	// 说明 perm的 0~9 位都已找完，表明找到了目标排列，打印出来
	if n > 9 {
		fmt.Printf("perm: ")
		for i := 0; i <= 9; i++ {
			fmt.Printf("%d ", perm[i])
		}
		fmt.Println("")
		return
	}

	a := A(9 - n)

	// 确定 perm[n] 应该填什么数字
	for i := 0; i <= 9; i++ {

		if i*a+1 <= remain && (i+1)*a+1 > remain {
			// 第 n 位，应该填 剩下所有未使用的数字中的第 i 个数字 (0~9 排序)

			cnt := 0
			for k := 0; k <= 9; k++ {
				if flag[k] == 0 {
					cnt++
				}

				if cnt == i+1 {
					// 第 n 位 应该填k
					perm[n] = k
					flag[k] = 1

					// 继续设置数列的n+1位
					setPermN(n+1, remain-i*a)
					return
				}
			}

			return
		}
	}

	return
}

func main() {
	setPermN(0, 1000000)
}

```

**递推实现**

```go
package main

import (
	"fmt"
)

var perm = [10]int{} // 存放最终的排列
var flag = [10]int{} // 标志0-9是否已使用，0 未使用，1 已使用

// n!
func A(n int) int {
	rel := 1
	for i := 1; i <= n; i++ {
		rel *= i
	}
	return rel
}

// 递推实现
// 设置perm数列的每一位
// remain 表示当前距离目标排列还有多远。初始时为 1000000
func setPerm(remain int) {
	// 10次循环，依次确定 perm 的第 0~9 位的数字
	for n := 0; n < 10; n++ {

		a := A(9 - n)

		// 第n位数字的次序
		i := 0
		for i = 0; i <= 9; i++ {
			if i*a+1 <= remain && (i+1)*a+1 > remain {
				// 第 n 位，应该填 剩下未使用的的数字中的第 i 个数字 (0~9 排序)
				remain -= i * a
				break
			}
		}

		// 至此，我们知道 perm 的第 n 位，应该填剩下未使用的的数字中的第 i 个数字 (0~9 排序)

		cnt := 0
		for k := 0; k < 10; k++ {
			if flag[k] == 0 {
				cnt++
			}
			if cnt == i+1 {
				perm[n] = k
				flag[k] = 1
				break
			}
		}
	}

	// 打印结果
	fmt.Printf("perm: ")
	for i := 0; i <= 9; i++ {
		fmt.Printf("%d ", perm[i])
	}
	fmt.Println("")
}

func main() {
	setPerm(1000000)
}

```


### Python 

**递归实现**

```python
perm = [0,0,0,0,0,0,0,0,0,0] # 存放最终的排列
flag = [0,0,0,0,0,0,0,0,0,0] # 标志0-9是否已使用，0 未使用，1 已使用

# n!
def A(n) :
	rel = 1
	for i in range(1, n+1): 
		rel *= i
	return rel

# 递归实现
# 设置perm数列的第 n 位, n 属于 0~9
# remain 表示当前距离目标排列还有多远。初始时为 1000000
def setPermN(n, remain) :
	# 说明 perm的 0~9 位都已找完，表明找到了目标排列，打印出来
	if n > 9 :
		print("perm: ", end="")
		for i in range(0,10):
			print(perm[i], end="")
		print("")
		return

	a = A(9 - n)

	# 确定 perm[n] 应该填什么数字
	for i in range(0,10) :

		if i*a+1 <= remain and (i+1)*a+1 > remain :
			# 第 n 位，应该填 剩下所有未使用的数字中的第 i 个数字 (0~9 排序)

			cnt = 0
			for k in range(0,10) :
				if flag[k] == 0 :
					cnt = cnt + 1

				if cnt == i+1 :
					# 第 n 位 应该填k
					perm[n] = k
					flag[k] = 1

					# 继续设置数列的n+1位
					setPermN(n+1, remain-i*a)
					return
			return
	return


setPermN(0, 1000000)
```

**递推实现**

```python
perm = [0,0,0,0,0,0,0,0,0,0] # 存放最终的排列
flag = [0,0,0,0,0,0,0,0,0,0] # 标志0-9是否已使用，0 未使用，1 已使用

# n!
def A(n) :
	rel = 1
	for i in range(1, n+1): 
		rel *= i
	return rel

# 递推实现
# 设置perm数列的每一位
# remain 表示当前距离目标排列还有多远。初始时为 1000000
def setPerm(remain):
	# 10次循环，依次确定 perm 的第 0~9 位的数字
	for n in range(0, 10) :

		a = A(9 - n)

		# 第n位数字的次序
		i = 0
		for i in range(0,10) : 
			if i*a+1 <= remain and (i+1)*a+1 > remain :
				# 第 n 位，应该填 剩下未使用的的数字中的第 i 个数字 (0~9 排序)
				remain -= i * a
				break

		# 至此，我们知道 perm 的第 n 位，应该填剩下未使用的的数字中的第 i 个数字 (0~9 排序)

		cnt = 0
		for k in range(0,10):
			if flag[k] == 0 :
				cnt = cnt + 1
			if cnt == i+1 :
				perm[n] = k
				flag[k] = 1
				break


	# 打印结果
	print("perm: ", end="")
	for i in range(0,10) :
		print(perm[i], end="")
	print("")

setPerm(1000000)
```

**更简单的递推实现**

使用列表存储，方便将已用的数字删除

```python
from functools import reduce
def A(n):
    '''return n!'''
    if n == 0 or n == 1:
        return 1
    else:
        return reduce(lambda x,y:x*y,range(1,n+1))

perm = []
digits = list('0123456789')

target = 1000000
for i in range(0,10):
    for n in range(0,10):
        if n * A(9-i) + 1 <= target and (n + 1) * A(9-i) +1 > target:
            perm.append(digits[n])
            digits.remove(digits[n])
            target -= n*A(9-i)
            break
print(perm)
```

A(n) 返回n!。 0~9 按序存储在列表digits中。

如果对于排列的第i位（从0开始） 如果 `n * A(9-i) + 1 <= target and (n + 1) * A(9-i) +1 > target`，表明第i位的数字是digit[n]，所以perm[i] = digit[n],然后将digit[n]从digit[] 列表中删除，target–= n * A(9-i)


## 方法2 使用STL中algorithm算法库中的next_permutation()函数 [适用于C++]

> 来自 Project Euler论坛中 第 1 页用户 cd-rw 的答案

```cpp
#include <iostream>
#include <algorithm>

int main()
{
    char ca[]="0123456789";
    for(int i=1;i<1000000;i++) std::next_permutation(ca, ca+10);
    std::cout << ca << std::endl;
    return 0;
}
```

[next_permutation()](https://www.cplusplus.com/reference/algorithm/next_permutation/) 产生序列字典序的下一项.

## 答案
2783915460