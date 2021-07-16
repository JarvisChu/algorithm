# Problem 59: XOR decryption

> https://projecteuler.net/problem=59

Each character on a computer is assigned a unique code and the preferred standard is ASCII (American Standard Code for Information Interchange). For example, uppercase A = 65, asterisk (*) = 42, and lowercase k = 107.

A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR each byte with a given value, taken from a secret key. The advantage with the XOR function is that using the same encryption key on the cipher text, restores the plain text; for example, 65 XOR 42 = 107, then 107 XOR 42 = 65.

For unbreakable encryption, the key is the same length as the plain text message, and the key is made up of random bytes. The user would keep the encrypted message and the encryption key in different locations, and without both "halves", it is impossible to decrypt the message.

Unfortunately, this method is impractical for most users, so the modified method is to use a password as a key. If the password is shorter than the message, which is likely, the key is repeated cyclically throughout the message. The balance for this method is using a sufficiently long password key for security, but short enough to be memorable.

Your task has been made easy, as the encryption key consists of three lower case characters. Using [p059_cipher.txt](https://projecteuler.net/project/resources/p059_cipher.txt) (right click and 'Save Link/Target As...'), a file containing the encrypted ASCII codes, and the knowledge that the plain text must contain common English words, decrypt the message and find the sum of the ASCII values in the original text.


## 分析

XOR 异或操作可以用于加密，因为它有一个特性：加密和解密可以使用相同的秘钥。如 65 XOR 42 = 107, 107 XOR 42 = 65，65 使用秘钥42加密得到107，107 又可以使用秘钥42解密成65。

理论上，秘钥的长度和明文的长度相等是最稳妥的。但实际上，我们都是使用简短易记的密码作为加密秘钥，该密码会被循环往复的用于明文的加密。

本题的任务是：p059_cipher.txt 中保存了加密后的 ASCII codes, 已知秘钥是3位的小写字母，明文中必须包含常用的英语单词，解密文件中的密文，然后统计明文中所有字符的 ASCII 值的总和。

**思路**
首先需要找到秘钥，如果直接遍历所有可能的话，从 "aaa" 到 "zzz" 有 `26*26*26 = 17575` 中可能，不可能人为的去判断每种解密结果是否合理。需要一种方法，可以快速去除明显不对的解码。

因为明文肯定是可读的，那么在解密过程中，**如果出现了不可显示的字符，即 ascii < 32 或者 ascii > 126 ，那么明显是错误的，直接排除**。

经过这样的筛选，最终仍有 **360** 种可能结果，但相比于 17575 种来说，360 种可能性，还是可以人为的去判断的。最终从 360 种结果中，发现密码为 **"exp"** 时，解密出来的明文是有意义的。

所以，可以使用 "exp" 来解密，得到明文，再统计其中 ASCII 码的总和。

## 方法 如分析中的思路

### CPP

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    // 读取文件中的所有数字，转换成字符，保存到cipher中
    char line[32] = {0};
    std::vector<char> cipher; // 密文
    std::ifstream f("p059_cipher.txt");
    while(f.getline(line, 32, ',')){
        int ascii = atoi(line);
        cipher.push_back( (char) ascii );
    }
    f.close();

    // 尝试使用 a~z 来解码
    for(char key1 = 'a'; key1 <= 'z'; key1++){
        for(char key2 = 'a'; key2 <= 'z'; key2++){
            for(char key3 = 'a'; key3 <= 'z'; key3++){

                char keys[3] = {key1, key2, key3};
                std::vector<char> plainText;   
                bool isValid = true;
                for(int i = 0; i < cipher.size(); i++){
                    char key = keys[ i % 3];
                    char plain = cipher[i] ^ key;
                    // 如果 plain 是不可打印的字符，必然不可能是明文
                    if( plain < 32 || plain >= 127){
                        isValid = false;
                        break;
                    }

                    plainText.push_back(plain);
                }

                if(!isValid) continue;

                printf("\n\nkey:%c%c%c\n", key1, key2,key3);
                for(int i=0;i<plainText.size(); i++) printf("%c", plainText[i]);
                printf("\n");     
            }
        }
    }

    // 通过上面的尝试解码，从输出的360种可能解码中，最终发现密码为 exp
    // 所以使用 exp 来解码，并且统计明文的ASCII码值总和

    char keys[3] = {'e', 'x', 'p'};
    int sum = 0;
    printf("\n\n--- the plain text ---\n");
    for(int i = 0; i < cipher.size(); i++){
        char key = keys[ i % 3];
        char plain = cipher[i] ^ key;
        sum += (int)plain;
        printf("%c", plain);
    }
    printf("\n\nthe sum of plain ascii is: %d\n", sum);
    return 0;
}
```


## 答案

129448

> **明文为**：
> An extract taken from the introduction of one of Euler's most celebrated papers, "De summis serierum reciprocarum" [On the sums of series of reciprocals]: I have recently found, quite unexpectedly, an elegant expression for the entire sum of this series 1 + 1/4 + 1/9 + 1/16 + etc., which depends on the quadrature of the circle, so that if the true sum of this series is obtained, from it at once the quadrature of the circle follows. Namely, I have found that the sum of this series is a sixth part of the square of the perimeter of the circle whose diameter is 1; or by putting the sum of this series equal to s, it has the ratio sqrt(6) multiplied by s to 1 of the perimeter to the diameter. I will soon show that the sum of this series to be approximately 1.644934066842264364; and from multiplying this number by six, and then taking the square root, the number 3.141592653589793238 is indeed produced, which expresses the perimeter of a circle whose diameter is 1. Following again the same steps by which I had arrived at this sum, I have discovered that the sum of the series 1 + 1/16 + 1/81 + 1/256 + 1/625 + etc. also depends on the quadrature of the circle. Namely, the sum of this multiplied by 90 gives the biquadrate (fourth power) of the circumference of the perimeter of a circle whose diameter is 1. And by similar reasoning I have likewise been able to determine the sums of the subsequent series in which the exponents are even numbers.