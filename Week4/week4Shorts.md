## Hexadecimal

目的 : 更容易让人阅读理解二进制

- 转二进制
- 转十进制

区别十进制, 0x 前缀

常用表示内存地址等

## Pointers

提供了函数间传递数据的不同方式

变量作用域, 值传递, 传递副本

例子 : swap

SSD HHD -> RAM 易失



数据类型大小

- int 4bytes
- ...
- string ?? 实际是 `char*` , 4 or 8 bytes, 取决于系统



字节序

指针不过是一个地址, 指向变量所在内存位置的地址

函数间传递变量, 传递地址

空指针 NULL, 记得声明指针是初始化为空, 否则容易出问题

`&arr[i]` arr 数组中第 i 个元素的内存地址



声明容易出错地方

```c
int* px, py, pz;		// 实际声明一个指针, 两个整数
int* px, *py, *pz; 	// 这样才声明三个指针
```



## [Defining Custom Types](https://cs50.harvard.edu/x/2024/shorts/defining_custom_types/#defining-custom-types)

```c
typedef <old name> <new name>
typedef char * string;
```



```c
struct car
{
  int year;
  char model[10];
  char plate[7];
  int odometer;
  double engine_size;
};

typedef struct car car_t;

----------> 简写为:
typedef struct car
{
} car_t;
```



## [Dynamic Memory Allocation](https://cs50.harvard.edu/x/2024/shorts/dynamic_memory_allocation/#dynamic-memory-allocation)

问题 : 不知道需要多少内存, 如何访问新内存 ? 比如: 接受用户输入, 但不知道用户输入多大

解决 : 动态分配内存



heap, 动态内存, 由低地址到高地址

stack, 静态内存, 由高地址到低地址



malloc, 找到符合条件的内存, 返回指针/地址

注意 : 第一件事获取指针是否为 null, 异常处理



```c
// statically
int x;

// dynamically
int *px = malloc(sizeof(int));
```



```c
// 动态分配浮点数组
float* heap_arrary = malloc(x * sizeof(float));
```



问题 : 必须手动回收内存

```c
char* word = malloc(50 * sizeof(char));

free(word); // 释放的是指针指向的内存
```

注意 : 别 double free , 可能会造成安全问题



## [Call Stacks](https://cs50.harvard.edu/x/2024/shorts/call_stacks/#call-stacks)

push

pop

例子 : 递归阶乘



## [File Pointers](https://cs50.harvard.edu/x/2024/shorts/file_pointers/#file-pointers)

目的 : 数据持久化

文件 : 数据组织形式



fopen

- r, w, a

fclose



fgetc(file pointer) , 获取下个字符/字节

```c
char ch;
while((ch = fgetc(ptr)) != EOF)
	printf("%c", ch);
```

实现 linux cat 功能

> EOF (End Of File)  io.h 内, 文件结束符

fputs(character, file pointer) , 把字符写入文件

```c
char ch;
while((ch = fgetc(ptr)) != EOF)
  	fputs(ch, ptr2);
```

实现 cp



fread(buffer, size, qty, file pointer) , 从文件读到 buffer

```c
double* arr2 = malloc(sizeof(double) * 80);
fread(arr2, sizeof(double), 80, ptr);
```

8 bytes * 80 = 640 bytes

```c
char c;
fread(&c, sizeof(char), 1, ptr);  // 把一个字节存到 c 中
```





fwrite(buffer, size, qty, file pointer) , 从 buffer 持久化到文件



fgets

fputs

fprintf

fseek

feof

ferror