## Pixel Art

位图, 一个 bit 表示颜色

- 1 代表白
- 0 代表黑

RGB 通道概念

- 000 黑色
- 255 225 255 白色

用六位数字, 有时候三位就够, 简洁地表示一定数量的红绿蓝

- `#0000FF` 表示 0 0 255 , 只是换了一种表述而已

## Hexadecimal

bin dec hex

二进制 十进制 十六进制

hex , base-16

- 0-9 , 不够用了, 用 ABCDEF     
- 0x0F

- 4ibt 够 1-15
- 简洁地表示出二进制数, 比如: 1111 1111 , 用 FF 简洁表示
- 描述内存中的位置, 地址

问题 : 10 可能被认为是十进制 10

解决: 表面用十六进制, 前缀 `0x10`



## Memory

Segment Fault 内存段错误

内存地址



`&` 取地址符, 获取内存一段数剑的地址

`*` 解引用运算符, 转到特定地址去



`%p` 打印地址

```c
int n = 50;
printf("%p\n", &n);
```

 

## Pointers 指针

操作内存, 但权力越大责任越大, 写出 bug 操作内存, 容易破坏程序

本质 : 一个变量, 存储了某个值的内存地址

指针类型, 是指向内存的类型



```c
int n = 50;
int *p = &n;
printf("%p\n", p);
```

可以拿到所存储数据的内存地址

OS 虚拟内存 : 同设备上, 重复运行此程序, 可能每次地址都一样

用处 : 组织内存构造数据结构, 不止是一维, 可以是二三维



指针大小, 占用多少 bytes ? 现代 8 bytes , 4bytes 32 位最大 4G 内存, 不够表示



双重指针 `**`, 两个指针互相指向



## String

```c
string s = "HI!";
```

内存开辟空间, 存放 `HI!` 和 `\0` 

s 呢 ? s 本身也需要占用一定空间

string 如何工作的 ?

- 其实 s 是一个指针
- 赋值字符串的第一个地址给 s 指针, 无需所有字符的地址
- 直到第一个字节位置, 就可以顺序向后查找了

c 语言本身没有 string 关键字, 其实是指向 `char` 的指针

-  string 符合直觉, 为了方便使用把 `char *` 抽象出来

```c
string s = "HI!";
char *s = "HI!";
```



如何抽象封装的 ? 

```c
typedef int integer; 	// 给 int 起了个别名
typedef char *stirng; 
```

string.h 库和 string 没任何关系, cs50.h 实现的



解引用, `*p` 解引用指针 p, 到所指的地址去

```c
int n = 50;
int *p = &n;
printf("%s\n", *p);
```



同一个 `*` 号, 发挥两种作用

解引用不用说明数据类型, 数据声明后就用不到再说明数据类型了



指针, 可以根据变量名得到他的地址, 然后反过来从地址取到那个变量



*号位置, 靠近那边都可以

```c
char *s = "HI!";
char* s = "HI!";

char* a,b;  // 注意: 不是声明两个指针变量
```



```c
char *s = "HI!";
printf("%p\n", s);		// 打印内存地址
printf("%s\n", s);		// 打印字符串内容, %s 指引到字符串内容, 不用加 * 解引用
printf("%s\n", *s);		// 转到地址的一个字符去
```

没有 string 关键字, 但是有 `%s`



下面两者都是打印内存地址, 且相同

字符串地址就是首字符的地址

```c
printf("%p\n", s);			// 打印内存地址
printf("%p\n", &s[0]);	// 打印内存地址, 首字符的地址
```



```c
printf("%p\n", &s[0]);
printf("%p\n", &s[1]);
printf("%p\n", &s[2]);
printf("%p\n", &s[3]);
```

打印的地址是连续的



## Pointer Arithmetic

指针算术运算

- 此处 * 是解引用

```c
printf("%c\n", *s);
printf("%c\n", *(s+1));
printf("%c\n", *(s+2));
printf("%c\n", *(s+3));
```

`s[0]` 是上面的语法糖, 本质底层转换成是上面这样



意味着可以去内存的任何地方, 很危险

```c
printf("%c\n", *(s+5000));
```

段错误

程序运行时, OS 分配给一段内存段, 越过就段错误

黑客, 从内存四处跳转, 搜查存储在内存中有用的东西, 比如: 密码, 财务信息等



```c
char *s = "HI!";

printf("%s\n", s);		// HI!
printf("%s\n", s+1); 	// I!
printf("%s\n", s+2); 	// !
```

`%s` 从字符串首地址打印到 `\0`

编译器智能识别步长, `+1` 为下一个字节 



## String Comparsion

为什么用 `strcmp` 而不是直接用 `==` ? 

- `==` 比较字符串首字母的内存地址, 而非逐个字符串比较



```c
int s = get_int("s: ");
int t = get_int("t: ");

if (s==t)
  printf("Same\n");
else
  printf("Different\n");
```



```c
string s = get_string("s: ");
string t = get_string("t: ");

if (s==t)
  printf("Same\n");
else
  printf("Different\n");
```

输入 : `HI!` 会输出 `Different`

因为比较了内存地址, 而非内容

实际是两段内存空间都存储了 "HI!"



```c
#include <string.h>

string s = get_string("s: ");
string t = get_string("t: ");

if (strcmp(s, t) == 0)
  printf("Same\n");
else
  printf("Different\n");
```

为什么 int 可以, string 不可以 ? stirng 比较特殊, 太常见了, 所以抽象封装了

- 其他数据类型是存储的值, 而字符串是存储的首字母地址

- 本质是字符数组, 用指针存字符串首字母地址

```c
if (*s == *t)  // 比较字符串首字母内容
if (*s == *t && *(s+1) == *(t+1) && *(s+2) == *(t+2)) // 挨个比较字符串每个字符
```



## Copy

```c
string s = get_string("s: ");

string t = s;						// 复制 s 到 t, 本质是复制的首字母地址, s 和 t 都指向相同内存

t[0] = toupper(t[0]);		// 把首字母大写

printf("%s\n", s);			// s 首字母也随着改变
printf("%s\n", t);			// 首字母大写
```

改进, 丢掉 string, 改进输入为空时特殊处理

```c
char *s = get_string("s: ");

char *t = s;						

if (strlen(t) > 0)
{
  t[0] = toupper(t[0]);		
}

printf("%s\n", s);			
printf("%s\n", t);
```



这就是传说中的引用传递 ? 



## malloc free

内存分配, 释放

找到内存首地址

风险 : 依赖程序员记忆分配了多少内存

死机 / 内存不断增加 : 常见原因就是程序不断申请内存, 但永远没有 free, 计算机耗尽内存, 崩溃

头文件 : `stdlib.c`

```c
char *s = get_string("s: ");
char *t = malloc(strlen(s) + 1); // +1 用来末尾加上 \0

for (int i = 0; i < strlen(s) + 1; i++) // +1 复制末尾 \0
{
  t[i] = s[i];			// 挨个复制
}

if (strlen(t) > 0)
{
  t[0] = toupper(t[0]);
}
```



```c
for (int i = 0; i < strlen(s); i++)
{
  t[i] = s[i];
}
t[strlen(s)] = '\0';  // 等价
```



优化 : 多次调用 `strlen(s)`, 在条件中用`strlen(s)` 可以存下来, 之后用

```c
for (int i = 0, n = strlen(s) + 1; i < len; i++)
{
  t[i] = s[i];
}
```

当然, 现代编译器, 比如 clang 能自动隐式做出优化



改进, 直接用 api , 省掉循环

```c
strcpt(t, s);
```



`NULL` 是 `0` 的别名

```c
char *s = get_string("s: ");
if (s == NULL)
{
  return 1;
}
```

虽然臃肿, 但实际必须这样写



最后手动 malloc 的内存别忘记释放

```c
free(t)
```

有工具自动检测此问题



memory.c

```c
int *x = malloc(3 * sizeof(int));

x[1] = 72;
x[2] = 73;
x[3] = 33;
```

改错

```c
int *x = malloc(3 * sizeof(int));

x[0] = 72;
x[1] = 73;
x[2] = 33;

free(x);
```



## Valgrind

valgrind 查找内存问题

提供线索

```c
int *x = malloc(3 * sizeof(int));
if (x == NULL)
{
  return 1;
}
x[0] = 72;
x[1] = 73;
x[2] = 33;

free(x);

return 0;
```



稍大的程序, 同一片内存可能被反复地分配和释放, 一会被使用, 过一会又没有

默认, 内存会有大量垃圾值



## Garbage Values

注意 : 变量初始化



## [Pointer Fun with Binky](https://cs50.harvard.edu/x/2024/notes/4/#pointer-fun-with-binky)

```c
int main(void)
{
  int *x;
  int *y;
  
  x = malloc(sizeof(int));
  
  *x = 42;
  
  y = x;
  
  *y = 13;
}
```



## [Swap](https://cs50.harvard.edu/x/2024/notes/4/#swap)

交换变量值, 例子 : 交换酒, 需要第三个空杯子

```c
void swap(int a, int b)
{
  int tmp = a;
  a = b;
  b = a;
}
```

例子, 交换没变化

- 原因 :
  - 值传递, 实际传的是值的副本
  - 作用域 Scope
- 解决 : 引用传递

```c
void swap(int x, int y);

int mian(void)
{
  int x = 1;
  int y = 2;
  
  printf("x is %i, y is %i\n", x, y);  // x is 1, y is 2
  swap(x, y);
  printf("x is %i, y is %i\n", x, y);	 // x is 1, y is 2, 没变化没交换
}

void swap(int a, int b)
{
  int tmp = a;
  a = b;
  b = tmp;
}
```



运行程序, 将程序加载到内存 RAM

- 机器码
- 全局变量
- 堆, malloc 申请, 从上到下, 低地址到高地址 
- 栈, 从下到上, 高地址到低地址



swap 栈帧

- main, x, y, 
- swap, tmp a b ,a b 接受 x y 的值传递, 执行完后栈帧释放, 回溯到 main



解决, 引用传递

- swap 作用域中 x 指向 main 作用域的 a 地址, y 指向 b 地址
- 解决本地作用域的问题, 访问其它函数里面的东西

```c
int swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int mian(void)
{
  int x = 1;
  int y = 2;
  
  printf("x is %i, y is %i\n", x, y);
  swap(&x, &y);   // 传递地址
  printf("x is %i, y is %i\n", x, y);
}
```



## [Overflow](https://cs50.harvard.edu/x/2024/notes/4/#overflow)

堆溢出, heap overflow

栈溢出, stack overflow

触及到不该访问的地方



## [`scanf`](https://cs50.harvard.edu/x/2024/notes/4/#scanf)

scanf 实现 cs50 的 get_int

```c
int x;
printf("x: ");
scanf("%i", &x);		// 引用传递, 传递给地址
printf("x: %i\n", x);
```



```c
char *s = NULL;
printf("s:");
scanf("%s", s); 		// 不用引用传递, 以为 s 本身已经是地址 
printf("s: %s\n", s);
```

问题 : 存不了输入, 没有

用数组, 可以把数组看成指针, 编译器做一些隐式转换

```c
char s[4];
```

问题: 输入 4 字符可以,但长字符没足够空间, 会自动截断, 忽略掉后面的输入

但不能用`s[4000]` 



## [File I/O](https://cs50.harvard.edu/x/2024/notes/4/#file-io)

phonebook.c

持久化存储

```c
FILE *file = fopen("", "a");		// 把磁盘文件读进内存, 返回指向文件开头的指针, a append 模式, 追加

string name = get_string("Name: ");
string number = get_string("Number: ");

fprintf(file, "%s, %s\n", name, number);

fclose(file);
```



bmp 位图

## [Summing Up](https://cs50.harvard.edu/x/2024/notes/4/#summing-up)

In this lesson, you learned about pointers that provide you with the ability to access and manipulate data at specific memory locations. Specifically, we delved into…

- Pixel art
- Hexadecimal
- Memory
- Pointers
- Strings
- Pointer Arithmetic
- String Comparison
- Copying
- malloc and Valgrind
- Garbage values
- Swapping
- Overflow
- `scanf`
- File I/O
