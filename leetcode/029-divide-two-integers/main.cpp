/*
 * https://leetcode.com/problems/divide-two-integers/
 * 题目：不使用除法/乘法/取模等算法，来求两个数的商， 商只保留整数部分
 * 思路：
 *    用减法来模拟除法，但是如果每次都只减去减数，那么速度太慢。所以需要采用：快启动/快恢复 的算法。
 *    即：只要够减，就把 除数*2，直到不够减，再把 除数/2 (使用移位实现/2)
 */
#include <iostream>
using namespace std;

#define TEST(a, b) ((a == b) ? "pass" : "fail")

// Time Limit Exceeded
// 思路1 直接使用减法替代除法
class Solution1 {
public:
    int divide(int dividend, int divisor) {
        if(dividend == 0 || divisor == 0) return 0;

        //  convert to positive numbers, using long to avoid overflow
        long dd = dividend > 0 ? dividend : - (long) dividend;
        long ds = divisor > 0 ? divisor : - (long) divisor;
        long quotient = 0;
        while(dd >= ds) {
            quotient++;
            dd -= ds;
        }

        // check the sign for the result
        bool positive = (dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0);
        quotient = positive ? quotient : -quotient;

        if(quotient > INT32_MAX) return INT32_MAX;
        if(quotient < INT32_MIN) return INT32_MIN;
        return quotient;
    }
};

// Time Limit Exceeded
// 思路2 直接使用减法替代除法，但是优化减法，不再是每次减去被减数，而是采用快启动、慢恢复的策略
class Solution2 {
public:
    int divide(int dividend, int divisor) {
        if(dividend == 0 || divisor == 0) return 0;

        //  convert to positive numbers, using long to avoid overflow
        long dd = dividend > 0 ? dividend : - (long) dividend;
        long ds = divisor > 0 ? divisor : - (long) divisor;
        long quotient = 0;
        long multi = 1;
        while(multi >= 1) {
            while (dd >= (ds * multi)) {
                quotient += multi;
                dd -= ds * multi;
                multi += multi; // 快启动，multi*2
            }
            multi -= 1; // 慢恢复 multi-1
        }

        // check the sign for the result
        bool positive = (dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0);
        quotient = positive ? quotient : -quotient;

        if(quotient > INT32_MAX) return INT32_MAX;
        if(quotient < INT32_MIN) return INT32_MIN;
        return quotient;
    }
};

// Accepted 3 ms Beats 59.24%
// 思路3 直接使用减法替代除法，优化点：快启动，快恢复
class Solution {
public:
    int divide(int dividend, int divisor) {
        if(dividend == 0 || divisor == 0) return 0;

        //  convert to positive numbers, using long to avoid overflow
        long dd = dividend > 0 ? dividend : - (long) dividend;
        long ds = divisor > 0 ? divisor : - (long) divisor;
        long quotient = 0;
        long multi = 1;

        while(multi >= 1) {
            while (dd >= (ds * multi)) {
                quotient += multi;
                dd -= ds * multi;
                multi += multi; // 快启动，*2
            }
            multi >>= 1; // 快恢复，multi/2
        }

        // check the sign for the result
        bool positive = (dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0);
        quotient = positive ? quotient : -quotient;

        if(quotient > INT32_MAX) return INT32_MAX;
        if(quotient < INT32_MIN) return INT32_MIN;
        return quotient;
    }
};

int main()
{
    Solution s;
    cout << TEST(s.divide(100, 3), 33) << endl;
    cout << TEST(s.divide(10, 3), 3) << endl;
    cout << TEST(s.divide(7, -3), -2) << endl;
    cout << TEST(s.divide(10, 2), 5) << endl;
    cout << TEST(s.divide(17, 3), 5) << endl;

    auto start = chrono::steady_clock::now();
    cout << TEST(s.divide(-2147483648, -1), 2147483647) << endl;
    auto end1 = chrono::steady_clock::now();
    cout<< "cost:" << chrono::duration_cast<chrono::milliseconds>(end1-start).count() <<endl;

    cout << TEST(s.divide(-2147483648, 1), -2147483648) << endl;
    auto end2 = chrono::steady_clock::now();
    cout<< "cost:" << chrono::duration_cast<chrono::milliseconds>(end2-end1).count() <<endl;

    return 0;
}