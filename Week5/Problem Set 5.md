## [Inheritance](https://cs50.harvard.edu/x/2024/psets/5/inheritance/)

### 背景知识

血型：A、B、O，A、B 是显性的，O 是隐形的。

每人携带两个等位基因（alleles），父母各随机遗传给后代一个，共 9 种可能组合。

显示类型共 4 种：A、B、AB、O

### 任务

输入：家族世代大小，整数

输出：每个家族成员分配基因，最老一代随机分配，最后递归释放内存。



## [Speller](https://cs50.harvard.edu/x/2024/psets/5/speller/)

### 背景知识

理论上 O(n) 和 O(2n) 渐进等价，这考虑了输入规模无限大时，但实际中输入规模不大时， O(n) 要比 O(2n) 快一倍

### 任务

实现实际上更快速的拼写检查器。将单词词典从磁盘加载到内存，然后对文件拼写检查

注：随着程序越来越大，将工程拆分解耦，单文件单独实现某一功能，以此实现工程化，用 makefile 来构建

实现 load、hash、size、check、unload

- check 只接受字母字符、标点符号，大小写敏感，只对字典中存在的单词返回 true

- hash 自己想的，而非网上搜的

### 理解

`dictionary.h`

- DICTIONARY_H，确保只编译一次
- 参数 `char *` 表示 `string`
- 参数 const，表示参数不可变

`speller.c`

- 控制参数数量

- 控制默认参数：`char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;`



读取每行单词

```c
while(fscanf(f, "%s", word) != EOF)
```

字符串拷贝，不能直接赋值

字符串比较，大小写不敏感

```c
strcasecmp(p->word, word) == 0
```

头插

```c
n->next = table[index];
table[index] = n;
```

遍历链表

```c
for (node *p = table[index]; p != NULL; p = p->next)
```

删除节点，单链表可以用临时指针，删除临时

```c
node *tmp;

tmp = table[i];
table[i] = table[i]->next;
free(tmp);
```





