## Data Types

### 标准

Int 

- 4bytes, 32bits, 有符号分正负

- 范围:  

char

- 1 byte , 8bits, 
- ASCII 映射, A 65, a 97

float

- 4 byte, 32bits
- 分整数部分和小数部分, 只有 32bit 可用, 意味着小数部分不够精确, 范围并不清晰

double

- 8 byte , 64bits
- 双精度, 小数部分精确度更高, 目的: 解决精读

void

- 空, 占位符, 认为什么都没有

### cs50.h

bool

- true 或 false

string

- 存储一串字符

### 自定义 Data Types

typedef

### 声明

- 声明名字 + 赋值



## Operators

赋值 = 

- 将左侧值赋给右侧

算数

- +
- -
- *
- /
- % , 模, 取余

boolean expression 布尔表达式

- 0 false
- 非 0, true

逻辑运算符

- &&
- ||
- !

关系运算符

- <
- <=
- \>
- \>=
- ==
- !=



## Conditional

if (boolean-expersion)

elsf if (boolean-expersion)

else



switch(x)

case 1:

case 2:

default:



三元

int x = (expr) ? 5 : 6;



## Loops

while ( true) {}

while ( boolean-exper){}



do {} while (boolean=expr)

- 至少一次, 多用于用户输入检查



for(start; expr; increment)

for(int i = 0; i < 10; i++)





## CLI

ls

cd

mkdir

copy

remove

move



## Magic Numbers

循环数作为变量, 用常量定义

- 当移植或修改时, 只需要修改预处理

预处理

- #define NAME REPLACEMENT
- #define PI 3.14

常量大写