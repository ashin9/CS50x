## Functions

黑盒

组织管理

简化

重用

### define

```c
return-type name(argument-list);
```

### calling



## Variable and Scope

全局变量

- 灵活传递信息
- 但有时候会产生危险



### 本地变量传递

值传递, 传递副本而非变量本身

- 意味着操作对原来的无效

```c
int main(void)
{
  int foo = 4;
  foo = triple(foo);
}

int tripe(int x)
{
  return x *= 3;
}
```

重新赋值覆盖, 可以达到想要效果

但是不会改变原来的

```c
int main(void)
{
  int x = 1;
  int y;
  y = increment(x);
  printf("x is %i, y is %i\n", x, y);
}

int increment(int x)
{
  x++;
  return x;
}
```



## Debugging

### Step through

### Step into



## Arrays

数据结构

内存块, 划分为小块

相同类型元素

索引从 0 开始

索引越界

```c
type name[size];

double a[50];
bool a = {tue, false, true};
```

二维数组

```c
bool b[10][10];
```



### 数组赋值

循环赋值

不能直接 =



### 数组传递

引用传递, 传递指针

接受者直接操作数组本身

原因 : 当数组很大时, 需要话费大量时间精力复制



例子, 值传递和引用传递

```c
void set_array(int array[4]);
void set_int(int x);

int main(void)
{
  int a = 10;
  int b[4] = { 0, 1, 2, 3};
  set_int(a);
  set_array(b);
  printf("%d %d\n", a, b[0]);		// 10 22
}

void set_array(int array[4])
{
  array[0] = 22;
}

void set_int(int x)
{
  x = 22;
}
```



## CLI argument

```c
int main(int argc, stirngs argv[])
```

- `argc`, 参数数量
- `argv[]`, 参数
  - `argv[0]` 为程序/命令
  - 空格分隔
  - 接受的是字符串, 需要转为数字
