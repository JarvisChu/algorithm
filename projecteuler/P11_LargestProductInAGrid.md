# Problem 11: Largest product in a grid

> https://projecteuler.net/problem=11

In the 20×20 grid below, four numbers along a diagonal line have been marked in red.

08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08
49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00
81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65
52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91
22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80
24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50
32 98 81 28 64 23 67 10 **26** 38 40 67 59 54 70 66 18 38 64 70
67 26 20 68 02 62 12 20 95 **63** 94 39 63 08 40 91 66 49 94 21
24 55 58 05 66 73 99 26 97 17 **78** 78 96 83 14 88 34 89 63 72
21 36 23 09 75 00 76 44 20 45 35 **14** 00 61 33 97 34 31 33 95
78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92
16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57
86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58
19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40
04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66
88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69
04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36
20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16
20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54
01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48

The product of these numbers is 26 × 63 × 78 × 14 = 1788696.

What is the greatest product of four adjacent numbers in the same direction (up, down, left, right, or diagonally) in the 20×20 grid?

## 分析
从20 x 20 的数字方格中，找出任意方向4个连续的数（往上，往下，往左，往右，往斜左下方，往斜右下方，往斜左上方，往斜右上方），这4个数的乘积最大。给出最大乘积。

## 方法1 遍历求解

对于每一个方格，它有8个方向，上、下、左、右、斜左下方，斜右下方，斜左上方，斜右上方

```
 \|/
-----
 /|\
```

但是我们只需要检测4个方向即可：
- **检查往右**，忽略往左，因为往左的方向已经被左侧的方格在检查向右方向时，检查过了
- **检查往下**，忽略往上，因为往上的方向已经被上方的方格在检查向下方向时，检查过了
- **检查斜右下方**，忽略斜左上方，因为斜左上方已经被斜左上方的方格在检查斜右下方时，检查过了
- **检查斜左下方**，忽略斜右上方，因为斜右上方已经被斜右上方的方格在检查斜左下方时，检查过了


将数组读取到20x20的二维数组data中，遍历每个元素，计算其对应6个方向上的4个数的乘积

### CPP

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* digits =
"08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08 \
49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00 \
81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65 \
52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91 \
22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80 \
24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50 \
32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70 \
67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21 \
24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72 \
21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95 \
78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92 \
16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57 \
86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58 \
19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40 \
04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66 \
88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69 \
04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36 \
20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16 \
20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54 \
01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48";

#define ROWS 20
#define COLUMNS 20
int main()
{
    // string to int array
    int arr[ROWS][COLUMNS] = {0};

    int row = 0, column = 0;
    for(int i=0; i< strlen(digits)-1; i+=3 ){
        arr[row][column] = int(digits[i] - '0') * 10 + int(digits[i+1] - '0') ;
        column ++;
        if(column % 20 == 0) {
            row ++;
            column = 0;
        }
    }

    /*for(int i=0;i<ROWS;i++) {
        for(int j=0;j<COLUMNS;j++) printf("%2d ", arr[i][j]);
        printf("\n");
    }*/

    //find max product
    int maxProduct = 0;
    int a = 0, b = 0, c = 0, d = 0;
    for(row = 0; row < ROWS; row++){
        for(column = 0; column < COLUMNS; column ++){
            int product = 0;

            // For one gird, these are 8 directions. left, left-up, up, right-up, right, right-down, down, left-down
            // But we only need to check 4 directions for one grid, cause the Symmetrical directions already checked.
            
            // no need to check direction-left, because a grid's direction-left is already checked by the grid left side.
            // right

            if(column + 3 < COLUMNS) {
                product = arr[row][column] * arr[row][column+1] * arr[row][column+2] * arr[row][column+3];
                if(product > maxProduct) {
                    maxProduct = product;
                    a = arr[row][column]; b = arr[row][column+1]; c = arr[row][column+2]; d = arr[row][column+3];
                    printf("Find a larger product: maxProduct=%8d row=%2d coloum=%2d direction=right\n", maxProduct, row, column);
                }
            }

            // no need to check direction-left-up, because a grid's direction-left-up is already checked by the gird left up.
            // right-down
            if(row + 3 < ROWS && column + 3 < COLUMNS) {
                product = arr[row][column] * arr[row+1][column+1] * arr[row+2][column+2] * arr[row+3][column+3];
                if(product > maxProduct) {
                    maxProduct = product;
                    a = arr[row][column]; b = arr[row+1][column+1]; c = arr[row+2][column+2]; d = arr[row+3][column+3];
                    printf("Find a larger product: maxProduct=%8d row=%2d coloum=%2d direction=right-down\n", maxProduct, row, column);
                }
            }

            // no need to check direction-up, because a grid's direction-up is already checked by the gird upon.
            // down
            if(row + 3 < ROWS) {
                product = arr[row][column] * arr[row+1][column] * arr[row+2][column] * arr[row+3][column];
                if(product > maxProduct) {
                    maxProduct = product;
                    a = arr[row][column]; b = arr[row+1][column]; c = arr[row+2][column]; d = arr[row+3][column];
                    printf("Find a larger product: maxProduct=%8d row=%2d coloum=%2d direction=down\n", maxProduct, row, column);
                }
            }

            // no need to check direction-right-up, because a grid's direction-right-up is already checked by the grid right-up.
            // left-down
            if(row + 3 < ROWS && column - 3 >= 0) {
                product = arr[row][column] * arr[row+1][column-1] * arr[row+2][column-2] * arr[row+3][column-3];
                if(product > maxProduct) {
                    maxProduct = product;
                    a = arr[row][column]; b = arr[row+1][column-1]; c = arr[row+2][column-2]; d = arr[row+3][column-3];
                    printf("Find a larger product: maxProduct=%8d row=%2d coloum=%2d direction=left-down\n", maxProduct, row, column);
                }
            }
        }
    }

    printf("The finnal max product is: %d, numbers:(%d, %d, %d, %d)\n", maxProduct, a, b, c, d);

    return 0;
}
```

### Golang

```go
package main

import (
    "fmt"
    "strings"
    "strconv"
)


var digits = `
08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08
49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00
81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65
52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91
22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80
24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50
32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70
67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21
24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72
21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95
78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92
16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57
86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58
19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40
04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66
88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69
04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36
20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16
20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54
01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48
`

func String2Array() (arr [][]int) {
    lines := strings.Split(digits, "\n")
    for _, line := range lines {
        if len(line) == 0 {
            continue
        }

        arrLine := []int{}
        numbers := strings.Split(line, " ")
        for _, number := range numbers {
            n, _ := strconv.ParseInt(number, 10, 32)
            arrLine = append(arrLine, int(n))
        }

        arr = append(arr, arrLine)
    }

    return arr
}

func FindMaxProduct(arr [][]int) int {
    ROWS, COLUMNS := 20, 20
    maxProduct, a, b, c, d  := 0, 0, 0, 0, 0
    for row := 0; row < ROWS; row++ {
        for column := 0; column < COLUMNS; column ++ {

            // For one gird, these are 8 directions. left, left-up, up, right-up, right, right-down, down, left-down
            // But we only need to check 4 directions for one grid, cause the Symmetrical directions already checked.
            
            // no need to check direction-left, because a grid's direction-left is already checked by the grid left side.
            // right

            if column + 3 < COLUMNS  {
                product := arr[row][column] * arr[row][column+1] * arr[row][column+2] * arr[row][column+3]
                if product > maxProduct {
                    maxProduct = product
                    a, b, c, d = arr[row][column], arr[row][column+1], arr[row][column+2], arr[row][column+3]
                    fmt.Printf("Find a larger product: maxProduct=%8d row=%2d coloum=%2d direction=right\n", maxProduct, row, column)
                }
            }

            // no need to check direction-left-up, because a grid's direction-left-up is already checked by the gird left up.
            // right-down
            if row + 3 < ROWS && column + 3 < COLUMNS {
                product := arr[row][column] * arr[row+1][column+1] * arr[row+2][column+2] * arr[row+3][column+3]
                if product > maxProduct {
                    maxProduct = product
                    a, b, c, d = arr[row][column], arr[row+1][column+1], arr[row+2][column+2], arr[row+3][column+3]
                    fmt.Printf("Find a larger product: maxProduct=%8d row=%2d coloum=%2d direction=right-down\n", maxProduct, row, column)
                }
            }

            // no need to check direction-up, because a grid's direction-up is already checked by the gird upon.
            // down
            if row + 3 < ROWS {
                product := arr[row][column] * arr[row+1][column] * arr[row+2][column] * arr[row+3][column]
                if product > maxProduct {
                    maxProduct = product
                    a, b, c, d = arr[row][column], arr[row+1][column], arr[row+2][column], arr[row+3][column]
                    fmt.Printf("Find a larger product: maxProduct=%8d row=%2d coloum=%2d direction=down\n", maxProduct, row, column)
                }
            }

            // no need to check direction-right-up, because a grid's direction-right-up is already checked by the grid right-up.
            // left-down
            if row + 3 < ROWS && column - 3 >= 0 {
                product := arr[row][column] * arr[row+1][column-1] * arr[row+2][column-2] * arr[row+3][column-3]
                if product > maxProduct {
                    maxProduct = product
                    a, b, c, d = arr[row][column], arr[row+1][column-1], arr[row+2][column-2], arr[row+3][column-3]
                    fmt.Printf("Find a larger product: maxProduct=%8d row=%2d coloum=%2d direction=left-down\n", maxProduct, row, column)
                }
            }
        }
    }

    fmt.Printf("The finnal max product is: %d, numbers:(%d, %d, %d, %d)\n", maxProduct, a, b, c, d)

    return maxProduct
}

func main(){
   arr := String2Array()

   for _, row := range arr {
       for _, column := range row {
           fmt.Printf("%d ", column)
       }
       fmt.Println("")
   }

   FindMaxProduct(arr)
}
```

### Python

```python
digits = '''
08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08
49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00
81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65
52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91
22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80
24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50
32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70
67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21
24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72
21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95
78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92
16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57
86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58
19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40
04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66
88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69
04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36
20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16
20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54
01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48
'''

# read string to int array
strArr = [ line.split(' ') for line in digits.splitlines() if len(line) > 0 ]
arr = []
for line in strArr:
    arr.append([int(digit) for digit in line])
#print(arr)


# find max product

ROWS, COLUMNS = 20, 20
maxProduct, a, b, c, d = 0, 0, 0, 0, 0
for row in range(ROWS):
    for column in range(COLUMNS) :
        # For one gird, these are 8 directions. left, left-up, up, right-up, right, right-down, down, left-down
        # But we only need to check 4 directions for one grid, cause the Symmetrical directions already checked.
            
        # no need to check direction-left, because a grid's direction-left is already checked by the grid left side.
        # right
        if column + 3 < COLUMNS :
            product = arr[row][column] * arr[row][column+1] * arr[row][column+2] * arr[row][column+3]
            if product > maxProduct :
                maxProduct = product
                a, b, c, d = arr[row][column], arr[row][column+1], arr[row][column+2], arr[row][column+3]
                print("Find a larger product: maxProduct=", maxProduct, "row=", row, ", coloum=", column, ", direction=right")

        # no need to check direction-left-up, because a grid's direction-left-up is already checked by the gird left up.
        # right-down
        if row + 3 < ROWS and column + 3 < COLUMNS :
            product = arr[row][column] * arr[row+1][column+1] * arr[row+2][column+2] * arr[row+3][column+3]
            if product > maxProduct :
                maxProduct = product
                a, b, c, d = arr[row][column], arr[row+1][column+1], arr[row+2][column+2], arr[row+3][column+3]
                print("Find a larger product: maxProduct=", maxProduct, "row=", row, ", coloum=", column, ", direction=right-down")
        
        # no need to check direction-up, because a grid's direction-up is already checked by the gird upon.
        # down
        if row + 3 < ROWS :
            product = arr[row][column] * arr[row+1][column] * arr[row+2][column] * arr[row+3][column]
            if product > maxProduct :
                maxProduct = product
                a, b, c, d = arr[row][column], arr[row+1][column], arr[row+2][column], arr[row+3][column]
                print("Find a larger product: maxProduct=", maxProduct, "row=", row, ", coloum=", column, ", direction=down")

        # no need to check direction-right-up, because a grid's direction-right-up is already checked by the grid right-up.
        # left-down
        if row + 3 < ROWS and column - 3 >= 0 :
            product = arr[row][column] * arr[row+1][column-1] * arr[row+2][column-2] * arr[row+3][column-3]
            if product > maxProduct :
                maxProduct = product
                a, b, c, d = arr[row][column], arr[row+1][column-1], arr[row+2][column-2], arr[row+3][column-3]
                print("Find a larger product: maxProduct=", maxProduct, "row=", row, ", coloum=", column, ", direction=left-down")

print("The finnal max product is: ", maxProduct, ", numbers:", a, b, c, d)
```

## 答案
70600674