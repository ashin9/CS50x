## Welcome

分析文本, 书籍, 等

判断阅读水平, 依据 ? 音节,句子复杂度



加密技术

理解和适应未来新技术



## Compling

make 只是自动化调用了编译器过程

clang 

clang hello.c

- a.out 默认名称 assmebler output
- mv a.out hello 可以, 但麻烦

clang -o hello hello.c

- -o 表示 output

clang 编译

找不到 `get_string` clang 找不到链接库

`-l` 指定非内置的第三方库

```shell
$ clang -o hello hello.c -lcs50		// 链接到 cs50 库
```

make 自动化了上面的流程

- 相当于手动挡, 自动挡



编译四步骤, 预处理, 编译, 汇编, 链接

- preprocessing, 处理引入头文件, 从 `usr/include` 里面找, 头文件替换成函数原型
  - 包含所有内容, 还是部分内容 ?

```c
#include <cs50.h>
预处理变成 ----> 
string get_string(string prompt);  // 函数原型

#include <stdio.h>
int printf(string prompt, ...);
```

- compling, 编译, 转换为汇编语言
  - 计算机理解的低级操作往往是算术上的加减法, 把数据移入和移除内存等
- assembling, 汇编, 转换为机器码 01
- linking, 链接, hello.c cs50.c stdio.c 把编译汇编好的内容链接在一起



decompling , 反编译, 从机器码转回到 c

- 方便分析程序
- 原始代码, 版权问题
- 问题, 变量名, 函数名不会再二进制中保留, 计算机只关心代码逻辑, 而非取了什么漂亮的变量名函数名, 只需要背后的逻辑就够了
- 很难判断是 for 循环还是 while 循环

逆向工程, 相当具有挑战, 耗时, 昂贵

比如拆开 iPhone

## [Debugging](https://cs50.harvard.edu/x/2024/notes/2/#debugging)

bugs

语法错误 ? 

代码逻辑错误, 比如循环多打印了

打印日志输入变量, 观察, 调试 debug

问题 : 手写 printf, 再删掉, 非常麻烦

解决 : debugger 调试器 小虫子标志

- VS Code 内置调试器, 一开始很麻烦, 云环境已经配置好
  - 打断点
- debug50 ./buggy0
  - 断点高亮, 
  - locals, 局部变量
  - continue, 程序结束, 若解决掉 bug 用, 一般最后用
  - Step Over , 调试器运行当前高亮显示的这行代码, 但不会深入它的执行
    - 比如: `printf` 不会深入到内部执行
    - 为什么 ? 因为标准库多年检验, 一般不会出问题的, 问题一般出在程序员编写的代码中
  - Step Into , 跳转到函数内, 看内部细节
    - 比如 : 想研究 `printf` 内部实现细节



C 编译器从上到下读取内容, 所以先上面声明后下面实现

变量作用域 ( scope )  , 变量在最近的 {}, 离开 {} 就被销毁

- 所以 do-while 时, 先在 do 外面声明, 再在while(内用)

橡皮鸭调试法 ddb

GBD GNU Debugger

## [Arrays](https://cs50.harvard.edu/x/2024/notes/2/#arrays)

- `bool` 1 byte
- `int` 4 bytes
- `long` 8 bytes
- `float` 4 bytes
- `double` 8 bytes
- `char` 1 byte
- `string` ? bytes



string

占 ? bytes , 取决于用户输入的长度



 long

- 32 位占 4 bytes
- 64 位占 8 bytes



内存, 分割编号



计算 3 个数的平均分

```c
printf("Average: %d\n", (score1 + score2+ score3) / 3);
// 想要浮点数, 可以直接把分母 3 改为 3.0
printf("Average: %d\n", (score1 + score2+ score3) / 3.0);
// 或者把 3 强制转换为浮点数
printf("Average: %d\n", (score1 + score2+ score3) / (float) 3);
```

直接定义多个分数变量存储设计并不好, 因为当分数很多是, 需要很多变量, 很麻烦

引入 : arrays



Arrays : 数组里面的所有数据, 紧挨着存储在计算机内存中, 这样可以方便地访问每个成员

- 不仅可以作为存储多个值的容器
- 也可作为函数参数传递

```c
int scores[3];		// 告诉计算机分配连续的 3 个 bytes
scores[0] = get_int("Score: ");
scores[1] = get_int("Score: ");
socres[2] = get_int("Score: ");
```

好处, 只需记住一个变量名即可

```c
printf("Average: %d\n", (score[1] + score[2]+ score[3]) / (float) 3);
```

优化

```c
for(int i = 0; i < 3; i++)
{
  scores[i] = get_int("Score: ");
}
```

考虑下内存情况



```c
float average(int array[])
{
  return (scores[0] + scores[1] + scores[2] ) / 3.0;
}
```

magic number , 有些地方, 数字定太死, 如果是程序员的责任, 记住所有硬编码的地方, 就设计的不好

```c
const int N = 3;		// 全局变量

int main(void)
{
  int scores[N];
  for (int i = 0; i < N; i++)
  {
    scores[i] = get_int("Score: ");
  }
}
float average(int array[])
{
  // 循环遍历累加, 再除, 根据 N 来, 而非写死
  int sum = 0;
  for (int i = 0; i < N; i++)
  {
    sum += array[i];
  }
  return sum / (float) N;
}
```

数字长度/大小 ? 其他语言可以, C 得自己弄

全局变量, 顶端看到可以方便

更优方式, 传长度参数到函数里面

```c
float average(int length, int array[])
{
  int sum = 0;
  for (int i = 0; i < length; i++)
  {
    sum += array[i];
  }
  return sum / (float) length;
}
```



## [Strings](https://cs50.harvard.edu/x/2024/notes/2/#strings)

字符串 string

长度可变 ? 底层是连续的字符数字

```c
string s = 'Hi!';
```

问题: 长度可变, 未知大小, 字符的结束如何表示?

解决: 字符串数字尾部增加1 个字节, `\0`  表示结束

```c
s[0] = 'H'
s[1] = 'i'
s[2] = '!
s[3] = '\0'
```

实际存储的数字值为

```c
s[0] = 72
s[1] = 73
s[2] = 33
s[3] = 0
```

\0 表示 NUL, ASCII 码表第一个

全部自动的, 无需手动



字符串 string 未知大小, 所以需要 null 结尾

但是数字知道大小, 无需 null 结尾

```c
char s = {'H', 'i', '!', '\0'};

string s = "Hi!";
printf("%s\n", s);
printf("%c %c %c\n", s[0], s[1], s[2]);
printf("%i %i %i %i\n", s[0], s[1], s[2], s[3]);	// 72 73 33 0
```



```c
string words[2];

words[0] = "Hi!";
words[1] = "BYE!";

printf("%s %s\n", words[0], words[1])

// 二维数组
printf("%c%c%c\n", words[0][0], words[0][1], words[0][2]);
printf("%c%c%c\n", words[1][0], words[1][1], words[2][2]);
```

索引单个字符的值

## [String Length](https://cs50.harvard.edu/x/2024/notes/2/#string-length)

计算字符串长度

```c
name = get_string();

int n = 0;
while(name[n] != '\0')
{
   n++;
}
printf("%i\n", n);
```

使用太多 , 因此string.h 库已经实现计算长度

```c
int n = strlen(name);
```



ctype.h 数据类型库

**大小写转换, 差 32 值**

```c
#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
  string s = get_string("Before: ");
  printf("After: ");
  for (int i = 0; i < strlen(s); i++)
  {
    if (s[i] >= 'a' && s[i] <= 'z')
    {
       printf("%c", s[i] - 32);
    }
    else
    {
      printf("%c", s[i]);
    }
  }
  printf("\n");
}
```

库, 别人已经遇到的问题, 封装好直接调用

```c
#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
  string s = get_string("Before: ");
  printf("After: ");
  for (int i = 0; i < strlen(s); i++)
  {
    if (islower(s[i]))
    {
       printf("%c", toupper(s[i]));
    }
    else
    {
      printf("%c", s[i]);
    }
  }
  printf("\n");
}
```

Toupper 自动判断

```c

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
  string s = get_string("Before: ");
  printf("After: ");
  for (int i = 0; i < strlen(s); i++)
  {
     printf("%c", toupper(s[i]));
  }
  printf("\n");
}
```

**优化, 条件不用每次都计算长度, 只在声明时计算一次存下来即可, 空间换时间**

- 总结 : 计算别放在循环的条件中

```c
for(int i = 0, n = strlen(n); i < n; i++)
```



## [Command-Line Arguments](https://cs50.harvard.edu/x/2024/notes/2/#command-line-arguments)

CLI 参数

解决问题 : 每次先命令, 再交互式等待输入, 麻烦

 ```c
 #include <cs50.h>
 #include <stdio.h>
 
 int main(int argc, string argv[])
 {
    printf("hello, %s\n", argv[1]);
 }
 ```

`argv[0]` 是什么? 程序自己名字

```
$ ./greet dxx
hello, ./greet
```



根据参数个数条件控制流程

```c
#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
  if (argc == 2)
  {
   	printf("hello, %s\n", argv[1]); 
  }
  else
  {
    printf("hello, world\n");
  }
}
```



cowsay

- -f dragon xxx



## [Exit Status](https://cs50.harvard.edu/x/2024/notes/2/#exit-status) 退出状态

404

特殊数字代表某种状态



status.c

```c
int main(int argc, string argv[])
{
  if (argc != 2)
  {
      printf("Missing command-line argument\n");
      return 1;
  }
  else
  {
    	printf("hello, %s\n", argv[1]);
    	return 0;
  }
}
```

echo $? 查看上条命令/程序 的状态码

- 0 值为正常
- 非 0 为不正常



## [Cryptography](https://cs50.harvard.edu/x/2024/notes/2/#cryptography)

密码学

- 输入
  - 明文, key
- 加解密算法
- 输出
  - 密文

凯撒密码, 偏移值

爆破



## [Summing Up](https://cs50.harvard.edu/x/2024/notes/2/#summing-up)

In this lesson, you learned more details about compiling and how data is stored within a computer. Specifically, you learned…

- Generally, how a compiler works.
- How to debug your code using four methods.
- How to utilize arrays within your code.
- How arrays store data in back to back portions of memory.
- How strings are simply arrays of characters.
- How to interact with arrays in your code.
- How command-line arguments can be passed to your programs.
- The basic building-blocks of cryptography.
