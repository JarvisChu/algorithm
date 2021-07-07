# Problem 31: Coin sums

> https://projecteuler.net/problem=31

In the United Kingdom the currency is made up of pound (£) and pence (p). There are eight coins in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, £1 (100p), and £2 (200p).

It is possible to make £2 in the following way:

1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
How many different ways can £2 be made using any number of coins?

## 分析

找钱问题。已知的面值为1，2，5，10，50，100，200，用这些面值去凑200，求有多少种凑法。

## 方法 递归求解

优先使用大面值再用小面值，依次去寻找。

先用 200面值 去凑 200，如果用 0 个200面值，则问题转换为再用100面值 去凑剩下的200-0*200=200。如果用1个200面值，则问题转换为再用100面值 去凑剩下的200-1*200=0 。可见这里面存在一个递归关系。

使用value[8] 保存记录面值1，2，5…，200；cnt[8] 保存对应的每种面值使用的数量；solutions用来保存可以凑到200的方案总数。Check(int v,int remaining) 函数实现递归关系，它使用面值value[v]去凑钱remaining，依次使用i= 0~remaining/value[v] 个该面值，然后递归调用Check(v-1, remaining-i*value[v] )去凑剩下的钱。如果v==0，说明要使用最后一种面值，即面值1去凑，此时直接用remaining个面值1即可，然后输出结果。如果remaining==0，说明前面已经凑到200，不用再凑了，将cnt[0~v] 设为0 ，然后输出结果即可。


### CPP

```cpp
#include <stdio.h>

int value[8] = {1,2,5,10,20,50,100,200}; //面值 排序 v: 0 ~ 7
int cnt[8] = {0,0,0,0,0,0,0,0}; //数量
int solutions = 0; //多少种方案

/************************************************************************
* 使用面值为value[v]的钱，去凑剩下的钱remaining，remaining初始值为200
************************************************************************/
int Check(int v,int remaining)
{
    int i;

    // 用面值 1 去凑
    if(v == 0) { // 用面值为value[0] = 1 去凑remaining
        cnt[v] = remaining; // 共需要 remaining/cnt[v] = remaining 个
        for (i=0;i<8;i++) printf("%3d",cnt[i]);//输出方案
        printf("\n");
        solutions ++; //方案数++
        return solutions;
    }

    // 不剩钱了
    else if (remaining== 0){
        for(i=0;i<=v;i++) cnt[i] = 0; // 小面值的都不需要了
        for (i=0;i<8;i++) printf("%3d",cnt[i]);//输出方案
        printf("\n");
        solutions ++; //方案数++
        return solutions;
    }

    //当前面值value[v] != 1,先用 value[v]凑，剩下的递归使用value[v-1]去凑
    else{
        for (i=0; i <= remaining/value[v]; i++){
            cnt[v] = i;
            Check(v-1, remaining - i*value[v] ); //递归，调用更小面值去凑
        }
    }
    return solutions;
}

int main()
{
    printf("%d\n",Check(7,200)); //从使用value[7]==200开始，去凑200
    return 0;
}
```

### Golang

```go
package main

import "fmt"

var value = [8]int{1, 2, 5, 10, 20, 50, 100, 200} //面值 排序 v: 0 ~ 7
var cnt = [8]int{0, 0, 0, 0, 0, 0, 0, 0}          //数量
var solutions = 0                                 //多少种方案

/************************************************************************
* 使用面值为value[v]的钱，去凑剩下的钱remaining，remaining初始值为200
************************************************************************/
func Check(v, remaining int) int {

	// 用面值 1 去凑
	if v == 0 { // 用面值为value[0] = 1 去凑remaining
		cnt[v] = remaining       // 共需要 remaining/cnt[v] = remaining 个
		for i := 0; i < 8; i++ { //输出方案
			fmt.Printf("%3d", cnt[i])
		}
		fmt.Println("")
		solutions++ //方案数++
		return solutions
	}

	// 不剩钱了
	if remaining == 0 {
		for i := 0; i <= v; i++ {
			cnt[i] = 0 // 小面值的都不需要了
		}
		for i := 0; i < 8; i++ { //输出方案
			fmt.Printf("%3d", cnt[i])
		}
		fmt.Println("")
		solutions++ //方案数++
		return solutions
	}

	//当前面值value[v] != 1,先用 value[v]凑，剩下的递归使用value[v-1]去凑
	for i := 0; i <= remaining/value[v]; i++ {
		cnt[v] = i
		Check(v-1, remaining-i*value[v]) //递归，调用更小面值去凑
	}
	return solutions
}

func main() {
	fmt.Println(Check(7, 200)) //从使用value[7]==200开始，去凑200
}

```


### Python

```python
#coding=utf8
value = [1,2,5,10,20,50,100,200] #面值
cnt = [0,0,0,0,0,0,0,0] #每种面值使用的数量
solutions = 0 #方案的总数

def Check(v,remaining):
    global solutions
    if v == 0: #使用面值1
        cnt[v] = remaining
        #print cnt
        solutions += 1
        return solutions
    elif remaining== 0: #钱已经凑齐
        for i in range(0,v): #小面值的不需要使用了
            cnt[i] = 0
            #print cnt
        solutions += 1
        return solutions
    else: #尝试使用value[v]去凑
        for i in range(0, int(remaining/value[v]) + 1):
            cnt[v] = i #面值value[v]使用i个
            Check(v - 1, remaining- i * value[v] ) #用更小面值去凑剩下的钱
    return solutions

print(Check(7,200)) #从使用value[7]==200开始，去凑200
```

## 答案
73682