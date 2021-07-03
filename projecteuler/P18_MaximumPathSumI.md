# Problem 18: Maximum path sum I

> https://projecteuler.net/problem=18

By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

```
   3
  7 4
 2 4 6
8 5 9 3
```

That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom of the triangle below:

```
              75
             95 64
            17 47 82
           18 35 87 10
          20 04 82 47 65
         19 01 23 75 03 34
        88 02 77 73 07 63 67
       99 65 04 28 06 16 70 92
      41 41 26 56 83 40 80 70 33
     41 48 72 33 47 32 37 16 94 29
    53 71 44 65 25 43 91 52 97 51 14
   70 11 33 28 77 73 17 78 39 68 17 57
  91 71 52 38 17 14 91 43 58 50 27 29 48
 63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
```

**NOTE**: As there are only 16384 routes, it is possible to solve this problem by trying every route. However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)

## 分析

三角形数字塔，从顶到低 找到一条路径，它的和最大，求该和的值。题目最后提醒我们最好不要用穷举法，虽然穷举可以解决本题。

首先想到的是动态规划法，使用递归实现，可以很容易获取答案。详见方法1。

但是递归实现的效率低，应对本题的规模还可以，对付如 Problem 67 就不行了。所以可以考虑使用带查找表的递推来实现。详见方法2。

两者的区别是，递归是从塔顶到塔底，使用带查找表的递推是从塔底到塔顶。

## 方法1 动态规划法，递归，效率不高

这题是很典型的**动态规划**算法题

- 首先将三角形数字塔保存到文件中，然后读取到data[][]数组中
- max_sum(row,column) 表示从 row 行，colomn 列往下走到塔底，最大的路径和。max_sum(0,0)就是问题的解。 max_sum(row,column)  = data[row][column] + max{ max_sum(row+1,column), max_sum(row+1,column+1)}，即从当前点走到底的最大值，是当前点的值（data[row][column] ）加上 从从左下角开始到塔底的最大值（max_sum(row+1,column） 和从右下角开始到塔底的最大值（max_sum(row+1,column+1)）。【数组中表示就是点的下面一个点开始，和下面一个点的右边点开始】

### CPP

```cpp
#include <stdio.h>
#include <stdlib.h>

#define SIZE 15
int data[SIZE][SIZE];

// 从 triangle.txt 中读取数据到data数组中
int read_data()
{
    FILE* fp = fopen("triangle.txt","r");

    for(int row = 0; row < SIZE; row++){
        for(int colum = 0; colum <= row; colum++){
            fscanf(fp,"%d", &data[row][colum]);
            printf("%2d ", data[row][colum]);
        }
        printf("\n");
    }
    fclose(fp);
    return 1;
}

int max(int a,int b){return a>=b ? a:b;}

// 动态规划法，找最大值
int max_sum(int row, int colum)
{
    if( row < colum){
        return 0;
    }

    if(row >= SIZE || colum >= SIZE){
        return 0;
    }

    return data[row][colum] + max( max_sum(row+1,colum), max_sum(row+1,colum+1) );
}
int main()
{
    read_data();
    printf("%d \n",max_sum(0,0));
    return 0;
}
```

### Golang

```go
package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

const SIZE = 15

// 从 triangle.txt 中读取数据到data数组中
func readTriangleData() [SIZE][SIZE]int {

	var data [SIZE][SIZE]int
	bytes, _ := ioutil.ReadFile("triangle.txt")
	content := string(bytes)

	lines := strings.Split(content, "\n")
	for row, line := range lines {
		line = strings.TrimLeft(line, " ")
		numbers := strings.Split(line, " ")
		for column, n := range numbers {
			u64, _ := strconv.ParseUint(n, 10, 32)
			data[row][column] = int(u64)
		}
	}

	return data
}

// maxSum 动态规划法，找 (row, column) 点到最底下一行的路径和最大值
func maxSum(data [SIZE][SIZE]int, row, column int) int {
	if row < column {
		return 0
	}

	if row >= SIZE || column >= SIZE {
		return 0
	}

	max := func(a, b int) int {
		if a >= b {
			return a
		}
		return b
	}

	return data[row][column] + max(maxSum(data, row+1, column), maxSum(data, row+1, column+1))
}

func main() {
	data := readTriangleData()
	fmt.Println(maxSum(data, 0, 0))
}
```

### Python

```python
triangle = '''
              75
             95 64
            17 47 82
           18 35 87 10
          20 04 82 47 65
         19 01 23 75 03 34
        88 02 77 73 07 63 67
       99 65 04 28 06 16 70 92
      41 41 26 56 83 40 80 70 33
     41 48 72 33 47 32 37 16 94 29
    53 71 44 65 25 43 91 52 97 51 14
   70 11 33 28 77 73 17 78 39 68 17 57
  91 71 52 38 17 14 91 43 58 50 27 29 48
 63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
'''

data, size = [], 15

# read triangle to data
lines = [line.strip() for line in triangle.splitlines()]
for line in lines :
    if len(line) == 0:
        continue
    numbers = line.split(' ')
    row = []
    for n in numbers :
        row.append( int(n) )
    data.append(row)
#print(data)

# maxSum 动态规划法，找 (row, column) 点到最底下一行的路径和最大值
def maxSum(row, column):
    if row < column:
        return 0
    if row >= size or column >= size :
        return 0

    return data[row][column] + max(maxSum(row+1, column), maxSum(row+1, column+1)) 

print(maxSum(0,0))

```


## 方法2 动态规划法，带查找表的递推实现，速度快，可以瞬间解决Problem67

带查找表的递推的思路如下：

- 首先将三角形数字塔从文件中读取到data[][]数组中。
- 使用path_sum[row][column] 记录从 (row,column) 到塔底的最大的路径和。
- 对于塔底（最后一行）的数，其path_sum就等于它们本身的数值，即path[SIZE-1][0 ~ (SIZE-1)] = data[SIZE-1][0 ~ (SIZE-1)] 。其中SIZE 是塔的高度，数组下标从0开始。
- 从倒数第二行往上，直到塔顶（row=0）。每一个当前点(row,column) 到 塔底的最大路径和就是它本身的数值，加上它下面两个点到塔底的最大路径和中较大的一个。即path[row][column] = data[row][column]+max{path[row+1][column] ,path[row+1][column+1] }
这种带查找表的递推实现的算法，对每个点都只统计了一次，而且没有递归堆栈的消耗，所以更快。

这个方法运行很快，即便是Problem 67,也是一瞬间就解出了正确答案。

### CPP

```cpp
#include <stdio.h>
#include <stdlib.h>

#define SIZE 15
int data[SIZE][SIZE];

// 从 triangle.txt 中读取数据到data数组中
int read_data()
{
    FILE* fp = fopen("triangle.txt","r");

    for(int row = 0; row < SIZE; row++){
        for(int colum = 0; colum <= row; colum++){
            fscanf(fp,"%d", &data[row][colum]);
            printf("%2d ", data[row][colum]);
        }
        printf("\n");
    }
    fclose(fp);
    return 1;
}

int max(int a,int b){return a>=b ? a:b;}


// 动态规划法，找最大值,使用查找表 lookup table
int max_sum()
{
    // 查找表
    int path_sum[SIZE][SIZE]; // path_sum[row][column] 记录从 (row,column) 点到塔底的最大路径和

    // 最下面的一行，即塔底的一行,其path_sum就等于本身的数值
    for (int i = 0; i < SIZE; i++){
        path_sum[SIZE-1][i] = data[SIZE-1][i];
    }

    //从倒数第二行开始，一直往塔顶找
    for (int row = SIZE-2; row >= 0; row--){ //行从 SIZE-2（即倒数第二行）到0（即塔顶）
        for(int column = 0; column <= row; column++){ //列，从左到右
            //当前点到塔底的最大路径和 = 它本身的数值 + 它下面两个点到塔底的最大路径和中较大的一个
            path_sum[row][column] = data[row][column] + max(path_sum[row+1][column],path_sum[row+1][column+1]);
        }
    }

    return path_sum[0][0];
}

int main()
{
    read_data();
    printf("%d \n",max_sum());
    return 0;
}
```

### Golang

```go
package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
)

const SIZE = 15

// 从 triangle.txt 中读取数据到data数组中
func readTriangleData() [SIZE][SIZE]int {

	var data [SIZE][SIZE]int
	bytes, _ := ioutil.ReadFile("triangle.txt")
	content := string(bytes)

	lines := strings.Split(content, "\n")
	for row, line := range lines {
		line = strings.TrimLeft(line, " ")
		numbers := strings.Split(line, " ")
		for column, n := range numbers {
			u64, _ := strconv.ParseUint(n, 10, 32)
			data[row][column] = int(u64)
		}
	}

	return data
}

// maxSum 动态规划法，找 (row, column) 点到最底下一行的路径和最大值
// 使用查找表 lookup table
func maxSum(data [SIZE][SIZE]int) int {

	// 查找表
	var path_sum [SIZE][SIZE]int // path_sum[row][column] 记录从 (row,column) 点到塔底的最大路径和

	// 最下面的一行，即塔底的一行,其path_sum就等于本身的数值
	for i := 0; i < SIZE; i++ {
		path_sum[SIZE-1][i] = data[SIZE-1][i]
	}

	max := func(a, b int) int {
		if a >= b {
			return a
		}
		return b
	}

	// 从倒数第二行开始，一直往塔顶找
	for row := SIZE - 2; row >= 0; row-- { //行从 SIZE-2（即倒数第二行）到0（即塔顶）
		for column := 0; column <= row; column++ { //列，从左到右
			//当前点到塔底的最大路径和 = 它本身的数值 + 它下面两个点到塔底的最大路径和中较大的一个
			path_sum[row][column] = data[row][column] + max(path_sum[row+1][column], path_sum[row+1][column+1])
		}
	}

	return path_sum[0][0]
}

func main() {
	data := readTriangleData()
	fmt.Println(maxSum(data))
}
```

### Python

```python
triangle = '''
              75
             95 64
            17 47 82
           18 35 87 10
          20 04 82 47 65
         19 01 23 75 03 34
        88 02 77 73 07 63 67
       99 65 04 28 06 16 70 92
      41 41 26 56 83 40 80 70 33
     41 48 72 33 47 32 37 16 94 29
    53 71 44 65 25 43 91 52 97 51 14
   70 11 33 28 77 73 17 78 39 68 17 57
  91 71 52 38 17 14 91 43 58 50 27 29 48
 63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
'''

data, size = [], 15

# read triangle to data
lines = [line.strip() for line in triangle.splitlines()]
for line in lines :
    if len(line) == 0:
        continue
    numbers = line.split(' ')
    row = []
    for n in numbers :
        row.append( int(n) )
    data.append(row)
#print(data)

# 动态规划法，找最大值,使用查找表 lookup table

# 查找表 path_sum[row][column]记录从(row,column)点到塔底的最大路径和
path_sum = [[0 for i in range(0,size)] for j in range(0,size)]

#最底下一行
for i in range(0,size):
    path_sum[size-1][i] = data[size-1][i]

#从倒数第二行(row=size-2)到塔顶(row=0)
for row in range(size-2,-1,-1):
    for column in range(0,row+1): #列从0~row
        #当前点到塔底的最大路径和 = 它本身的数值 + 它下面两个点到塔底的最大路径和中较大的一个
        path_sum[row][column] = data[row][column] + max(path_sum[row+1][column],path_sum[row+1][column+1])

print(path_sum[0][0])
```

## 答案
1074

## 知识点

- 动态规划法 (DP算法）
- 动态规划法的递归实现：通常由上到下，即由未知 递归到 已知
- 动态规划法的递推实现：通常由下到上，即由已知 递推得到 未知 【通常使用查找表lookup table，或称 备忘录】