# Problem 14: Longest Collatz sequence

> https://projecteuler.net/problem=14

The following iterative sequence is defined for the set of positive integers:

n → n/2 (n is even)
n → 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.

## 分析
克拉兹猜想 [Collatz Problem](https://planetmath.org/CollatzProblem). 求1百万以下的一个数，以它为起点的Collatz 序列长度最长。

## 方法1 递推+查表

使用map记录下每一个序列的起点，以及序列长度。如 mapChainLen[n]=len，表示以n为起点的序列，长度为len.
> mapChainLen 即为一个 lookup table

- (1) 初始时，mapChainLen[1]=1
- (2) 从 i=2 开始，到 i=1000000 结束，遍历计算每个mapChainLen[i]的值
  * (2.1) 如果 i 为偶数，则  mapChainLen[i] = 1+mapChainLen[i/2]； 因为mapChainLen[0，i-1]的值已经计算过了
  * (2.2) 如果 i 为奇数，则 按照公式 i=3*i+1 继续循环往下找，同时序列长度的值 +1。根据克拉兹猜想，最后都必然收归到1，会跳出循环
  * (2.3) 通过上两步，已经得到了mapChainLen[i]，此时判断mapChainLen[i]是不是最长的，如果是则记录下来
- (3) 循环结束，输出最长的序列的起点的数即可

```cpp
#include <iostream>
#include <map>

std::map<int64_t,int> mapChainLen; // 保存每个数为起点的长度

/*
 * 1: 1 (1)
 * 2: 2->1 (2)
 * 3: 3->10->5->16->8->4->2->1 (8)
 * 4: 4->2->1 (3)
 * 5: 5->16->8->4->2->1 (6)
 * 6: 6->3 (9=1+8)
 * ...
 * 13: 13->40->20->10->5 (10=4+6)
 */

// 计算以 n 为起点的序列的长度
int CalcChainLen(int64_t n) 
{
    int64_t i = n;
    int len = 0;

    while(i>1){
        len ++;
        if(i % 2 == 0){ // 偶数
            if(i/2 < n){ // 小于i的值已经被计算出来了
                len +=  mapChainLen[i/2];
                break;
            }
            i /= 2;
        }
        else{ // 奇数
            i = 3*i + 1;
        }
    }
    return len;
}


int main()
{
    mapChainLen[1] = 1; // 1 的长度记为1，表示1是序列的最后一个数了
    
    int64_t maxStart = 1;
    int maxLen = 1;

    // 依次计算 mapChainLen[i]
    for(int64_t i = 2; i < 1000000; i++){
        mapChainLen[i] = CalcChainLen(i);
        if(mapChainLen[i] > maxLen){
            maxLen = mapChainLen[i];
            maxStart = i;
            //printf("find a large: maxStart:%lld, maxLen:%d\n", maxStart, maxLen);
        }
    }

    printf("maxStart:%lld, maxLen:%d\n", maxStart, maxLen);

    return 0;
}
```

注意：一定要使用int64_t类型


### Golang

```go
package main

import (
	"fmt"
)

var mapChainLen = make(map[int64]int, 0) // 保存每个数为起点的长度

/*
 * 1: 1 (1)
 * 2: 2->1 (2)
 * 3: 3->10->5->16->8->4->2->1 (8)
 * 4: 4->2->1 (3)
 * 5: 5->16->8->4->2->1 (6)
 * 6: 6->3 (9=1+8)
 * ...
 * 13: 13->40->20->10->5 (10=4+6)
 */

// 计算以 n 为起点的序列的长度
func CalcChainLen(n int64) int {
	i, len := n, 0
	for i > 1 {
		len ++
		if i % 2 == 0 {  // 偶数
			if i/2 < n { // 小于i的值已经被计算出来了
				len += mapChainLen[i/2]
				break
			}
			i /= 2
		}else{ // 奇数
			i = 3*i + 1
		}
	}
	return len;
}


func main(){
    mapChainLen[1] = 1 // 1 的长度记为1，表示1是序列的最后一个数了
    maxStart, maxLen := int64(1), 1;

	// 依次计算 mapChainLen[i]
	for i := int64(2); i < 1000000; i++ {
		mapChainLen[i] = CalcChainLen(i);
		if mapChainLen[i] > maxLen {
			maxLen = mapChainLen[i];
			maxStart = i;
			//fmt.Printf("find a large: maxStart:%v, maxLen:%v\n", maxStart, maxLen)
        }
    }
	fmt.Printf("maxStart:%v, maxLen:%v\n", maxStart, maxLen)
}

```

### Python

```python
#coding=utf-8
#author: JarvisChu
#date:2014-3-19

mapChainLen = [] #保存所有start number对应的序列长度
for i in range(0,1000001):
    mapChainLen.append(-1)

mapChainLen[1] = 1
mapChainLen[2] = 2
mapChainLen[4] = 3

max_len = 0
start_number = 0
for i in range(3,1000):
    if mapChainLen[i] == -1: #没计算过
        if i % 2 == 0: #偶数
            mapChainLen[i] = 1 + mapChainLen[int(i/2)]
        else: #奇数
            cnt = 1
            tmp = i
            while tmp != 1:
                if tmp < i:
                    mapChainLen[i] = cnt + mapChainLen[int(tmp)]
                    break
                cnt += 1
                if tmp % 2 == 0: tmp /= 2
                else: tmp = tmp * 3 + 1

    #mapChainLen[i] 此时已获得，比较是不是更大的
    print(i,',', mapChainLen[i] )
    if mapChainLen[i] > max_len:
            max_len = mapChainLen[i]
            start_number = i

print('Starting Number:', start_number, 'Max Len',max_len)
```

## 方法2 方法1的优化版本，计算以某个数为起点的序列长度时，将整个序列中的数的长度都同时计算出来。

以 ` 3: 3->10->5->16->8->4->2->1 (8)` 为例，在计算3为起点的长度时，虽然 10 比 3 大，还没有计算出来，但是从推导过程可以看出 **3的长度比10的长度多1**.
另外，由克拉兹猜想的规律可知，最终所有数都会归为1，那么在整个序列的链中，所有的数字，必然只会出现1次，不然就会出现环，导致链无限长，永不会归一。
根据这样的信息，可知，在计算3的长度时，其实链中的所有数字的长度都可以获得了
如：
- mapChainLen[10] = mapChainLen[3] - 1；
- mapChainLen[5] = mapChainLen[3] - 2；
- mapChainLen[16] = mapChainLen[3] - 3；
- ...

按照这样的思路，我们可以在计算长度的过程中，快速的将 lookup table 丰富起来，减少计算量


### CPP

```cpp
#include <iostream>
#include <map>
#include <vector>

std::map<int64_t,int> mapChainLen; // 保存每个数为起点的长度

/*
 * 1: 1 (1)
 * 2: 2->1 (2)
 * 3: 3->10->5->16->8->4->2->1 (8)
 * 4: 4->2->1 (3)
 * 5: 5->16->8->4->2->1 (6)
 * 6: 6->3 (9=1+8)
 * ...
 * 13: 13->40->20->10->5 (10=4+6)
 */

// 用于保存一个序列中，所有数和其起点的数的长度差值
// 如 3: 3->10->5->16->8->4->2->1 (8)
// Dist 就保存了(10,1), (5,2), (16,3)...
// 这样当3的长度计算出来时，序列中的所有数的长度都能同时计算出来了
typedef struct stDist {
    int64_t n;
    int dist;
}Dist;

// 计算以 n 为起点的序列的长度
// 计算的过程中，会把序列中所有数的长度，一并记录下来
int CalcChainLen(int64_t n) 
{
    int64_t i = n;
    int len = 0;

    std::vector<Dist> vecDists; // 记录n的序列中，所有未计算出长度的数，它和n长度的差值
                                // 比如 n=3时，3: 3->10->5->16->8->4->2->1 (8)
                                // vecDists[0] = (10,1)，表示 mapChainLen[10] = mapChainLen[3] - 1;
                                // vecDists[1] = (5,2)

    while(i>1){
        len ++;

        // 获取序列中的下一个数字next
        int64_t next = (i % 2 == 0) ? i/2 : 3*i + 1;

        // 判断next的 mapChainLen 是否已经计算出来了
        // 如果已经计算出来了，则结束
        std::map<int64_t,int>::iterator it = mapChainLen.find(next);
        if(it != mapChainLen.end()){
            len += mapChainLen[next];
            break;
        }

        // 如果没有计算出来，则可以继续查找下一个数字，但此时可以计算得到 next 的长度了
        Dist d; 
        d.n = next;
        d.dist = len; // mapChainLen[next] = mapChainLen[n] - len;
        vecDists.push_back(d);

        // 继续查找下一个数字
        i = next;
    }

    // 跳出循环时，n的mapChainLen 已获得。则可以通过 vecDists保存的信息，将链上其它数的mapChainLen计算出来
    mapChainLen[n] = len;
    //printf("(%lld, %d)\n", n, len);
    for(int i=0; i< vecDists.size(); i++){
        mapChainLen[vecDists[i].n] = len - vecDists[i].dist;
        //printf("---> (%lld, %d)\n", vecDists[i].n, len - vecDists[i].dist);
    }

    return len;
}


int main()
{
    mapChainLen[1] = 1; // 1 的长度记为1，表示1是序列的最后一个数了
    
    int64_t maxStart = 1;
    int maxLen = 1;

    // 依次计算 mapChainLen[i]
    for(int64_t i = 2; i < 1000000; i++){
        
        int len = 0;
        std::map<int64_t,int>::iterator it = mapChainLen.find(i);
        if(it != mapChainLen.end()){
            len = mapChainLen[i]; // 已经计算过了
        }else{
            len = CalcChainLen(i); // 没有计算过，需要计算
        }

        if(len > maxLen){
            maxLen = len;
            maxStart = i;
            //printf("find a large: maxStart:%lld, maxLen:%d\n", maxStart, maxLen);
        }
    }

    printf("maxStart:%lld, maxLen:%d\n", maxStart, maxLen);

    return 0;
}
```

### Golang

```go
package main

import (
	"fmt"
)

var mapChainLen = make(map[int64]int, 0) // 保存每个数为起点的长度

/*
 * 1: 1 (1)
 * 2: 2->1 (2)
 * 3: 3->10->5->16->8->4->2->1 (8)
 * 4: 4->2->1 (3)
 * 5: 5->16->8->4->2->1 (6)
 * 6: 6->3 (9=1+8)
 * ...
 * 13: 13->40->20->10->5 (10=4+6)
 */

// 用于保存一个序列中，所有数和其起点的数的长度差值
// 如 3: 3->10->5->16->8->4->2->1 (8)
// Dist 就保存了(10,1), (5,2), (16,3)...
// 这样当3的长度计算出来时，序列中的所有数的长度都能同时计算出来了
type Dist struct{
    n int64
    dist int
}

// 计算以 n 为起点的序列的长度
// 计算的过程中，会把序列中所有数的长度，一并记录下来
func CalcChainLen(n int64) int {
	i, len := n, 0
	vecDists := []Dist{} 	// 记录n的序列中，所有未计算出长度的数，它和n长度的差值
							// 比如 n=3时，3: 3->10->5->16->8->4->2->1 (8)
							// vecDists[0] = (10,1)，表示 mapChainLen[10] = mapChainLen[3] - 1;
							// vecDists[1] = (5,2)

    for i>1 {
        len ++

        // 获取序列中的下一个数字next
        next := int64(0)
		if i % 2 == 0 {
			next = i / 2  // 偶数
		} else {
			next = 3*i + 1 // 奇数
		} 

        // 判断next的 mapChainLen 是否已经计算出来了
        // 如果已经计算出来了，则结束
		if val, ok := mapChainLen[next]; ok {
			len += val
            break
		}

		// 如果没有计算出来，则可以继续查找下一个数字，但此时可以计算得到 next 的长度了
		vecDists = append(vecDists, Dist{n:next, dist:len}) // mapChainLen[next] = mapChainLen[n] - len;

		// 继续查找下一个数字
		i = next;
	}

    // 跳出循环时，n的 mapChainLen 已获得。则可以通过 vecDists保存的信息，将链上其它数的mapChainLen计算出来
    mapChainLen[n] = len
	for _, d := range vecDists {
		mapChainLen[d.n] = len - d.dist;
	}

    return len
}


func main() {
	mapChainLen[1] = 1 // 1 的长度记为1，表示1是序列的最后一个数了
	maxStart, maxLen := int64(1), 1
	
	// 依次计算 mapChainLen[i]
	for i := int64(2); i < 1000000; i++ {
		len := 0
		if val, ok := mapChainLen[i]; ok {
			len = val // 已经计算过了
		}else{
			len = CalcChainLen(i) // 没有计算过，需要计算
		}
		
		if len > maxLen {
            maxStart, maxLen = i, len
		}
	}

    fmt.Printf("maxStart:%v, maxLen:%v\n", maxStart, maxLen)
}

```

### Python

```python
mapChainLen = {} # 保存每个数为起点的长度

#########
# 1: 1 (1)
# 2: 2->1 (2)
# 3: 3->10->5->16->8->4->2->1 (8)
# 4: 4->2->1 (3)
# 5: 5->16->8->4->2->1 (6)
# 6: 6->3 (9=1+8)
# ...
# 13: 13->40->20->10->5 (10=4+6)
#########

# 用于保存一个序列中，所有数和其起点的数的长度差值
# 如 3: 3->10->5->16->8->4->2->1 (8)
# Dist 就保存了(10,1), (5,2), (16,3)...
# 这样当3的长度计算出来时，序列中的所有数的长度都能同时计算出来了

class Dist:
    def __init__(self, n, dist):
        self.n = n
        self.dist = dist

# 计算以 n 为起点的序列的长度
# 计算的过程中，会把序列中所有数的长度，一并记录下来
def CalcChainLen(n) : 
    i, len = n, 0
    vecDists = [] # 记录n的序列中，所有未计算出长度的数，它和n长度的差值
                  # 比如 n=3时，3: 3->10->5->16->8->4->2->1 (8)
                  # vecDists[0] = (10,1)，表示 mapChainLen[10] = mapChainLen[3] - 1;
                  # vecDists[1] = (5,2)

    while i>1 :
        len = len + 1

        # 获取序列中的下一个数字next
        next = (i/2) if (i % 2 == 0) else ( 3*i + 1)
        
        # 判断next的 mapChainLen 是否已经计算出来了
        # 如果已经计算出来了，则结束
        if next in mapChainLen:
            len = len + mapChainLen[next]
            break
        
        # 如果没有计算出来，则可以继续查找下一个数字，但此时可以计算得到 next 的长度了
        vecDists.append(Dist(next, len)) # mapChainLen[next] = mapChainLen[n] - len
        
        # 继续查找下一个数字
        i = next
    
    # 跳出循环时，n的 mapChainLen 已获得。则可以通过 vecDists保存的信息，将链上其它数的mapChainLen计算出来
    mapChainLen[n] = len
    for d in vecDists :
        mapChainLen[d.n] = len - d.dist
    
    return len


if __name__=="__main__":
    mapChainLen[1] = 1 # 1 的长度记为1，表示1是序列的最后一个数了
    maxStart, maxLen = 1, 1
    
    # 依次计算 mapChainLen[i]
    for i in range(2, 1000001) :
        len = 0
        if i in mapChainLen:
            len = mapChainLen[i]  # 已经计算过了
        else :
            len = CalcChainLen(i) # 没有计算过，需要计算
            
        if len > maxLen :
            maxStart, maxLen = i, len

    print("maxStart:", maxStart, ", maxLen:",maxLen)
```

## 答案
837799
