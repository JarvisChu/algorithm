# Problem 15: Lattice paths

> https://projecteuler.net/problem=15

Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/project_euler_15_1.png)

How many such routes are there through a 20×20 grid?

## 分析
20x20的方格，从左上角到右下角的路径条数。由题可知，路径的方向要么向右，要么向下。

## 方法1 递归

https://blog-1252824460.cos.ap-nanjing.myqcloud.com/project_euler_15_2.png


如图，对方格建立坐标系，左上角为原点(0,0)。path(w, h) 表示从原点到(w, h)点的路径总条数。则path(20, 20)就是问题的解。

对于点(w, h)，它只能由(w-1, h)和(w, h-1)两个点到达。所以path(w, h) = path(w-1, h) + path(w, h-1)，这就是递推公式。已知path(0,0) = 1，path(1,1) = 2 。

### CPP

```cpp
#include <stdio.h>
#include <stdlib.h>

/************************************************************************
* 递归方法
************************************************************************/
/*返回宽为w,高为h的方格的路径条数*/
long long path(int w,int h)
{
    if(h <0 || w <0) return 0; //走出了方格
    if(h ==0 || w ==0) return 1; //方格边缘，只有一种走法
    if(h==1 && w==1) return 2; // 1 x 1的方格，两条路径

    return path(w-1,h) + path(w,h-1);  // 其它位置，递归
}

int main()
{
    printf("%lld\n",path(20,20));
    return 0;
}
```

算法很简单，但是运行时间太久，所以基本上不可取，golang/python实现会更慢，直接忽略该方法了

## 方法2 递推

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/project_euler_15_3.png)

方格是正方形。左上角为坐标原点(0,0)，path_cnt[w][h]表示从原点到(w,h)的路径数。path_cnt[20][20] 就是问题的解。

> w 横向，h 纵向

从(0, 0)点开始，不断往外一圈一圈扩散，circle = 1时，第一圈上的所有点（绿色点）的path_cnt可以通过前一圈的所有点的值推导出来。circle=2时，第二圈上的所有点（红色点）的path_cnt可以通过前一圈的所有点(绿点)的值推导出来，如此类推，直到circle=20，就可以得到path_cnt[20][20],即问题的解。

```
cycle = 0,1,2,3,4 时的情况
0  1  2  3  4
1  1  2  3  4
2  2  2  3  4
3  3  3  3  4
4  4  4  4  4
```

- 1. 最上面的边(h=0)，其上所有点的路径条数为1，只能沿边走，即 path_cnt[0~w][0] = 1
- 2. 最左边的边(w=0)，其上所有点的路径条数为1，只能沿边走，即 path_cnt[0][0~h] = 1
- 3. 对于每一圈 cycle 上的所有点：
   * 3.1 除交叉点 [cycle,cycle] 之外，横着的一排点( [1~cycle-1, cycle] )，可以从左向右依次计算其值，每个点的值等于它的左边点+上边点，左边点在前一步已经计算出来，上边点在上一圈已经计算出来，都是已知，所以可以直接得到当前点的值，即 **path_cnt[i][cycle] = path_cnt[i-1][cycle] + path_cnt[i][cycle-1]**
   * 3.2 除交叉点 [cycle,cycle] 之外，竖着的一排点( [cycle, 1~cycle-1] ), 可以从上往下依次计算其值，每个点的值等于它的左边点+上边点，左边点在上一圈中已经计算出来，上边点在前一步已经计算出来，都是已知，所以可以直接得到当前点的值，即 **path_cnt[cycle][i] = path_cnt[cycle-1][i] + path_cnt[cycle][i-1]**
   * 3.3 对于交叉点 [cycle,cycle], 在3.1 和3.2 中，已经计算出其左边点和上边点的值了，也就可以直接得到它的值 **path_cnt[cycle][cycle] = path_cnt[cycle-1][cycle] + path_cnt[cycle][cycle-1]**


### CPP

```cpp
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

/************************************************************************
* 递推方法
************************************************************************/

//递推方法
long long path(int size)
{
    long long path_cnt[MAX_SIZE+1][MAX_SIZE+1]; // path[w][h] 表示(w,h) 点的路径条数

    /*
    从(0,0)点向外，一圈一圈的算
    cycle = 0,1,2,3,4 时的情况

    0  1  2  3  4
    1  1  2  3  4
    2  2  2  3  4
    3  3  3  3  4
    4  4  4  4  4
    */

    // 1. 最上面的边(h=0)，其上所有点的路径条数为1，只能沿边走，即 path_cnt[0~w][0] = 1
    for(int i = 0; i <= size; i ++) path_cnt[i][0] = 1;

    // 2. 最左边的边(w=0)，其上所有点的路径条数为1，只能沿边走，即 path_cnt[0][0~h] = 1
    for(int i = 0; i <= size; i ++) path_cnt[0][i] = 1;

    // 3. 对于每一圈 cycle 上的所有点：
    for(int cycle = 1; cycle <= size; cycle ++){
        // 3.1 除交叉点 [cycle,cycle] 之外，横着的一排点( [1~cycle-1, cycle] )，可以从左向右依次计算其值，每个点的值等于它的左边点+上边点，
        //     左边点在前一步已经计算出来，上边点在上一圈已经计算出来，都是已知，所以可以直接得到当前点的值，
        //     即 path_cnt[i][cycle] = path_cnt[i-1][cycle] + path_cnt[i][cycle-1]
        for(int i = 1; i < cycle; i++) path_cnt[i][cycle] = path_cnt[i-1][cycle] + path_cnt[i][cycle-1];

        // 3.2 除交叉点 [cycle,cycle] 之外，竖着的一排点( [cycle, 1~cycle-1] ), 可以从上往下依次计算其值，每个点的值等于它的左边点+上边点，
        //     左边点在上一圈中已经计算出来，上边点在前一步已经计算出来，都是已知，所以可以直接得到当前点的值，
        //     即 path_cnt[cycle][i] = path_cnt[cycle-1][i] + path_cnt[cycle][i-1]
        for(int i = 1; i < cycle; i++) path_cnt[cycle][i] = path_cnt[cycle-1][i] + path_cnt[cycle][i-1];

        // 3.3 对于交叉点 [cycle,cycle], 在3.1 和3.2 中，已经计算出其左边点和上边点的值了，
        //     也就可以直接得到它的值 path_cnt[cycle][cycle] = path_cnt[cycle-1][cycle] + path_cnt[cycle][cycle-1]
        path_cnt[cycle][cycle] = path_cnt[cycle-1][cycle] + path_cnt[cycle][cycle-1];
    }

    return path_cnt[size][size];
}

int main()
{
    printf("%lld\n",path(20));
    return 0;
}
```

速度极快，几乎是运行的瞬间结果就出来了。


### Golang

```go
package main

import (
	"fmt"
)

const MAX_SIZE = 20

/************************************************************************
* 递推方法
************************************************************************/

//递推方法
func path(size int) int64 {

	path_cnt := [MAX_SIZE + 1][MAX_SIZE + 1]int64{} // path[w][h] 表示(w,h) 点的路径条数

	/*
	   从(0,0)点向外，一圈一圈的算
	   cycle = 0,1,2,3,4 时的情况

	   0  1  2  3  4
	   1  1  2  3  4
	   2  2  2  3  4
	   3  3  3  3  4
	   4  4  4  4  4
	*/

	// 1. 最上面的边(h=0)，其上所有点的路径条数为1，只能沿边走，即 path_cnt[0~w][0] = 1
	for i := 0; i <= size; i++ {
		path_cnt[i][0] = 1
	}

	// 2. 最左边的边(w=0)，其上所有点的路径条数为1，只能沿边走，即 path_cnt[0][0~h] = 1
	for i := 0; i <= size; i++ {
		path_cnt[0][i] = 1
	}

	// 3. 对于每一圈 cycle 上的所有点：
	for cycle := 1; cycle <= size; cycle++ {
		// 3.1 除交叉点 [cycle,cycle] 之外，横着的一排点( [1~cycle-1, cycle] )，可以从左向右依次计算其值，每个点的值等于它的左边点+上边点，
		//     左边点在前一步已经计算出来，上边点在上一圈已经计算出来，都是已知，所以可以直接得到当前点的值，
		//     即 path_cnt[i][cycle] = path_cnt[i-1][cycle] + path_cnt[i][cycle-1]
		for i := 1; i < cycle; i++ {
			path_cnt[i][cycle] = path_cnt[i-1][cycle] + path_cnt[i][cycle-1]
		}

		// 3.2 除交叉点 [cycle,cycle] 之外，竖着的一排点( [cycle, 1~cycle-1] ), 可以从上往下依次计算其值，每个点的值等于它的左边点+上边点，
		//     左边点在上一圈中已经计算出来，上边点在前一步已经计算出来，都是已知，所以可以直接得到当前点的值，
		//     即 path_cnt[cycle][i] = path_cnt[cycle-1][i] + path_cnt[cycle][i-1]
		for i := 1; i < cycle; i++ {
			path_cnt[cycle][i] = path_cnt[cycle-1][i] + path_cnt[cycle][i-1]
		}

		// 3.3 对于交叉点 [cycle,cycle], 在3.1 和3.2 中，已经计算出其左边点和上边点的值了，
		//     也就可以直接得到它的值 path_cnt[cycle][cycle] = path_cnt[cycle-1][cycle] + path_cnt[cycle][cycle-1]
		path_cnt[cycle][cycle] = path_cnt[cycle-1][cycle] + path_cnt[cycle][cycle-1]
	}

	return path_cnt[size][size]
}

func main() {
	fmt.Println(path(20))
}
```

### Python

```python

#递推方法

# path[w][h] 表示(w,h) 点的路径条数
path_cnt = [ [ 0 for x in range(0,21) ] for y in range(0,21) ] 

'''
从(0,0)点向外，一圈一圈的算
cycle = 0,1,2,3,4 时的情况

0  1  2  3  4
1  1  2  3  4
2  2  2  3  4
3  3  3  3  4
4  4  4  4  4
'''


# 1. 最上面的边(h=0)，其上所有点的路径条数为1，只能沿边走，即 path_cnt[0~w][0] = 1
for i in range (0, 21):
    path_cnt[i][0] = 1

# 2. 最左边的边(w=0)，其上所有点的路径条数为1，只能沿边走，即 path_cnt[0][0~h] = 1
for i in range (0, 21):
    path_cnt[0][i] = 1

# 3. 对于每一圈 cycle 上的所有点：
for cycle in range(1, 21):
    # 3.1 除交叉点 [cycle,cycle] 之外，横着的一排点( [1~cycle-1, cycle] )，可以从左向右依次计算其值，每个点的值等于它的左边点+上边点，
    #     左边点在前一步已经计算出来，上边点在上一圈已经计算出来，都是已知，所以可以直接得到当前点的值，
    #     即 path_cnt[i][cycle] = path_cnt[i-1][cycle] + path_cnt[i][cycle-1]
    for i in range(1, cycle):
        path_cnt[i][cycle] = path_cnt[i-1][cycle] + path_cnt[i][cycle-1]
    
    # 3.2 除交叉点 [cycle,cycle] 之外，竖着的一排点( [cycle, 1~cycle-1] ), 可以从上往下依次计算其值，每个点的值等于它的左边点+上边点，
    #     左边点在上一圈中已经计算出来，上边点在前一步已经计算出来，都是已知，所以可以直接得到当前点的值，
    #     即 path_cnt[cycle][i] = path_cnt[cycle-1][i] + path_cnt[cycle][i-1]
    for i in range(1, cycle):
        path_cnt[cycle][i] = path_cnt[cycle-1][i] + path_cnt[cycle][i-1]

    # 3.3 对于交叉点 [cycle,cycle], 在3.1 和3.2 中，已经计算出其左边点和上边点的值了，
    #     也就可以直接得到它的值 path_cnt[cycle][cycle] = path_cnt[cycle-1][cycle] + path_cnt[cycle][cycle-1]
    path_cnt[cycle][cycle] = path_cnt[cycle-1][cycle] + path_cnt[cycle][cycle-1]

print(path_cnt[20][20])
```

## 方法3 排列组合，极其高效

从方格 (0,0) 走到 (w,h) 处，要向左走w步，向下走h步。至于每一步向左和向下其实是无所谓的，只要整个过程向左了w步，向下了h步，必然就能走到(w,h)点。
这就相当于 总共要走 w+h 步，其中包含 w 步向左的，这就是一个排列问题，即 C(w+h, w)

C(w+h, w) = (w+h)! / ( w! * (w+h - w)! ) = (w+h)! / ( w! * h!)

所以问题的解就是C(20+20, 20) = C(40,20) = 40!/(20!*20!) = 137846528820


## 答案
137846528820