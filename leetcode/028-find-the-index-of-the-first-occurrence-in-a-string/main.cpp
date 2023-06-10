/*
 * https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
 * 题目：给定两个 string, needle 和 haystack，返回 needle 在 haystack 中第一次出现的位置。如果不存在，则返回 -1
 * 思路：
 *    其实就是 string::find 函数
 */
#include <iostream>
using namespace std;

#define TEST(a, b) ((a == b) ? "pass" : "fail")

// Accepted 0 ms
// 思路1  直接使用 string::find
class Solution {
public:
    int strStr(string haystack, string needle) {
        return haystack.find(needle);
    }
};

// 思路2  手动实现 string::find
// 采用最简单的字符串匹配算法，即 Sliding Window 算法
// 其它思路：采用KMP 等字符串匹配算法
class Solution2 {
public:
    int strStr(string haystack, string needle) {
        for(int i = 0; i < int(haystack.size()) - int(needle.size()) + 1; i++) {
            int j = 0;
            while(j < needle.size() && haystack[i] == needle[j]) {i++; j++;}
            i -= j;
            if(j == needle.size()) return i;
        }
        return -1;
    }
};

// 思路3： Rabin-Karp Algorithm (Single Hash)
// 来源官方解法：https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/editorial/
// 基本思路如下：
//     假设子串的长度是 m，我们给子串计算一个 hash 值。 然后给原串每 m 个字符也计算一个hash.
//     这样比较时，直接比较子串的 hash 和 原串当前位置的 hash 是否相等即可。 不等肯定不匹配。相等的话，再逐字符做匹配，来确定不是因为hash冲突引起的相等。
// 这里有两个问题：
//     (1) 如果 hash 值冲突太多，那么需要逐字符比较的次数就多了，等同于思路2了，所以要尽量减少hash值的冲突
//     (2) 原串要每 m 个字符计算一个hash。如果只是简单的取每m个字符，计算hash，那不如不算hash，直接和子串判等了。所以这里也要优化。
// 解决方案：
//     问题(1) ：对于 m 长度的字符串，每个字符的 value 取 m[i]-'a'，即 a=>0, b=>1 ...，
//              每个字符的 position weight 取值是 RADIX^index，即 RADIX的n次方，index是它在字符串中的位置，RADIX 是一个基数。
//              字符有26中可能，只要取 RADIX >= 26，hash(m) = value[0] * RADIX^0 + value[1] * RADIX^1 ....，这样hash值就不会重复。
//              比如 字符串为 abd, RADIX=26, hash(abd) = 0*26^0 + 1*26^1 + 3*26^2
//              当然，hash(xxx) 的值可能很大，所以需要取模，一般是选一个很大的质数取模
//     问题(2)： 通过 rolling hash 解决。 比如对于原串 abcdefg, 子串长度为3，在计算 hash(bcd) 时不用依次计算b/c/d，只需要对 hash(abc) 减去 a 的值， 除以radix，再加上 b 的值即可。
//              这样，只需要计算前 m 个字符的hash, 后面的字符hash都可以直接算出来。
//     因为 取模 的问题，算出来的hash值，可能无法被 radix 除尽，所以上面的hash算法要稍加改造。
//         如：原来 hash(abd) = 0*26^0 + 1*26^1 + 3*26^2 ，改为 hash(abd) = 0*26^2 + 1*26^1 + 3*26^0
//         这样计算 rolling hash时，就避免了除法，改成了乘法，对于串 abcd，hash(bcd) =  ( hash(abc) - a的值) * 26 + d
class Solution3 {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size();
        int m = needle.size();
        if(n < m) return -1;

        int radix = 26;      // 26 个字母，radix >= 26 即可
        int mod = 1000000033;// 一个大的质数

        int hash_pre = hashStr(haystack, m, radix, mod);
        int hash_sub = hashStr(needle, m, radix, mod);
        if(hash_pre == hash_sub && strEqual(haystack, 0, needle)){
            return 0;
        }

        for(int i = 1; i < n-m+1; i++){
            int h = hashRolling(hash_pre, m, haystack[i-1], haystack[i+m-1], radix, mod);
            //printf("i=%d main:%s,%d, sub:%s,%d, equal:%s\n", i, haystack.substr(i, m).c_str(), h, needle.c_str(), hash_sub, h == hash_sub?"true":"false");
            if(h == hash_sub && strEqual(haystack, i, needle)){
                return i;
            }
            hash_pre = h;
        }

        return -1;
    }

    // hash_pre: 前m个字符子串的hash值
    // m: 子串的长度
    // first_pre: pre串的首个字符
    // new_char: 新加入的字符
    // radix: 基数
    // mod: 取模
    int hashRolling(int hash_pre, int m, char first_pre, char new_char, int radix, int mod){
        int hpre = hashChar(first_pre, m-1, radix, mod);
        int hnew = hashChar(new_char, 0, radix, mod);
        return ( long(mod + hash_pre - hpre) * radix + hnew) % mod; // mod+ 是为了防止负数
    }

    int hashStr(const std::string& s, int m, int radix, int mod){
        int h = 0;
        for(int i = 0; i < m; i++) {
            int hc = hashChar(s[i], m - i - 1 , radix, mod);
            h = (h + hc) % mod;
        }
        return h;
    }

    int hashChar(char c, int power, int radix, int mod) {
        long value = c - 'a';
        long position_weight = powMod(radix, power, mod); // radix^i
        return int(value * position_weight % mod);
    }

    // return a^b
    int powMod(int a, int b, int mod) {
        long p = 1;
        for(int i = 0; i < b; i++) p =  p*a % mod;
        return p;
    }

    bool strEqual(const std::string& str1, int start_at, const std::string& str2){
        for(int i = 0; i < str2.size(); i++) {
            if(str1[i+start_at] != str2[i]) return false;
        }
        return true;
    }
};

// Solution3 的官方答案
class Solution4 {
public:
    int hashValue(string string, int RADIX, int MOD, int m) {
        int ans = 0;
        long factor = 1;
        for (int i = m - 1; i >= 0; i--) {
            ans += ((int) (string[i] - 'a') * factor) % MOD;
            factor = (factor * RADIX) % MOD;
        }
        return ans % MOD;
    }

    int strStr(string haystack, string needle) {
        int m = needle.length();
        int n = haystack.length();
        if (n < m)
            return -1;

        // CONSTANTS
        int RADIX = 26;
        int MOD = 1000000033;
        long MAX_WEIGHT = 1;

        for (int i = 0; i < m; i++)
            MAX_WEIGHT = (MAX_WEIGHT * RADIX) % MOD;

        // Compute hash of needle
        long hashNeedle = hashValue(needle, RADIX, MOD, m), hashHay = 0;

        // Check for each m-substring of haystack, starting at index windowStart
        for (int windowStart = 0; windowStart <= n - m; windowStart++) {
            if (windowStart == 0) {
                // Compute hash of the First Substring
                hashHay = hashValue(haystack, RADIX, MOD, m);
            } else {
                // Update Hash using Previous Hash Value in O(1)
                hashHay = ((hashHay * RADIX) % MOD - ((int) (haystack[windowStart - 1] - 'a') * MAX_WEIGHT) % MOD
                           + (int) (haystack[windowStart + m - 1] - 'a') + MOD) % MOD;
            }
            // If the hash matches, Check Character by Character.
            // Because of Mod, spurious hits can be there.
            if (hashNeedle == hashHay) {
                for (int i = 0; i < m; i++) {
                    if (needle[i] != haystack[i + windowStart]) {
                        break;
                    }
                    if (i == m - 1) {
                        return windowStart;
                    }
                }
            }
        }

        return -1;
    }
};


// Approach 3: Rabin-Karp algorithm (Double Hash)
// 即 Solution3/Solution4 的优化版本，优化思路如下：
// Solution3/Solution4 中，如果hash值相等，那么会逐字符的比较来最终确定是否相同。
// Double Hash 算法的核心是：减少这种逐字符比较的情况，即减少hash冲突的情况，那么怎么办？
// 方案是使用两个hash函数， hash算法本身不变，更改下 radix mod 参数即可。 这样判断时，如果两个hash都相等，再逐字符判断。这样可以大大减少逐字符判断的机率。
class Solution5{};

// KMP 算法
class Solution6{};

int main()
{
    Solution3 s;

//    int h = s.hashChar('c', 7, 26, 1000000033);
//    if (h % 26 == 0){
//        cout << h << endl;
//    }
//
//    Solution5 s5;
//    int h1 = s5.hashValue("abaababcaabc", 26, 1000000033, 9 );
//    if (h1 % 26 == 0){
//        cout << h1 << endl;
//    }

    cout << TEST(s.strStr("a", "a"), 0) << endl;
    cout << TEST(s.strStr("a", "abc"), -1) << endl;
    cout << TEST(s.strStr("abaababcaabc", "ababcaabc"), 3) << endl;
    cout << TEST(s.strStr("ababcaababcaabc", "ababcaabc"), 6) << endl;
    cout << TEST(s.strStr("mississippi", "mississippi"), 0) << endl;
    cout << TEST(s.strStr("abc", "bc"), 1) << endl;
    cout << TEST(s.strStr("sadbutsad", "sad"), 0) << endl;
    cout << TEST(s.strStr("leetcode", "leeto"), -1) << endl;
    cout << TEST(s.strStr("adfasdfasdfasd", "a"), 0) << endl;
    cout << TEST(s.strStr("fsdfasdfasdfas", "fasd"), 3) << endl;
    cout << TEST(s.strStr("fsdfasdfasdfas", "fasd"), 3) << endl;
}