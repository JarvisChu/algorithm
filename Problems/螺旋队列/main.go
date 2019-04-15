// 螺旋队列
// 问题描述和分析： http://zhujiangtao.com/?p=1238

package main
import "fmt"

func getAbs(x int) int {
    if x > 0 {
        return x
    }
    return -x
}

func getMax(x, y int) int {
    if x > y {
        return x
    }
    return y
}

func GetValue(x,y int) int {

    // x,y 中较大的值，就是(x,y)所在的圈数
    n := getMax(x,y)

    p := (2 * n + 1) * (2 * n + 1)
    p1 := p - n
    p2 := p - 3 * n
    p3 := p - 5 * n
    p4 := p - 7 * n

    if x == n {
        return p4 + y
    }

    if x == -n {
        return p2 - y
    }

    if y == n {
        return p1 + x
    }

    if y == -n {
        return p3 - x
    }

    return 0
}

func main(){
   fmt.Printf("%v\n", GetValue(0,0))
   fmt.Printf("%v\n", GetValue(1,1))
   fmt.Printf("%v\n", GetValue(10,10))
}