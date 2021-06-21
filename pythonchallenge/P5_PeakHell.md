# Peak Hell

解谜P4后，转至第五题P5，其url如下

http://www.pythonchallenge.com/pc/def/peak.html

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p5_1.png)

一张图，图上是一个绿色的小山头，下面的文字提示“pronounce it”。不明所以，再打开网页源码找找线索。

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p5_2.png)

源码中有一段提示“peak hell sounds familiar ?” 又是再提示发音，peak hell？hell难道是hill(山) ？ peak难道是“pic”（picture,图片）或者“pick”（摘，选择）？

源码中还有一个链接，src="banner.p"，打开banner.p看看。

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchallenge_p5_3.png)

又是一堆字符（老招数了都）。banner是“旗帜，标语”的意思

实在琢磨不透，万般无奈，我选择在网上找资料，总不能一直卡在这里了。找到资料http://www.iainbenson.com/programming/Python/Challenge/solution5.php，才明白，原来peak hell是指python中的pickle模块(只能说自己python不熟啊)。代码如下（来自该资料）

```python
import pickle
from urllib.request import urlopen

fd = urlopen("http://www.pythonchallenge.com/pc/def/banner.p")
banner = pickle.load(fd)
print(banner)
for item in banner:
    print("".join(i[0] * i[1] for i in item)) #print characters[/python]
```

运行输出

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/pythonchanllege_p5_4.png)

这里的代码写的就比较高级了，作为初学者看了很久才明白。但不妨碍，结果还是出来了channel。

## 解谜
将url中的peak替换成channel，即可解谜开启下一题

http://www.pythonchallenge.com/pc/def/channel.html

## Python知识点
这题以学知识为主吧，不到万不得已，一定要自己找思路。

- pickle
- string.join()
- i[0] * i[1] for i in item 的用法理解

### pickle

Python提供的持久存储(序列化)模块,可将任何一个Python对象存储到文件中,然后再从文件中取出来.

```python
pickle.dump(obj, file[, protocol=0])
```

使用dump()函数将一个Python对象obj序列化到file文件中。

```python
obj = pickle.load(file)
```

使用load()函数加载一个序列化的文件，取出其中存储的Python对象

### string.join(str)

以string为分隔符，将str中的所有元素合并成一个字符串。

```python
print "@".join("abcd")#输出：a@b@c@d
```

### i[0] * i[1] for i in item 的用法理解

首先理解i[0]*i[1].本题中i[0]是一个字符，i[1]是一个数字，两者相乘的意思是将前一个对象i[0]重复i[1]次得到一个新的对象。例子如下：

```python
print('a'*5) #输出aaaaa
print([1,2]*3) #输出[1, 2, 1, 2, 1, 2]
```

再理解 i for i in item 这条语句，目前先记住它在join中的用法吧。