# What Are You Looking At

PythonChallenge系列第十题P10（http://www.pythonchallenge.com/pc/return/bull.html）

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p10_1.png)

图像下方文字提示len(a[30])=? ，再点击图像，打开的页面上提示了一行序列

> a = [1, 11, 21, 1211, 111221,

所以，本题思路就是找a序列的规律，然后计算a[30]的长度。

问题的关键：a序列的规律

```
1       1
11      前一个数的描述：1个1
21      前一个数的描述：2个1
1211    前一个数的描述：1个2, 2个1
111221  前一个数的描述：1个1, 1个2, 2个1
```
可见，序列的规律是后一个数是前一个数的具体描述，描述前一个数中某个数字连续出现的次数和该数字本身，自左向右，直到前一个数中每个数字都被描述了。

## 代码

```python
#-*- coding: utf-8 -*-

def generateNext(seq):
    '''生成序列的下一项'''

    #初始
    pre = seq[0] # 前一个数字
    cnt = 1      # 该数字出现的次数
    new = []     # 新的序列

    #中间字符
    for i in range(1,len(seq)):
        if seq[i] == pre:
            cnt+=1
        else:
            new.append(str(cnt))
            new.append(pre)
            cnt = 1
            pre = seq[i]

    #seq最后的字符
    new.append(str(cnt))
    new.append(pre)
    #print(new)
    return ''.join(new)

seq = '1'
a = [seq]
for i in range(0,31):
    #print(i,seq)
    seq = generateNext(seq)
    a.append(seq)
print(a[30])
print(len(a[30]))
```

generateNext函数由传入的当前项seq，产生序列中的下一项并返回。具体的方法就是遍历seq，统计字符，每当前一个pre和当前值seq[i]不一样，则将前一个值出现的次数cnt和前一个值pre追加到new列表中，前一项和后一项相同则cnt++。for循环结束时，seq中末尾的字符还没有被统计进new列表中（因为只在前后变化时，才将前一个加入new中，末尾的字符后面没有字符，就不会产生一个变化，也就不会加入到new中），需要再次添加进去。

主程序中，将seq初始至’1’，然后不断循环调用generateNext产生下一项并添加到a中，最后打印len(a[30])

## 解谜
这一题还是比较直接的，没有绕什么弯弯，关键就是序列规律的寻找。找到规律，编码没有太大难度，算是整个解谜过程中一个调整放松环节吧。程序的输出结果为5808。将url中的bull换成5808即可解谜该题，并打开下一题。

http://www.pythonchallenge.com/pc/return/5808.html