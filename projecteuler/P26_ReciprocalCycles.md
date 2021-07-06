# Problem 26: Reciprocal cycles

> https://projecteuler.net/problem=26

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/project_euler_26_1.png)


## 分析

1/6 = 0.1(6) 表示0.16666…，拥有 1 位数字的重复周期

1/7=0.(142857) 拥有6位的重复周期

找到d < 1000, 1/d 拥有最长重复周期的数字。

## 方法1 模拟1/n的实际计算过程，记录下商的每一位，判断有没有出现重复

方法：模拟1/n的实际计算过程，具体的为div(n)函数。详细说明如下：

使用 div(n) 函数返回 1/n 的重复周期 和 1/n 的商(可选)       
模拟了实际的 1/n 的计算过程，除数始终为n,

初始状态时： 被除数 numerator = 1，商集合 fraction 为空，余数集合 reminder 为空。执行下面的循环：

- 1. 如果numerator < n，不够除，则numerator *= 10, 同时 0 追加到 fraction 中，如此循环，直到够除，才跳转到2   
- 2. 计算余数 c = numerator % n, 并将商 numerator/n 追加都 fraction 中，如果 c==0，则表示能除尽，不存在重复周期，返回 0 和 fraction，跳转到4。否则跳转到3   
- 3. 余数 c != 0, 查找 reminder, 确定 c 是否出现过，如果出现过，则出现了重复周期，则统计第一次出现（包括这次）直到 reminder 结束的数字个数 cnt。返回 cnt 和 fraction，跳转到4. 否则将余数 c 追加到 reminder 中，c 赋给 numerator, numerator = c, 跳转到1，继续循环。   
- 4. 结束

### CPP

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************************
*功能：返回 1/n 的重复周期 和 1/n的商 （可选）
*说明：模拟了实际的 1/n 的计算过程，除数始终为n,被除数初始为1,numerator = 1，商集合fraction为空，余数集合reminder为空
执行下面的循环：
1. 如果numerator < n，不够除，则numerator *= 10,同时0追加到fraction中，如此循环，直到够除，才跳转到2
2. 计算余数c = numerator % n,并将商numerator/n 追加都fraction中，如果c==0，则表示能除尽，不存在重复周期，返回0和fraction，跳转到4。否则跳转到3
3. 余数c != 0, 查找reminder,确定c是否出现过，如果出现过，则出现了重复周期，则统计第一次出现（包括这次）直到reminder结束的数字个数cnt。返回cnt和fraction，跳转到4.否则将余数c追加到reminder中，c 赋给numerator,numerator = c,跳转到1，继续循环。
4. 结束
************************************************************************/
int div(int n)
{
    int numerator = 1; // 被除数（分子）
    vector<int> fraction; // 商 集合 (如果需要，可以返回这个商)
    vector<int> reminder; // 余数 集合

    while (1){

        // Step 1 : 确保numerator >= n
        while (numerator < n){
            numerator *= 10;
            fraction.push_back(0);
        }

        // Step 2 ：计算余数c
        int c = numerator % n;
        fraction.push_back(numerator/n);
        //cout<<"c:"<<c<<endl;
        if (c == 0){
            return 0; // 能除尽，结束
        }

        // Step 3 ：余数不为0，判断余数是否出现过
        else{
            // 找到c出现的位置
            vector<int>::iterator it = find(reminder.begin(), reminder.end(), c);
            if (it != reminder.end()){ // 出现过，说明有重复了
                int cnt=0;
                for (; it!=reminder.end(); ++it ){ // 从上次出现的位置，计算到当前的长度
                    cnt++;
                }
                return cnt;
            }
            else{ //没出现过
                reminder.push_back(c);
                numerator = c; // 继续下一轮
            }
        }
    }
}

int main()
{
    int max_index = 0, max_cycle = 0;
    for (int i=1; i<1000; i++){
        if (div(i) > max_cycle){
            max_index = i;
            max_cycle = div(i);
        }
    }
    cout<<"重复周期最长的数为："<<max_index<<endl;
    cout<<"最长的重复周期为： "<<max_cycle<<endl;
    return 0;
}
```

### Golang

```go
package main

import "fmt"

/************************************************************************
*功能：返回 1/n 的重复周期 和 1/n的商 （可选）
*说明：模拟了实际的 1/n 的计算过程，除数始终为n,被除数初始为1,numerator = 1，商集合fraction为空，余数集合reminder为空
执行下面的循环：
1. 如果numerator < n，不够除，则numerator *= 10,同时0追加到fraction中，如此循环，直到够除，才跳转到2
2. 计算余数c = numerator % n,并将商numerator/n 追加都fraction中，如果c==0，则表示能除尽，不存在重复周期，返回0和fraction，跳转到4。否则跳转到3
3. 余数c != 0, 查找reminder,确定c是否出现过，如果出现过，则出现了重复周期，则统计第一次出现（包括这次）直到reminder结束的数字个数cnt。返回cnt和fraction，跳转到4.否则将余数c追加到reminder中，c 赋给numerator,numerator = c,跳转到1，继续循环。
4. 结束
************************************************************************/
func div(n int) int {

	numerator := 1             // 被除数（分子）
	fraction := make([]int, 0) // 商 集合 (如果需要，可以返回这个商)
	reminder := make([]int, 0) // 余数 集合

	for {

		// Step 1 : 确保 numerator >= n
		for numerator < n {
			numerator *= 10
			fraction = append(fraction, 0)
		}

		// Step 2 ：计算余数c
		c := numerator % n
		fraction = append(fraction, numerator/n)
		if c == 0 {
			return 0 // 能除尽，结束
		}

		// Step 3 ：余数不为0，判断余数c是否出现过
		loc := -1
		for i, r := range reminder {
			if r == c {
				loc = i
				break
			}
		}

		if loc >= 0 { // 出现过，说明有重复了
			size := len(reminder) - loc // 从上次出现的位置，计算到当前的长度
			return size
		} else { // 没有出现过，继续往后除
			reminder = append(reminder, c)
			numerator = c
		}
	}

	return 0
}

func main() {
	maxIndex, maxCycle := 0, 0
	for i := 1; i < 1000; i++ {
		if div(i) > maxCycle {
			maxIndex = i
			maxCycle = div(i)
		}
	}

	fmt.Println("重复周期最长的数为：", maxIndex)
	fmt.Println("最长的重复周期为：", maxCycle)
}

```

### Python

```python
#************************************************************************
#功能：返回 1/n 的重复周期 和 1/n的商 （可选）
#说明：模拟了实际的 1/n 的计算过程，除数始终为n,被除数初始为1,numerator = 1，商集合fraction为空，余数集合reminder为空
#执行下面的循环：
# 1. 如果numerator < n，不够除，则numerator *= 10,同时0追加到fraction中，如此循环，直到够除，才跳转到2
# 2. 计算余数c = numerator % n,并将商numerator/n 追加都fraction中，如果c==0，则表示能除尽，不存在重复周期，返回0和fraction，跳转到4。否则跳转到3
# 3. 余数c != 0, 查找reminder,确定c是否出现过，如果出现过，则出现了重复周期，则统计第一次出现（包括这次）直到reminder结束的数字个数cnt。返回cnt和fraction，跳转到4.否则将余数c追加到reminder中，c 赋给numerator,numerator = c,跳转到1，继续循环。
# 4. 结束
#************************************************************************
def div(n) :

	numerator = 1 # 被除数（分子）
	fraction = [] # 商 集合 (如果需要，可以返回这个商)
	reminder = [] # 余数 集合

	while True:

		# Step 1 : 确保 numerator >= n
		while numerator < n :
			numerator *= 10
			fraction.append(0)

		# Step 2 ：计算余数c
		c = numerator % n
		fraction.append(numerator/n)
		if c == 0 :
			return 0 # 能除尽，结束

		# Step 3 ：余数不为0，判断余数c是否出现过
		if c in reminder :
			# 出现过，说明有重复了
			for i, r in enumerate(reminder):
				if r == c :
					return len(reminder) - i # 从上次出现的位置，计算到当前的长度

		# 没有出现过，继续往后除
		reminder.append(c)
		numerator = c


maxIndex, maxCycle = 0, 0
for i in range(1,1000) :
		if div(i) > maxCycle :
			maxIndex = i
			maxCycle = div(i)

print("重复周期最长的数为：", maxIndex)
print("最长的重复周期为：", maxCycle)
```

## 方法2 利用数学定理

利用定理，对每个数n，重复n次 *10 并求余运算，不断往后计算余数，然后记下最后依次的余数，再不断重复*10 并求余运算运算往后找余数，如果发现新的余数与记下的余数相等了，就说明出现了重复周期

> 来自 ProjectEuler 论坛第 1 页第 2 贴 grimbal的答案

```cpp
void ex26()
{
    int maxlen = 0, maxn = 0;

    for(int n = 2 ; n <= 1000 ; n++ ){
        int rest = 1;

        for(int i = 0 ; i < n ; i++ ) rest = (rest*10) % n; // code-1

        int r0 = rest; //code-2
        int len = 0;
        do { //code-3
            rest = (rest*10)%n;
            len++;
        } while( rest != r0 );

        if( len > maxlen ){ //code-4
            maxn = n;
            maxlen = len;
        }
    }

    printf("ex26: %d: %d\n", maxn, maxlen);
}
```

通过求余数，判断余数是否会重复的思路，和方法1是相同的。但是 code-1 行，为什么要使用n，而不是其它数字呢，grimbal的代码没有任何解释，只能自己思考。

rest = (rest*10)%n 的意思就是不断往后找余数，循环n次后，rest就是第n个余数的值。然后 code-2 处记录下了这个值到r0中。code-3的循环与code-1相似，很好理解，就是继续往后找余数，只要发现新找的余数rest和r0相等了，就说明余数重复出现了，也就是出现重复周期。len就记下了两次重复之间的数字个数，即重复周期的大小。code-4 处用来记录下重复周期最大的数。

问题的关键还是在于：code-1为什么用的是n？ 用n的意思就是1/n的余数最多n次就必然会出现循环？这有何根据？

通过搜索，我找到到了如下的定理：

> **[定理](https://zhidao.baidu.com/question/85290154.html)**：任意自然数N，在1/N后得到有限小数或者是无限循环小数且循环字节数小于N-1
>
> **证明：** 1/N 的余数必然属于 (0 ~ N-1)，所以要么能除尽，即有限小数，要么不能除尽，但余数必然会重复，因为余数只能有 1~N-1 可选，所以最多距离 N-1 次，必然会出现重复。也就是循环字节数小于N-1。

看来数学理论对于解题确实太有帮助了！

## 答案
983

## 知识点
定理：任意自然数N，在1/N后，得到有限小数或者是无限循环小数且循环字节数小于N-1