# What About Making Trans

解谜P0热身题之后，url会自动跳转到第一题P1，（其url如下）

http://www.pythonchallenge.com/pc/def/map.html

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p1_1.png)

观察谜面，图中将K、O、E分别对应指向M、Q、G，这应该是暗示了一种字符转换规则。图片下方给出了一大段乱排的字母，应该在用转换规则对其转换后会给出该题的答案

## 思路
由K、O、E分别对应指向M、Q、G，知转换规则为字符后移两位。又注意到下方的乱排字母段全部为小写，则只要转换小写的即可。

编写代码之前要注意2点:
- (1) 只翻译字母，特殊字符不要翻译；
- (2) 考虑最后的 y和z，y要变成a，z要变成b


## 代码

### 实现代码1

```python
src="g fmnc wms bgblr rpylqjyrc gr zw fylb. \
rfyrq ufyr amknsrcpq ypc dmp. \
bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. \
sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. \
lmu ynnjw ml rfc spj."
dst=''

#conside the special character and the last two character 'y' and 'z'
for c in src:
    # translate alphabet
    if ord(c)<=ord('z') and ord(c)>= ord('a') :
        c1 = chr(ord(c)+2)
        if(c=='y'):
            c1='a'
        if(c=='z'):
            c1='b'
        dst = dst+c1
    # other character no need to trans    
    else:
        dst = dst+c
print(dst)
```

首先将乱排字母段保存在src中，定义dst保存转换后的结果。遍历src，判断当前的字符是不是字母，方法是通过判断ord()函数返回的字符的ASCII码值是否在’a’和‘z’之间，如果不在则不是字母是特殊字符，直接追加到dst中，如果在则是字母，将其ASCII码值+2，在通过chr()函数将+2后的ASCII码转换回字母，再考虑一下y和z的情况，将转换后的字母加入到dst中。最后输出dst如下

> i hope you didnt translate it by hand. thats what computers are for. doing it in by hand is inefficient and that's why this text is so long. using string.maketrans() is recommended. now apply on the url.

由此我们知道：推荐我们使用string.maketrans()函数来实现这个转换功能，这个我们下面再实现；我们可以把这种转换规则应用到url中，也就是把map根据规则转换，转换结果为ocr。

### 实现代码2 使用 string.maketrans 函数

```python
intab="abcdefghijklmnopqrstuvwxyz"
outtab="cdefghijklmnopqrstuvwxyzab"
transtab=str.maketrans(intab,outtab)

src="g fmnc wms bgblr rpylqjyrc gr zw fylb. \
rfyrq ufyr amknsrcpq ypc dmp. \
bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. \
sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. \
lmu ynnjw ml rfc spj."

print(src.translate(transtab))
print("map".translate(transtab))#ocr
```

通过定义转化表，实现字符转换，更加简洁高效而且优雅！

## 谜底
利用将字符后移两个的转换规则，将url中的map替换为ocr，成功解谜P1第一题，并打开下一题。

http://www.pythonchallenge.com/pc/def/ocr.html

> 规则2：乱排的字符段通常是用来处理并获取谜底的

## Python知识点

- ord()函数返回一个字符的ASCII码
- chr() 将一个数字转换成相应的ASCII字符
- 字符串太长一行写不下，可以写成多行，但要在每行（除最后一行）的结尾使用’\’符号
- ranstab = str.maketrans(intab,outtab) 定义一个转换表，源intab中的每一项分别对应目标outtab中的每一项
- 使用string.translate(transtab)函数，可以调用转换表translab将string中的相应项转换。