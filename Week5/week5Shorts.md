## [Data Structures](https://cs50.harvard.edu/x/2024/shorts/data_structures/)

适用什么数据结构，取决于场景需求

### Arrays

- 增删麻烦，中间增删则需要移动大量元素
- 查询快速，随机访问，常量时间
- 排序简单，数据空间相对小，不冗余
- 固定长度，不灵活

### Linked Lists

- 增删简单，常量时间
- 查询麻烦，线性查找
- 排序麻烦，
- 相对较小空间，相比数组肯定不如

### Hash tables

- 增删简单，常量时间
- 查询相比链表平均快得多，考虑现实世界因素
- 排序很麻烦，不是理想的数据结构

- 空间看情况，数组越小，链表越长，不是准确固定的

### Tries

- 插入麻烦，大量动态分配内存，分配好插入简单恒定时间
- 删除简单，free 调 node 即可
- 查找快速，不如数组，但差不多
- 已经排好序，根据构建情况已经排序
- 占用空间很大，



## [Structures](https://cs50.harvard.edu/x/2024/shorts/structures/)

优点在于可自定义封装数据类型，来组合不同的数据类型

- 将逻辑联合的数据绑定分组到一起

```c
struct car
{
  int year;
  char model[10];
  char plate[7];
  int odometer;
  double engine_size;
};
```

访问结构体成员变量

```c
struct car mycar;
mycar.year = 2011;

struct car *mycar = malloc(sizeof(struct car));
(*mycar).year = 2011;  // 解引用到地址，在访问
mycar->year = 2011;		 // 相当于语法糖
```



## [Singly-Linked Lists](https://cs50.harvard.edu/x/2024/shorts/singly_linked_lists/)

node，两个字段，数据内容 + 相同类型node 的指针

```c
typedef struct sllist 	// 临时命名，以便可以在结构体内自引用，因为代码是从上到下解释  
{
  VALUE val;
  struct sllist* next; 	// 自引用数据类型
} sllnode;							// 最后起名
```

 创建链表

- 1，动态申请内存空间
- 2，检查申请空间返回的指针不为 NULL
- 3，设置新 node 的数据内容和下个指针
- 4，返回指针

链表遍历搜索

- 1，创建遍历指针，指向链表头
- 2，遍历查找对比，移动指针
- 3，到链表尾，报错

链表插入单个节点

- 1，动态申请内存，并检查
- 2，头插法，更新指针和链表头，O(1)
- 2，尾插法？O(n)

链表删除单个节点

- 主要是更新指针，无法访问前个 node，一般用双向链表解决

删除整个列表，递归删除

- 1，直到 NULL 指针停止
- 2，删除列表 node，free 掉，递归从后向前删



## [Doubly-Linked Lists](https://cs50.harvard.edu/x/2024/shorts/doubly_linked_lists/)

双向链表，允许指针前后方向移动

占用空间变大，需要权衡利弊

```c
typedef struct dllist
{
  VALUE val;
  struct dllist* prev;
  strcut dllist* next;
} dllnode;
```

双向链表操作和单向链表操作差不多

区别比较大的是增删节点，更新指针



插入新节点

- 1，动态申请内存，并检查指针
- 2，头插，next 指到旧链表头，更新 prev 指针到旧链表头
- 3，更新返回新链表头指针

删除旧节点，解决单向链表的问题

- 1，定位到
- 2，前一个 node 的 next 指向下个 node
- 3，后一个 node 的 prev 指向前个 node
- 4，free



## [Hash Tables](https://cs50.harvard.edu/x/2024/shorts/hash_tables/)

将数组和链表结合，综合两者优点，平均查找删除都是常数时间

缺点：无法排序

hash fucntion ，hash code，好的 hash 方法，使得分布更平均，平均查找性能也就越好

- 仅用数据、用所有数据、确定的、平均分布数据、输入相似数据输出不同 hashcode
- 互联网有很多公开的好 hash 函数，自己创造浪费时间

```c
unsigned int hash(char* str)
{
  int sum = 0;
  for (int j = 0; str[j] != '\0'; j++)
  {
    sum += str[j];
  }
  return sum % HASH_MAX;
}
```

碰撞：两个不同输入，输出相同 hash code

解决碰撞：来回探测放置，当偏离很多时，则失去了哈希表的优势

解决碰撞的缺点：用链表放置碰撞的元素

- 当链表够多时，所有数据平均分布，虽然理论上仍然 O(n)，实际上时间缩短了多倍



## [Tries](https://cs50.harvard.edu/x/2024/shorts/tries/)

key-value，映射来查找信息：

- 数组，元素索引
- 哈希表，数据的 hash code 索引
  - 但是 key 可能冲突

尝试，前提 key 是唯一的，像是多叉树，从头到尾遵循数据图来查找

优点：不同于哈希表，不存在冲突，没有两个数据的路径相同

```c
typedef strcut _trie
{
  char university[20];
  struct _trie* paths[20];  // 存储指向
} trie;
```

构建，用 key 来索引每层的位置

搜索，用数字索引向下每层查找



空间换时间，大量数据流动



## [Queues](https://cs50.harvard.edu/x/2024/shorts/queues/)

Queue，队列，FIFO，保证公平

- enqueue，进队，队尾入队
- dequeue，出队，队首出队



### 基于 array 的队列

```c
typedef struct _queue
{
  VALUE array[CAPCITY];	 // 静态队长
  int front;						 // 跟踪队首，进行出队
  int size;							 // 不跟踪队尾，而是跟踪当前队长
} queue;

queue q;								 // 占用空间：队列长度+front+size 两个标记存储空间
```

enqueue，入队

- 添加数据入队
- 更新队长

```c
void enqueue(queue* q, VALUE data);
```

dequeue，出队

- 删除队首元素？实际上是更新队首指针，假装不存在
- 更新队首和对长
- 返回删除的元素

```c
int x = dequeue(&q);
```

### 基于 Linked List 的队列

```c
typedef struct _queue
{
  VALUE val;
  struct _queue *prev;
  struct _queue *next;
} queue;
```

enqueue，入队

- 动态申请内存，并检查
- 设置 next 指针为 NULL，prev 指针为 tail 链表尾
- 设置链表尾 next 指针为新 node
- 移动尾 tail 指针到新 node

dequeue，出队

- tarv 指针移动到第二个
- free 头节点
- 移动 head 指针到 trav 指针所指
- 设置 node 的 prev 为 NULL



## [Stacks](https://cs50.harvard.edu/x/2024/shorts/stacks/)

Stacks，栈，FILO，先进后出

### 基于 array

```c
typedef struct _stack
{
  VALUE array[CAPACITY];
  int top;				// 追踪栈顶
} stack;

stack s;
```

push，

- 接受指向栈的指针，这样才可以改变堆栈，否则只是传递副本
- 接受添加的数据类型
- 新加数据到栈顶
- 改变栈顶位置

```c
push(&s, 28);
```



pop，

- 改变栈顶位置，不用free，假装数据不见



### 基于 Linked List

```c
typedef struct _stack
{
  VALUE val;
  struct _stack *next;
} stack;
```

push，头插

pop，头删