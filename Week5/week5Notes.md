## Data structures

## abstract data types 抽象数据类型

### queues 队列，FIFO，先进先出，公平的方式

- enqueue dequeue

```c
const int CAPACITY = 50;

typedef struct
{
  person people[CAPACITY];
  int size;
} queue;
```



### Stacks 堆栈，FILO，先进后出，不公平方式 ，但用户希望看到最新消息，如：邮箱

- push，pop

```c
typedef struct
{
  person people[CAPCITY];
  int size;
} stack;
```



### arrays 数组，连续内存块，连续存储，随机访问 O(1)（索引，地址+偏移） 

- 静态定义数组，编译时分配内存，大小固定，栈区，自动释放。
- 动态定义数组，手动分配内存，大小可变，堆区，生命周期由程序员控制。访问方式和静态声明一行，还是索引访问，底层都是地址+偏移来访问

### [Resizing Arrays](https://cs50.harvard.edu/x/2024/notes/5/#resizing-arrays)

数组扩容，找够的连续内存，复制过去，再释放原来的，非常耗费时间

- 为什么不一开始静态申请大量内存？因为浪费
- 解决此问题：链表

```c
int main(void)
{
  int *list = malloc(3 * sizeof(int));
  if (list == NULL)
  {
    return 1;
  }
  
  list[0] = 1;
  list[1] = 2;
  list[2] = 3;
  
  int *tmp = malloc(4 * sizeof(int));
  if (tmp == NULL)
  {
    free(list);		// 若前面申请的内存还没释放就返回，造成内存泄漏
    return 1;
  }
  
  for (int i = 0; i < 3; i++)
  {
    tmp[i] = list[i];
  }
  list[3] = 4;
  
  free(list);			// 此时可以释放原来的内存了
  
  list = tmp;			// 更新列表指针，指向新的内存块
  
  return 0;
}
```



### Linked List，链表，随机存储，顺序访问 O(n)

- 额外空间存储，存储下个存储地址，空间换时间
- 首不存数据，指向第一个存储位置，末尾指向 NULL

```c
typedef strcut Node
{
  int data;
  struct Node *next;
} Node;


Node *list = NULL;   // 定义必须指向 NULL，否则可能到处乱指
Node *n = malloc(sizeof(Node)); 

(*n).number = 1;		// *n 解引用指向地址，. 访问结构体成员
n->number = 1;			// 上面的简洁语法

n->next = NULL;			// 最后指向 NULL		
list = n;						// list 指向 n 指向的地址
```

新节点头插法、尾插法，主要是更新指针

- 若孤立一块内存，会导致内存泄漏

头插法：时间 O(1)，副作用是倒序

```c
typedef struct node
{
  int data;
  struct node *next;
} node;


int mian(int argc, char *argv[])
{
  node *list = NULL;
  
  for (int i = 1; i < argc; i++)
  {
    printf("%s\n", argc[i]);
    printf("%i\n", atoi(argc[i]));
    
    // 申请新节点
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
      return 1;
    }
    n->number = number;
    // n->next = NULL;
    
    // 更新指针以链接
    n->next = list;
    list = n;
  }
  
  // 遍历打印，头插倒序打印
  node *ptr = list;
  while (ptr != NULL)
  {
    printf("%i\n", ptr->number);
    ptr = ptr->nextl
  }
}
```

尾插法：O(n)

```c
for (node * ptr = list; ptr != NULL; ptr = ptr->next)
{
  if (ptr->next = NULL)
  {
    ptr->next = n;
    break;
  }
}
```

中间插入：保持顺序

```c
if (list == NULL)
{
  list = n;
}
else if (n->number < list->number)  // 头插
{
  n->next = list;
  list = n;
}
else
{
  for (node *ptr = NULL; ptr != NULL; ptr = ptr->next)
  {
    if (ptr->next == NULL)
    {
      ptr->next = n;
      break;
    }
    
    if (n->number < ptr->next->number)  // 中间插入
    {
      n->next = ptr->next;
      ptr->next = n;
      break;
    }
  }
}
```



按顺序保存数据的好处，分治，增加或缩小数据结构的动力



### Tree，树，链表思想的变体，现实的树倒过来

- 高度：logn，n 为节点数

binary search tree，二叉搜索树，O (logn)，其实和数的高度对应 。多维度思考抽象为树，仍然左右有序，递归的结构

```c
typedef struct node
{
  int data;
  struct node *left;
  struct ndoe *right;
} node;
```



搜索树

```c
bool search(node *tree, int number)
{
  if (tree == NULL)
  {
    return false;
  }
  else if (number < tree->number)
  {
    return search(tree->left, number);  // 递归搜索
  }
  else if (number > tree->number)
  {
    return search(tree->right, number);	// 递归搜素
  }
  else
  {
    return true;
  }
}
```



构建二叉搜索树，和输入顺序有关

- 2，1，3：两边平衡
- 1，2，3：不平衡了，更像一个链表，没有实际的左右

平衡二叉树，插入删除，左右旋转，保持平衡



### Dictionaries，字典，键值对

word : definition

key : value

电话薄



内存中如何实现？

- 链表？O(n)
- 树？O(logn)，用树结构麻烦
- hashing，O(1)





### hashing and hash tables，散列表，数组+链表思想的变体，速度更快

hashing，哈希，映射地址，碰撞特殊处理

hash function

1-26 的数组，每个组存一个链表

- 垂直向使数组
- 水平向使链表

```c
typedef struct node
{
  char *name;
  char *number;
  struct node *next;
} node;

node *table[26];
```



比如：实现电话薄

- 相同姓氏发生冲突？向后插入链表
- 最坏情况，所有人都是相同姓氏，O(n)
- 平均情况，平均分布，O(n/k)，虽然理论任然是 O(n)，但实际应用上效果很大，若真做到平均分布，提升 26 倍

优化：不用链表，都存数组，但会浪费大量空间，空间换时间，若有很好的 hash fucntion，不发生冲突，则可 O(1)



```c
#include <ctype.h>

int hash(char *word)
{
  return toupper(word[0]) - 'A';
}
```



## tries，尝试，不同数据结构混合，数组树

数组，存放树的根

树，存放数据，26 个字母的节点

```c
typedef struct node
{
  struct ndoe *children[26];
  char *number;
} node;

node *try;
```

O(k)，O(n)，取决于名字长度，实际上是个常数

缺点：浪费大量空间



## [Summing Up](https://cs50.harvard.edu/x/2024/notes/5/#summing-up)

In this lesson, you learned about using pointers to build new data structures. Specifically, we delved into…

- Data structures
- Stacks and queues
- Resizing arrays
- Linked lists
- Dictionaries
- Tries
