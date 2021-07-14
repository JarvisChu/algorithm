# Problem 51: Prime digit replacements

> https://projecteuler.net/problem=51

By replacing the 1<sup>st</sup> digit of the 2-digit number *3, it turns out that six of the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3<sup>rd</sup> and 4<sup>th</sup> digits of 56**3 with the same digit, this 5-digit number is the first example having seven primes among the ten generated numbers, yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of this family, is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) with the same digit, is part of an eight prime value family.

## 分析

使用同样的数字，替换一个数中的某些位（不一定是相邻位），可以生成一组质数，这组质数称为一个 family. 如果这组质数包含 n 个质数，则称为 n prime value family.

找到最小的一个质数，它可以生成一个 8 prime value family。

## 方法

从 n=11 往上遍历，对每一个n，做如下处理：

- (1) 分解得到其所有位上的数字 digits[]，如 n = 123, 则 digits = [1,2,3]
- (2) 然后，获取从 digits.size() 个位置中，选出 cnt = 1~digits.size() 个位置的选法，这个cnt个位置用于后面做0~9的替换，通过 getChoices(digits.size(), cnt) 返回所有的选法。如 n = 123, digits = [1,2,3]，digits.size() = 3， getChoices(3, 1) 表示从3个位置中，选择1个位置，返回 [[0],[1],[2]]，表示有三种选法，即分别选第0位，第1位，第2位。getChoices(3, 2) 表示从3个位置中，选择2个位置，返回 [[0,1],[0,2],[1,2]]，表示有三种选法，即分别选第0位和第1位，第0位和第2位，第1位和第2位。
- (3) 对于(2) 中获得每一种选法，使用 0~9 来替换选中的位置，生成一个family，使用replace(digits, choice) 函数实现。如 n=123, replace([1,2,3], [0,1]) 表示将 digits的第0位和第1位 依次使用 0~9 替换，返回 113,223,333,443,553,663,773,883,993。注意：003 需要被剔除。
- (4) 判断返回的family 是否包含8个质数，如果包含，则找到了答案，结束


这里的核心点在于：**getChoices(len,cnt)** 的实现方法，即获取从 len 个位置中，选出 cnt 个位置的所有选法。

方法(1)： 可以使用递归的方式来实现 getChoices
方法(2)： 也可以使用 std::next_permutaion 来实现; 从 len 中选择 cnt 个位置，相当于对数组 [0,0,0...1,1,1] 做全排列

> 对每个数，都需要调用 getChoices，所以可以事先把getChoices的结果保存下来，需要时，直接使用，而不是每次都调用。
> 本题解题速度还可以，故没有用这种优化。

### CPP

**方法(1) 使用递归实现的 getChoices**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

bool isPrime(int n)
{
    if(n <= 1 ) return false;
    if(n == 2 || n == 3) return true;
    if(n % 2 == 0) return false;
    if(n % 6 != 1 && n % 6 != 5 ) return false;
    for(int i=5; i * i <= n; i++){
        if( n % i == 0 ) return false;
    }
    return true;
}


// 从 flag[start~len) 中，选择 cnt 个位置，填充为1
// choices: 如果找到了一种选法，则保存到 choices 中
// flag: 待填充的数组，flag[i] = 1，表示选中 i 位置，0 表示不选择该位置
// len: flag数组的长度
// start: 开始的位置
// cnt: 要填充的个数
void select(std::vector<std::vector<int> >& choices, int flag[], int len, int start, int cnt) 
{
    // 找到了一种选法，保存到 choices 中
    if(cnt == 0){
        std::vector<int> choice;
        for(int i = 0; i < len; i++){
            if(flag[i] == 1) choice.push_back(i);
        }
        choices.push_back(choice);
        return;
    }

    // flag 已经遍历完，直接返回
    if(start >= len) return;

    // 填充某个中间位置，分两种情况：填充和不填充

    // (1) 填充
    flag[start] = 1;
    select(choices, flag, len, start + 1, cnt - 1);

    // (2) 不填充
    for(int i = start; i < len; i++){ // 重置(1)中的修改
        flag[i] = 0;
    }
    select(choices, flag, len, start + 1, cnt);

    return;
}


// select cnt from len
// 返回所有的可能的选择方法
std::vector<std::vector<int> > getChoices(int len, int cnt)
{
    std::vector<std::vector<int> > choices;
    int flag[100] = {0};
    select(choices, flag, len, 0, cnt);
    return choices;
}

// 分别用 0~9 替换 digits 中 choice 包含的位置，获得一组数字
std::vector<int> replace(std::vector<int> digits, std::vector<int> choice)
{
    std::vector<int> family;
    for(int digit = 0; digit <= 9; digit++ ){

        for(int k = 0; k < choice.size(); k++){
            digits[ choice[k] ] = digit;
        }

        // convert digits to int
        int v = 0;
        for(int k = 0; k < digits.size(); k++){
            v *= 10;
            v += digits[k];
        }

        // 如果 0 出现在开头，则位数不同。所以需要剔除 0 出现在开头的情况
        if(digit == 0 && choice[0] == 0) continue;

        family.push_back(v);
    }

    return family;
}

int main()
{   
    // 从小到大遍历所有的质数，判断能否替换其中几位的数字，生成一组质数
    for(int n = 11; ; n++){
        if(!isPrime(n)) continue;

        // 分解得到 i 的每一位数字
        std::vector<int> digits;
        int cpy = n;
        while(cpy > 0){
            digits.push_back( cpy % 10 );
            cpy /= 10;
        }

        // 分解得到的是逆序的。需要再逆序回来
        std::reverse(digits.begin(), digits.end());

        // 依次替换 digits 中 1 ~ digits.size() 个位置，判断能否生成 8 prime value family
        for(int cnt = 1; cnt <= digits.size(); cnt++){

            // 替换 cnt 个位置
            // 从 digits.size() 个位置中，选 cnt 个位置，使用 0~9 替换；即 select cnt from digits.size()
            std::vector<std::vector<int> > choices = getChoices(digits.size(), cnt);
            for(int h = 0; h < choices.size(); h++){

                std::vector<int> family = replace(digits, choices[h]);
                int primeCnt = 0;
                for(int i = 0; i < family.size(); i++){
                    if(isPrime(family[i])) primeCnt ++;
                }

                if( primeCnt == 8){
                    printf("find family: ");
                    for(int i = 0; i < family.size(); i++){
                       if(isPrime(family[i])) printf("%d ", family[i]);
                    }
                    printf("\n");
                    return 0;
                }
            }  
        }
    }

    return 0;
}
```

**方法(2) 使用 std::next_permutaion 实现 getChoices**

替换方法(1) 中的 getChoices 函数即可

```cpp
// select cnt from len
// 返回所有的可能的选择方法
std::vector<std::vector<int> > getChoices(int len, int cnt)
{
    // 从 len 中选择 cnt 个位置，相当于对数组 [0,0,0...1,1,1] 做全排列
    std::vector<std::vector<int> > choices;

    // 总长 len, 末尾 cnt 个 1，开头 len-cnt 个 0
    std::vector<int> flag;
    for(int i = 0; i < len; i++){
        if( i < len-cnt ) flag.push_back(0);
        else{
            flag.push_back(1);
        }
    }

    // 对 flag 进行全排列
    do{
        std::vector<int> choice;
        for(int i = 0; i < len; i++){
            if(flag[i] == 1) choice.push_back(i);
        }
        choices.push_back(choice);
    }while ( std::next_permutation(flag.begin(), flag.end()));

    return choices;
}
```

### Golang

**方法(1) 使用递归实现的 getChoices**

```go
package main

import (
	"fmt"
)

func isPrime(n int) bool {
	if n <= 1 {
		return false
	}

	if n == 2 || n == 3 {
		return true
	}

	if n%2 == 0 {
		return false
	}

	if n%6 != 1 && n%6 != 5 {
		return false
	}

	for i := 5; i*i <= n; i++ {
		if n%i == 0 {
			return false
		}
	}

	return true
}

// 从 flag[start~len) 中，选择 cnt 个位置，填充为1
// choices: 如果找到了一种选法，则保存到 choices 中
// flag: 待填充的数组，flag[i] = 1，表示选中 i 位置，0 表示不选择该位置
// len: flag数组的长度
// start: 开始的位置
// cnt: 要填充的个数
func select1(choices *[][]int, flag []int, len, start, cnt int) {

	// 找到了一种选法，保存到 choices 中
	if cnt == 0 {
		var choice []int
		for i := 0; i < len; i++ {
			if flag[i] == 1 {
				choice = append(choice, i)
			}
		}
		*choices = append(*choices, choice)
		//fmt.Println("append:", choices)
		return
	}

	// flag 已经遍历完，直接返回
	if start >= len {
		return
	}

	// 填充某个中间位置，分两种情况：填充和不填充

	// (1) 填充
	flag[start] = 1
	select1(choices, flag, len, start+1, cnt-1)

	// (2) 不填充
	for i := start; i < len; i++ { // 重置(1)中的修改
		flag[i] = 0
	}
	select1(choices, flag, len, start+1, cnt)

	return
}

// select cnt from len
// 返回所有的可能的选择方法
func getChoices(len, cnt int) [][]int {
	var choices [][]int
	var flag []int
	for i := 0; i < len; i++ {
		flag = append(flag, 0)
	}
	select1(&choices, flag, len, 0, cnt)
	//fmt.Println("getChoice: ", choices)
	return choices
}

// 分别用 0~9 替换 digits 中 choice 包含的位置，获得一组数字
func replace(digits []int, choice []int) []int {

	var cpy []int
	cpy = append(cpy, digits...)

	var family []int
	for digit := 0; digit <= 9; digit++ {

		for k := 0; k < len(choice); k++ {
			cpy[choice[k]] = digit
		}

		// convert digits to int
		v := 0
		for k := 0; k < len(cpy); k++ {
			v *= 10
			v += cpy[k]
		}

		// 如果 0 出现在开头，则位数不同。所以需要剔除 0 出现在开头的情况
		if digit == 0 && choice[0] == 0 {
			continue
		}

		family = append(family, v)
	}

	return family
}

func main() {

	// 从小到大遍历所有的质数，判断能否替换其中几位的数字，生成一组质数
	for n := 11; ; n++ {
		if !isPrime(n) {
			continue
		}

		// 分解得到 i 的每一位数字
		var digits []int
		cpy := n
		for cpy > 0 {
			digits = append(digits, cpy%10)
			cpy /= 10
		}

		// 分解得到的是逆序的。需要再逆序回来
		for i := 0; i < len(digits)/2; i ++ {
			digits[i],digits[len(digits)-i-1] = digits[len(digits)-i-1], digits[i]
		}

		// 依次替换 digits 中 1 ~ len(digits) 个位置，判断能否生成 8 prime value family
		for cnt := 1; cnt <= len(digits); cnt++ {

			// 替换 cnt 个位置
			// 从 len(digits) 个位置中，选 cnt 个位置，使用 0~9 替换；即 select cnt from len(digits)
			choices := getChoices(len(digits), cnt)
			for h := 0; h < len(choices); h++ {
				family := replace(digits, choices[h])
				primeCnt := 0
				for i := 0; i < len(family); i++ {
					if isPrime(family[i]) {
						primeCnt++
					}
				}

				if primeCnt == 8 {
					fmt.Printf("find family: ")
					for i := 0; i < len(family); i++ {
						if isPrime(family[i]) {
							fmt.Printf("%d ", family[i])
						}
					}
					fmt.Println("")
					return
				}
			}
		}
	}
}
```

**方法(2) 使用 nextPermutaion 实现 getChoices**

```go

// 获取perm的下一个序列
// std::next_permutation
// 未使用
func nextPermutation(perm []int) bool {
	// 长度不超过1，直接返回
	if len(perm) <= 1 {
		return false
	}

	// 从后往前，找到第一个 perm[i] < perm[i+1]
	// e.g perm=1238[57]64, perm[i]=5
	i := -1
	for i = len(perm) - 2; i >= 0; i-- {
		if perm[i] < perm[i+1] {
			break
		}
	}

	// 找不到，说明整个 perm 是递减的，已是最大，没有next
	if i == -1 {
		return false
	}

	// 从后往前 [末尾, i+1]，找到第一个比 perm[i] 大的数，然后交换
	// e.g. perm=1238[5]7[6]4, 交换 5 和 6
	for k := len(perm) - 1; k >= i+1; k-- {
		if perm[k] > perm[i] {
			// 交换 perm[k] 和 perm[i]
			perm[k], perm[i] = perm[i], perm[k] // golang 支持这样交换
			break
		}
	}

	// i+1 到末尾目前是降序的，改为升序
	// e.g perm=12386[754] => perm=12386[457]
	for k := i + 1; k < len(perm); k++ {
		last := len(perm) + i - k
		if k >= last {
			break
		}

		// 交换 perm[k] 和 perm[last]
		perm[k], perm[last] = perm[last], perm[k] // golang 支持这样交换
	}

	return true
}

// select cnt from len
// 返回所有的可能的选择方法
func getChoices(len, cnt int) [][]int {

	// 从 len 中选择 cnt 个位置，相当于对数组 [0,0,0...1,1,1] 做全排列
	var choices [][]int

	// 总长 len, 末尾 cnt 个 1，开头 len-cnt 个 0
	var flag []int
	for i := 0; i < len; i++ {
		if i < len-cnt {
			flag = append(flag, 0)
		} else {
			flag = append(flag, 1)
		}
	}

	// 对 flag 进行全排列
	for ok := true; ok; ok = nextPermutation(flag) {
		var choice []int
		for i := 0; i < len; i++ {
			if flag[i] == 1 {
				choice = append(choice, i)
			}
		}
		choices = append(choices, choice)
	}

	return choices
}
```

### Python

```python
import math

def isPrime(n): 
    if n <= 1 : return False
    if n == 2 or n == 3 : return True
    if n % 2 == 0 : return False

    # 关于质数分布的规律：大于等于5的质数一定和6的倍数相邻
    # 即大于等于5的质数一定是 6x-1 和 6x+1，6x+2 ~ 6x+4 一定不是质数
    # 即大于等于5的质数一定满足 n%6==1 or n%6==5
    # https://blog.csdn.net/songyunli1111/article/details/78690447
    if n % 6 != 1 and n % 6 != 5 : return False

    # 从 [5, sqrt(n)] 遍历寻找是否是其因数
    for i in range(5, int(math.sqrt(n)) + 1):
        if n % i == 0 : return False

    return True

# 获取perm的下一个序列
# std::next_permutation
def nextPermutation(perm) :
	# 长度不超过1，直接返回
	if len(perm) <= 1 :
		return False

	# 从后往前，找到第一个 perm[i] < perm[i+1]
	# e.g perm=1238[57]64, perm[i]=5
	i = len(perm) - 2
	while i >= 0 : 
		if perm[i] < perm[i+1] :
			break
		i = i - 1

	# 找不到，说明整个 perm 是递减的，已是最大，没有next
	if i == -1 :
		return False

	# 从后往前 [末尾, i+1]，找到第一个比 perm[i] 大的数，然后交换
	# e.g. perm=1238[5]7[6]4, 交换 5 和 6
	for k in range(len(perm) - 1, i, -1) :
		if perm[k] > perm[i] :
			# 交换 perm[k] 和 perm[i]
			perm[k], perm[i] = perm[i], perm[k] # python 支持这样交换
			break

	# i+1 到末尾目前是降序的，改为升序
	# e.g perm=12386[754] => perm=12386[457]
	for k in range(i + 1, len(perm)) :
		last = len(perm) + i - k
		if k >= last :
			break

		# 交换 perm[k] 和 perm[last]
		perm[k], perm[last] = perm[last], perm[k] # python 支持这样交换

	return True

# select cnt from len
# 返回所有的可能的选择方法
def getChoices(len, cnt) :
    # 从 len 中选择 cnt 个位置，相当于对数组 [0,0,0...1,1,1] 做全排列
    choices = []
    
    # 总长 len, 末尾 cnt 个 1，开头 len-cnt 个 0
    flag = []
    for i in range(0, len) :
        if i < len-cnt:
            flag.append(0)
        else:
            flag.append(1)
    
    # 对 flag 进行全排列
    while True:
        choice = []
        for i in range(0, len):
            if flag[i] == 1:
                choice.append(i)
        choices.append(choice)

        if not nextPermutation(flag):
            break
    return choices


def replace(n, choice):
    
    family = []
    chars = ['0', '1','2','3','4','5','6','7','8','9']
    for digit in chars:
        digits = list(str(n))
        for k in range(0, len(choice)):
            #print(digits, k, choice[k])
            digits[ choice[k] ] = digit
        
        f = int(''.join(digits))

        if len(str(f)) < len(digits):
            continue

        family.append(f)
    return family

# 从小到大遍历所有的质数，判断能否替换其中几位的数字，生成一组质数
n = 11
while True:
    if not isPrime(n):
        n += 2
        continue
    sz = len(str(n))
    
    # 依次替换 n 中 1 ~ sz 个位置，判断能否生成 8 prime value family
    for cnt in range(1, sz+1):
        # 替换 cnt 个位置
        # 从 sz 个位置中，选 cnt 个位置，使用 0~9 替换；即 select cnt from sz
        choices = getChoices(sz, cnt)
        #print("n=", n, "cnt=", cnt, "choices=", choices)
        for c in choices:
            family = replace(n, c)
            #print("family", family)
            primeCnt = 0
            for f in family:
                if isPrime(f):
                    primeCnt = primeCnt + 1
            #print("primeCnt", primeCnt)
            if primeCnt == 8 :
                print("find family: ", end="")
                for f in family:
                    if isPrime(f):
                        print(f, end=" ")
                print("")
                exit(0)
    n += 2
```

## 答案
121313 

family: 121313 222323 323333 424343 525353 626363 828383 929393