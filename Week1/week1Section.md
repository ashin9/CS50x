## Variables and Types

变量名

变量值, 容器放值, 值可变

变量类型, 存储的是什么样的值 ?

= assignment operator , 赋值运算符

```c
int calls = 3;
int courty_code = 65;
```

为什么关注类型 ? 

```c
int courty_code = 65;		// 0100 0001
char courty_code = 65;  // 'A' = 65 = 0100 0001
```



语法糖 `Syntactic sugar` , 方便

```c
int calls = 4;
calls = calls + 2;
calls = calls - 1;
calls = calls * 2;
calls = calls / 2;

--->
int calls = 4;
calls += 1;
calls -= 2;
calls *= 3;
calls /= 2;
```



截断 `Truncation` , 丢掉小数部分

```c
int calls = 4;
calls += 1;
calls -= 2;
calls *= 3;
calls /= 2;			// 值为? 4.5? 4 , 因为存储的是整数
```



## Input and Printing

占位符

- %i int %d decimal 十进制数
- %f float
- %c char
- %s string

```c
#include <stdio.h>

int calls = get_int("Calls: ");
string name = get_name("What's your name ? ")
printf("class is %i\n", calls);
```



## Fucntions

预定义

参数

返回值

## Loops

while

for

## Conditions
