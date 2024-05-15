## [Python](https://cs50.harvard.edu/x/2024/notes/6/#python)

站在别人的肩膀上更快完成工作



make clang 编译器，编译执行

python 解释器，解释执行 .py



单引号和双引号差不多，比较宽松



## [Speller](https://cs50.harvard.edu/x/2024/notes/6/#speller)

实现 dictionary.py，精简了很多内存指针操作

```python
words = set()

def check(word):
  return word.lower() in words

def load(dictionary):
  with open(dictionary) as file:
    words.update(file.read().splitlines())
  return true

def size():
  return len(words)

def unload():
  return True
```

缺点：速度慢，占用内存多

python 视为中间人，承担了更多工作



## [Filter](https://cs50.harvard.edu/x/2024/notes/6/#filter)

实现 blur.py

```python
from PIL import Image, ImageFilter

before = Image.open("bridge.bmp")
after = before.filter(ImageFilter.BoxBlur(10))
after.save("out.bmp")
```

实现 edge.py

```python
from PIL import Image, ImageFilter

before = Image.open("bridge.bmp")
after = Image.filter(ImageFilter.FIND_DEGES)
after.save("out.bmp")
```



优势：丰富的库，调用 API 很快完成工作



比如：识别面部

```python
python recognize.py
```



functions



## [CS50 Library](https://cs50.harvard.edu/x/2024/notes/6/#cs50-library)

libraries

```python
import cs50
from cs50 import get_string
```



## [Strings](https://cs50.harvard.edu/x/2024/notes/6/#strings)

同一目标不同实现方式，团队约定

类型变量自动识别

字符串拼接 +

```python
answer = get_string("What's your name?")

answer = input("What's your name?")
print("hello," + answer)
```

参数分割，注意参数前空格也算

```python
print("hello,", answer)
```

格式化串

```python
print("hello, {answer}")  # 忘记 f
print(f"hello, {answer}")
print("hello, {}".format(answer))
```



## [Variables](https://cs50.harvard.edu/x/2024/notes/6/#variables)

弱类型

```python
c = c + 1
c += 1
```



## [Types](https://cs50.harvard.edu/x/2024/notes/6/#types)

- bool
- int
- float，简化 long 和 double
- str



## [Calculator](https://cs50.harvard.edu/x/2024/notes/6/#calculator)

```python
from cs50 import get_int

x = get_int("x: ")
y = get_int("y: ")
print(x + y)	# 3

x = input("x: ")
y = input("y: ")
print(x + y)   # 12 当做字符串链接

# 解决: 类型转换
x = int(input("x: "))
y = int(input("y: "))
print(int(x) + int(y))
```



range

list

tuple

dict

set



报错回溯：Traceback



导入

```python
import cs50
cs50.get_int()

from cs50 import get_int, get_string
get_int()
```



## [Conditionals](https://cs50.harvard.edu/x/2024/notes/6/#conditionals) 条件

```python
if x < y:
  print("x is less than y")
elif x > y:
  print("x is greater than y")
else:
  print("x is equal to y")
```

缩进很重要



str



compare

```python
if s == t:
	print("Same")
else:
	print("Different")
```

c 语言两个字符串直接比较，实际是比较 char * 即字符串的地址，肯定不同，因此必须使用字符串比较

py 直接比较字符串内容



agree.c

```python
s = input("Do you agree? ")

if s == "Y" || s == "y":
  print("Agreed")
elif s == "N" || s == "n":
  print("Not Agreed")
```



in

```python
if s in ["y", "yes", "Y"]:
  print("Agreed")
elif s in ["n", "no", "N", "No"]:
  print("Not Agreed")
```



## [Object-Oriented Programming](https://cs50.harvard.edu/x/2024/notes/6/#object-oriented-programming) oop

内置方法

```python
s = s.lower()

if s in ["y", "yes"]:
```

```python
s = input("Do you agree? ").lower()
```



uppercase.py

```
```



docs.python.org



## [Loops](https://cs50.harvard.edu/x/2024/notes/6/#loops)

```python
i = 0
while i < 3:
  print("mew")
  i++
```



```python
for i in [0, 1, 2]:		# 问题: 遍历更多？
  print(i)

for i in range(3):
  print(i)
```

Pythonic 思想



```python
for _ in range(3):
  print("meow")
```



```python
while True:
  print("meow")
```



print end 默认为 `\n`，可修改

```python
print("After:  ", end="")
```



```python
before = input("Before: ")
print("After:  ", end="")
for c in before:
  print(c.upper(), end="")  # 遍历每个字符，顺序打印不换行
print()		# 最后换行
```

更简单方式：

```python
print(f"After: {before.upper()}")
```



named parameters



Positional parameters



## [Abstraction](https://cs50.harvard.edu/x/2024/notes/6/#abstraction)

def

```python
def meow():
	print("meow")
  
meow()
meow()

for i in range(3):
  meow()
```

理解任然从上到下



```python
def main():
  for i in range(3):
    meow()

def meow():
  print("meow")

main() # 调用
```



参数

```python
def main():
  meow(5)

def meow(n):
  for i in range(n):
  	print("meow")

main() # 调用
```



## [Truncation and Floating Point Imprecision](https://cs50.harvard.edu/x/2024/notes/6/#truncation-and-floating-point-imprecision)

```python
x = int(input("x: "))
y = int(input("y: "))

z = x / y
print(z)  # 若 1/3 自动转换为小数，比 c 智能

print(f"{z:.50f}")	# 精度，超过多少位就不精确了
```

integer overflow？c 中溢出会变 0 甚至负数，py 不存在，内存站位动态变化越占越多，但仍会丢失精度



## [Exceptions](https://cs50.harvard.edu/x/2024/notes/6/#exceptions)

```python
def get_int(prompt):
  return int(input(prompt))
```

输入非数字报错



c语言中处理错误情况，唯一方法是返回特殊值

异常，处理错误情况

Value Error，

```python
def get_int(prompt):
  try:
    return int(input(prompt))
  except ValueError:
    print("Not an interger")
```

不断获取输入

```python
def get_int(prompt):
  while True:
    try:
      return int(input(prompt))
    except ValueError:
      print("Not an interger")
```

跳过错误

```python
def get_int(prompt):
  while True:
    try:
      return int(input(prompt))
    except ValueError:
      pass
```



## [Mario](https://cs50.harvard.edu/x/2024/notes/6/#mario)

竖着的

```python
while True:
  n = int(input("Height: "))
  if n > 0:
    break

for i in range(n):
  print("#")
```

横着的

```python
for i in range(4):
  print("?", end="")
print()

print("?" * 4)
```

方格

```python
for i in range(4):
  for j in range(3):
    print("#", end="")
  print()

for i in range(4):
  print("#" * 3)
```



## [Lists](https://cs50.harvard.edu/x/2024/notes/6/#lists)

scires

- sum()、len()

```python
scores = [72, 73, 33]

average = sum(scores) / len(scores)
print(f"Average: {average}")
```

append() 附加，尾指针添加

```python
scores = []
for i in range(3):
  score = int(input("Score: "))
  scores.append(score)

average = sum(scores) / len(scores)
print(f"Average: {average}")

scores = scores + [score] # 累加
```



Phonebook

线性查找

```python
names = ["dxx", "David", "John"]

name = input("Name: ")

for n in names:
  if n in name:
    print("Found")
    break
  else:
    print("Not found")	# 输入 David, 输出 Not found Found, 因为遍历
```



```python
names = ["dxx", "David", "John"]

name = input("Name: ")

for n in names:
  if n in name:
    print("Found")
    break
  else:
    print("Not found")
    break
```



实际上 for 也有 else

```python
names = ["dxx", "David", "John"]

name = input("Name: ")

for n in names:
  if n in name:
    print("Found")
    break
else:
  print("Not found")
```



化简，让 py 完成循环

```python
names = ["dxx", "David", "John"]

name = input("Name: ")

if name in names:
  print("Found")
else:
  print("Not Found")
```



## [Searching and Dictionaries](https://cs50.harvard.edu/x/2024/notes/6/#searching-and-dictionaries)

k-v，本质是哈希表

```python
people = [
  {"name": "Carter", "number": "+1-123456"},
  {...}
]
```

遍历 dict

```python
name = input("Name: ")

for person in people:
	if person["name"] == name:
  	number = person["number"]
  	print(f"Found {number}")
    break
else:
  print("Not Found")
```

优化

```python
name = input("Name: ")

for person in people:
	if person["name"] == name:
  	print(f"Found {person['number']}")
    break
else:
  print("Not Found")
```

重新构建字典

```python
people = [
  "Carter": "+1-123456"
  {...}
]
```

优化方法

```python
name = input("Name: ")

if name in people:
  number = people[name]
  print(f"Found {number}")
else:
  print("Not found")
```



## [Command-Line Arguments](https://cs50.harvard.edu/x/2024/notes/6/#command-line-arguments)

sys 库

```python
from sys import argv

if len(argv) == 2:
  print(f"Hello, {argv[1]}")
else:
  print("hello, world")
```

argv 忽略shell 的 python

- `python hello.py dxx` argv 长度为 2

```python
import sys

if len(sys.argv) != 2:
  print("Missing CLI argument")
  sys.exit(1)
else:
  print(f"hello, {sys.argv[1]}")
  sys.exit(0)
```



## [Exit Status](https://cs50.harvard.edu/x/2024/notes/6/#exit-status)

exit 码相当于 return



## [Third-Party Libraries](https://cs50.harvard.edu/x/2024/notes/6/#third-party-libraries)

pip

```shell
pip install xxxx
```



qrcode 库

```python
import qrcode

img = qrcode.make("")
img.save("qr.png", "PNG")
```



## [Summing Up](https://cs50.harvard.edu/x/2024/notes/6/#summing-up)

In this lesson, you learned how the building blocks of programming from prior lessons can be implemented within Python. Further, you learned about how Python allowed for more simplified code. Also, you learned how to utilize various Python libraries. In the end, you learned that your skills as a programmer are not limited to a single programming language. Already, you are seeing how you are discovering a new way of learning through this course that could serve you in any programming language – and, perhaps, in nearly any avenue of learning! Specifically, we discussed…

- Python
- Variables
- Conditionals
- Loops
- Types
- Object-Oriented programming
- Truncation and floating point imprecision
- Exceptions
- Dictionaries
- Command-line arguments
- Third-Party libraries
