## Pointers

Address Value

0x50000000 3			// int calls = 3;

0x50000004 0x50000000    // int *p = &calls; 指向上面内存区域的指针

### Key Syntax

- type * 指向类型
- *x 指针 x
- &x 取x地址

### Reasons to use Pointers

- 引用传递, 而非值传递
- 动态内存



## File IO

### fopen

返回指向内存中文件的指针, 类型位 FILE 类型

```c
FILE *f = fopen("hi.txt", "r");
```

### fclose

### fread

把文件读取到 `buffer*`

```c
fread(buffer, 1, 4, from)
```

1 : 文件最小存储单元多大 / 一次性处理的大小单元? 文本 1byte, 图像 3 bytes / 6bytes

4 : 滑动窗口大小 ? 

返回值：读到的字节数

### fwrite

把 `buffer*` 写入文件

### Buffer

临时存储区域

为什么需要 ? 为什么不一次性把文件读入内存 ? 

因为 : 不知道文件多大, 每次读取一小部分

用处 : 使得能够查看文件的某些特定部分, 而不是一次性查看整个文件

### Practice

读取文件头, 检查类型, 比如: PDF 前四字节为: `37, 80, 68, 70`

```c
#include <stdio.h>
#include <stdint.o>

int main(int argc, string argv[])
{
  filename = argv[1];
  FILE *f = fopen(filename, "r");
  
  int buffer[4];    // 不行, 是 16 bytes
  uint8_t buffer[4];
  int blocks_read = fread(buffer, 1, 4, f);
  
  for (int i = 0; i < 4; i++)
  {
    printf("%i\n", buffer[i]);
  }
  printf("%i\n", blocks_read);
    
  fclose(f);
}
```

