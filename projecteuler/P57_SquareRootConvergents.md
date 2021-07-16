# Problem 57: Square root convergents

> https://projecteuler.net/problem=57

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/project_euler_57_1.png)

## 分析

每次扩展，相当于将 1/2 替换为 1/(2+1/2)，所以

```
第 1 次扩展结果: fraction = 1 + 1/2
第 2 次扩展结果: fraction = 1 + 1/(2+1/2)
第 3 次扩展结果: fraction = 1 + 1/(2+1/(2+1/2))
第 4 次扩展结果: fraction = 1 + 1/(2+1/(2+1/(2+1/2)))
第 5 次扩展结果: fraction = 1 + 1/(2+1/(2+1/(2+1/(2+1/2))))
第 6 次扩展结果: fraction = 1 + 1/(2+1/(2+1/(2+1/(2+1/(2+1/2)))))
...
```

做 n 次拓展，相当于对 fraction 做 n 次替换。

接下来，就需要计算 fraction 的值。以6次拓展的结果为例，整个求值过程如下：

```
1 + 1/(2+1/(2+1/(2+1/(2+1/(2+1/2)))))  x 2
1 + 1/(2+1/(2+1/(2+1/(2+2/(4+1)))))
1 + 1/(2+1/(2+1/(2+1/(2+2/5))))        x 5
1 + 1/(2+1/(2+1/(2+5/(10+2))))
1 + 1/(2+1/(2+1/(2+5/12)))             x 12
1 + 1/(2+1/(2+12/(24+5)))
1 + 1/(2+1/(2+12/29))                  x 29
1 + 1/(2+29/(58+12))
1 + 1/(2+29/70)                       x 70
1 + 70/(140+29)
1 + 70/169
```

从上面的求值过程可见，每步的求值相当于：

(1) 先找最后一个 `1/(a+b/c)` 格式的算式

(2) 再对该算式做 `*c` 处理，得到 `c/(a*c+b)`，计算出 `a*c+b` 的值，变成 `c/d`

(3) 再使用 `c/d` 替换 `1/(a+b/c)` 即可

重复上述步骤，直到找不到 `1/(a+b/c)` 格式的算式，此时 fraction 的格式必然为 `1+a/b`，即 (a+b)/b，分子为 a+b, 分母为b。 判断分子分母的长度。如果分子比分母长，则统计值+1。

对 1~1000 的每一个数，做上述处理，获取最终的统计值，即为答案

**这里有个注意点**： 上述过程中的 a,b,c,d 都可能是大数，必须做**大数处理**。

## 方法1 如分析

### Golang

```go
package main

import (
	"fmt"
	"math/big"
	"strings"
)

// 做 cnt 次展开，返回最终分数的分子和分母
func expansion(cnt int) (numerator, denominator *big.Int) {

	// 1 + 1/2 => 1 + 1/(2+1/2)  => 1 + 1/(2 + 1/(2+1/2) ) => 1 + 1/(2+1/(2+ 1/(2+1/2) ))
	// i.e 每次展开相当于替换 1/2 为 1/(2+1/2)
	// cnt: 1, fraction: 1 + 1/2
	// cnt: 2, fraction: 1 + 1/(2+1/2)
	// cnt: 3, fraction: 1 + 1/(2+1/(2+1/2))
	// cnt: 4, fraction: 1 + 1/(2+1/(2+1/(2+1/2)))
	// cnt: 5, fraction: 1 + 1/(2+1/(2+1/(2+1/(2+1/2))))
	// cnt: 6, fraction: 1 + 1/(2+1/(2+1/(2+1/(2+1/(2+1/2)))))

 	fraction := "1+1/2"      // 第一次展开的值
	for i := 1; i < cnt; i++ { // 再做 cnt-1 次展开
		fraction = strings.ReplaceAll(fraction, "1/2", "1/(2+1/2)")
	}

	// 接下来，计算 fraction 算式的值

	// 以cnt=6时为例，整个求值过程如下：
	// 1 + 1/(2+1/(2+1/(2+1/(2+1/(2+1/2)))))  x 2
	// 1 + 1/(2+1/(2+1/(2+1/(2+2/(4+1)))))
	// 1 + 1/(2+1/(2+1/(2+1/(2+2/5))))        x 5
	// 1 + 1/(2+1/(2+1/(2+5/(10+2))))
	// 1 + 1/(2+1/(2+1/(2+5/12)))             x 12
	// 1 + 1/(2+1/(2+12/(24+5)))
	// 1 + 1/(2+1/(2+12/29))                  x 29
	// 1 + 1/(2+29/(58+12))
	// 1 + 1/(2+29/70)                       x 70
	// 1 + 70/(140+29)
	// 1 + 70/169

	// 可见，每次相当于：
	// (1) 先找最后一个 1/(a+b/c) 格式的算式
	// (2) 再对该算式做 *c 处理，得到 c/(a*c+b)，计算出a*c+b的值，变成 c/d
	// (3) 再使用 c/d 替换 1/(a+b/c) 即可

	for{
		// (1) 先找到最后一个 1/(a+b/c) 格式的算式，
		// 起始点 start 为倒数第二个除号 / 前一位
		// 结束点 end 为 start 之后的第一个右括号 )
		// 如果找不到，说明整个算式已经是 1+a/b 的形式了，结束

		start, end := -1, -1 // 起止点
		seq := 0
		for i := len(fraction) - 1; i >= 0; i-- {
			if fraction[i:i+1] == "/" {
				seq++
				if seq == 2 { // 倒数第二个 /
					start = i - 1
					break
				}
			}
		}

		// 没找到 start，说明已经是 1+a/b 的形式了
		if start == -1 {
			break
		}

		// start 之后的第一个右括号 ) 即为 end
		for i := start; i <= len(fraction) - 1; i++ {
			if fraction[i:i+1] == ")" {
				end = i
				break
			}
		}

		// (2) 取出算式 expression = fraction[start,end] 做 *c 处理，得到 c/(a*c+b) => c/d
		// 从算式 1/(a+b/c) 中取出 a,b,c 的值，计算出 d, 并生成 c/d
		// 注意，a,b,c,d 都可能是大数
		expression := fraction[start:end+1] // 1/(a+b/c)
		expression = strings.ReplaceAll(expression,"(", "") // 1/(a+b/c) => 1/a+b/c)
		expression = strings.ReplaceAll(expression,")", "") // 1/a+b/c) => 1/a+b/c
		arr := strings.Split(expression, "/") // [1,a+b,c]
		arr2 := strings.Split(arr[1], "+") // [a,b]

		a,b,c,d := big.NewInt(0),big.NewInt(0),big.NewInt(0),big.NewInt(0)
		a, _ = a.SetString(arr2[0], 10)
		b, _ = b.SetString(arr2[1], 10)
		c, _ = c.SetString(arr[2], 10)
		d = d.Mul(a,c) // d := a*c+b
		d = d.Add(d,b)
		s := fmt.Sprintf("%v/%v", c.String(), d.String()) // s: c/d

		// (3) 再使用 c/d 替换 1/(a+b/c) 即可
		fraction = strings.ReplaceAll(fraction, fraction[start:end+1], s)

		//fmt.Println(fraction)
	}

	// 运行至此，fraction 格式为 1+a/b
	// 取出从 1+a/b 中取出 a,b 的值
	arr := strings.Split(fraction,"+") // [1,a/b]
	arr2 := strings.Split(arr[1], "/") // [a,b]

	a,b := big.NewInt(0),big.NewInt(0)
	a, _ = a.SetString(arr2[0], 10)
	b, _ = b.SetString(arr2[1], 10)

	// 1+a/b => (a+b)/b, 分子 a+b, 分母 b
	// [对分子分母不用做约分]
	numerator, denominator= big.NewInt(0), big.NewInt(0)
	numerator = numerator.Add(a,b) // 分子
	denominator = b                // 分母

	//fmt.Printf("cnt=%v, fraction=%v/%v\n", cnt, numerator, denominator)
	return numerator, denominator
}

func main() {
	cnt := 0
	for i := 1; i <= 1000; i++ {
		numerator, denominator := expansion(i)
		if len(numerator.String()) > len(denominator.String()) {
			cnt++
		}
	}

	fmt.Println(cnt)
}
```

## 方法2 来自论坛中的第一个答案

### Python

```python
def expand(n):
    (num,den) = (1,2)
    for i in range(1, n): (num,den) = (den,num + 2*den)
    return (num,den)

def nth(n):
    (num,den) = expand(n)
    return len(str(num+den)) > len(str(den))

counter = 0
for n in range(0, 1000): 
    if nth(n+1): counter += 1
print(counter)
```

## 答案

153