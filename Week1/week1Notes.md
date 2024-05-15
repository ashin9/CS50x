## Welcome

Scratch GUI 编程, 概念有用



各种符号 思维模型

源代码 : 

计算机不理解

机器码

源代码 -> 编译器 -> 机器码

编译器

优秀的代码, 反复练习

- correctness , 正确性首要

- design , 设计, 更主观
  - 更快, 易于维护
- style , 代码美学, 计算机不关心, 人关心



## Hello World

编辑器 : VS Code , 文本代码

- 标签页, 文件
- 终端窗口, 命令行界面 , CLI 相对 GUI, 程序员更青睐 CLI, 因为键盘打字更快
- 文件管理器, 分层树形结构



编辑

```shell
$ code hello.c
```

编译运行

```shell
$ make hello
$ ./hello			# ./ 当前目录 CLI运行, 等价于 GUI 双击
```



stuidio

stdio

愚蠢的错误, 随着时间推移



打开二进制文件, 不会对人有什么启发, 所以IDE很少展示



自动代码上色, 可自定义配色, 主题



联系 Scratch 中的 hello world



## Functions

函数 function

say - printf()

- 椭圆 ()
- 字符串, 双引号
- \n , 
- ;



忘记;

clear

重新编译

报错分析, 5 行 29 个字符

解决问题

那些行需要加;?



\n 删除

- 不会换行, $跟在 hello world 后面
- \n 代表换行

理想状况 : 换行便于使用



直接换行代码

- 保持在同一行



main() 看成启动程序凡方式



删除 include

头文件 , 引入

- .h

- stand input output = stdio.h

手册, 简化版

cs50.h



get_char

get_double

get_float

...



返回值

 get_string("What's your name? ")



## Variables

变量

answer = get_string("What's your name? ")

赋值, 从右到左

存到变量中, 重用函数返回值



变量类型

string answer = get_string("What's your name? ");



join -> 

占位符 %s , 特殊处理表示插入某个值, 替换

printf("hello, %s \\n", answer );

两个占位符

%如何表示 ? %%



数据类型



## Conditionals

条件语句

bool 表达式周边括号

{} 形象理解包裹

if 

else

三叉

else if



比较相等 == 和 赋值 =

类似解决%用%%



优化 else if , 最后一种情况 else 即可



compare.c

code 重新打开, 不会新创建



人决定变量类型

{ 自动补充

箭头选择以前的命令

修改代码重新编译



开头括号需要另起一行吗? cs50 需要, 只是不同风格



取单个字符, 判断是否是某字符

```c
char c = get_char("...");
if (c=='y')
{
  ...
}
```

单引号

大小写敏感



组合 bool 表达式 逻辑, 优化分支 

```shell
if ( c == 'y' || c == 'Y')
```

忽略大小写的函数



输入不合法 ? 

- 字符串 , 输入不合法
- 其他没判断到的字符, 没其他流程结束



## Loops

循环

变量

- 初始化
- 右到左赋值

```c
int cout = 0;
```

语法糖

```c
cout = cout + 1
cout += 1
```

类比 Scratch

```c
int cout = 3;
while ( cout > 0 )
{
  printf("meow\n");
  // cout -= 1;
  cout--;
}
```



存储减内容



变法

```c
int i = 1;
while ( i <= 3)
{
  printf("meow\n");
  i++;
}
```

变法, 最经典, 符合人思考

```c
int i = 0;
while ( i < 3 )
{
  printf("meow\n");
  i++;
}
```



repeat - for 循环

- 两分号, 三表达式
- 初始化只执行一次, 不会再次 i=0

```c
for ( int i = 0; i < 3; i++ )
{
  pirntf("meow\n");
}
```



forever - while(true)

- 检查碰撞, 检查等待输入

```c
while(true)					// 得引入 #include<stdbool.h>
{
  printf("meow\n");
}
while(1)
```

退出死循环, ctrl - c



## Linux CLI

- 一些简单的命令, 缩写
- ls list , 
- 有*, 表示可执行, 权限问题, 
- mv
- 蓝色/ 文件夹
- cd change dir 切换文件夹
- cp
- mkdir
- rm
- rmdir

GUI vs CLI

云容器



## Mario

涉及图形和音频编码

超级玛丽, 循环打印?

\n 位置

```c
for (int i = 0; i < 4; i++)
{
  printf("?");
}
pirntf("\n");
```

打印竖墙 #

```c
for (int i = 0; i < 4; i++)
{
  printf("#\n");
}
```

打印网格块, 双重循环

```c
for (int i = 0; i < 3; i++)
{
  for (int j = 0; j < 3; j++)		// 不能用 i 了, 避免冲突
  {
    printf("#");
  }
  printf("\n");								 	// 换行控制
}
```

改变长短, 变量控制

```c
int n = 5;
for (int i = 0; i < n; i++)
{
  for (int j = 0; j < n; j++)		// 不能用 i 了, 避免冲突
  {
    printf("#");
  }
  printf("\n");								 	// 换行控制
}
```

可能中间不小心用了 n++, 用 `const` 声明不可变, 增加代码健壮性, 防御性更强

```c
const int n = 5;
```

代码可读性

代码格式化



具有动态性, n 自定义

```c
# include <cs50.h>

int n = get_int("Size: ");
```

输入字符 ? 负数 ? 已处理

输入错误再次获取输入 ? 

```c
int n = get_int("Size: ");
while (n < 1)
{
  n = get_int("Size: ");
}
```

改成 do while

```c
int n;
do
{
  n = get_int("Size: ");
}
while (n < 1);
```

一次后再循环, 其他语言很少有

场景 : 获取用户输入, 并检查时



## Comments

注释 // 灰色, 让人理解代码干什么



抽象: 读取和打印封装为函数

- return 返回值
- void 空返回值声明
- 参数, 类型, 名称
- 放到 main 下面, 会报错找不到, 因为按顺序从上到下查找
- 放到 main 上面, 导致 main 靠下, 很难找到
- 解决 : 上面声明, 下面实现

```c
#include <stdio.io>
#include <cs50.h>

int get_size(void);
void print_grid(int size);

int main(void)
{
  int n = get_size();
  print_grid(n);
}

int get_size(void)
{
  int n;
  do
  {
    n = get_n("Size: ");
  }
  while( n < 1);
  return n;
}

void print_grid(int size)
{
  for (int i = 0; i < size; i++)
  {
    for ( int j = 0; j < size; j++)
    {
      printf("#");
    }
    printf("\n");
  }
}
```

解决过程冗杂, 但设计更好, main 中只有两行代码即可

把核心部分拆解解耦



## Operators

计算器, 20亿 + 20 亿 ? 整数溢出 overflow

```c
#include <stdio.h>
#include <cs50.h>

int main(void)
{
  int x = get_int("get x : ");
  int y = get_int("get y : ");
  
  printf("%i \n", x + y);
}
```

int 32 bit, 所以 bit 都设 1, 最大 4294967295

有符号, 最大 4294967295 一半

连续进位, 产生截断, 只保留了有的位

- *Operators* refer to the mathematical operations that are supported by your compiler. In C, these mathematical operators include:
  - `+` for addition
  - `-` for subtraction
  - `*` for multiplication
  - `/` for division
  - `%` for remainder



long

```c
#include <stdio.h>
#include <cs50.h>

int main(void)
{
  long x = get_long("get x : ");
  long y = get_long("get y : ");
  
  printf("%li \n",  x / y );
}
```

格式化

- %c
- %f
- %i

- %li
- %s

整数除法得 0



## Types

浮点数

```c
#include <stdio.h>
#include <cs50.h>

int main(void)
{
  long x = get_long("get x : ");
  long y = get_long("get y : ");
  
  float z = x / y;
  printf("%f \n",  z );
}
```

结果仍然是 0, 0.000, 同整数, 只不过结果=0 给了浮点数, 没小数部分

强制类型转换

```c
float z = (float) x / (float) y
```

浮点数不精确性, 存储近似值

第几位小数

```c
pirntf("%.20f\n", z)
```

解决 : double, 更多位存储, 更精确些, 不完美, 但好多了

```c
double z = (doulble) x / (double) y
printf("%.20f\n", z)
```

py 自动算需要多少位决定数据类型

只用两位数字存储年份问题

**决定用 32bit 从 1970.1.1 开始计算时间流逝多少 s**

**2038 1.19 有些计算机存储时间的 bit 位将用尽, 无法继续跟踪时间**



## [Summing Up](https://cs50.harvard.edu/x/2024/notes/1/#summing-up)

In this lesson, you learned how to apply the building blocks you learned in Scratch to the C programming language. You learned…

- How to create your first program in C.
- Predefined functions that come natively with C and how to implement your own functions.
- How to use variables, conditionals, and loops.
- How to approach abstraction to simplify and improve your code.
- How to approach problem-solving for a computer science problem.
- How to use the Linux command line.
- How to integrate comments into your code.
- How to utilize types and operators.
