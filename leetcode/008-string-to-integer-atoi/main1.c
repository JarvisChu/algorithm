#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 优化上一个方案，即 main.c 中的方案
// 优化点：不用做过多容易得判断

// 重新实现atoi
// Accepted 0 ms Beats 100%
int myAtoi(char * str){
    if(str == NULL) return 0;

    long n = 0;       // 当前找到的数值，使用long，防止溢出
    int positive = 1; //

    char * p = str;
    while(*p == ' ') p ++; // 跳过空格
    
    if(*p == '+') p ++;    // 处理符号
    else if(*p == '-'){
        positive = 0;
        p++;
    }

    while(*p >= '0' && *p <= '9') {
        n = n * 10 + (*p - '0');
        p++;
        if(n - 1 > INT32_MAX ) break; // -1 是为了负数的情况， n > INT32_MAX + 1
    }

    if(positive){
        return n > INT32_MAX ? INT32_MAX : n;
    }else{
        n = -n;
        return n < INT32_MIN ? INT32_MIN : n;
    }
}

int main()
{
    printf("%d\n", myAtoi("-2147483648")); // expect -2147483648
    printf("%d\n", myAtoi("-2147483647")); // expect -2147483647 
    
    printf("%d\n", myAtoi("42"));
    printf("%d\n", myAtoi("-42"));
    printf("%d\n", myAtoi("4193 with words"));
    printf("%d\n", myAtoi("words and 987"));
    printf("%d\n", myAtoi("-91283472332"));

    return 0;
}