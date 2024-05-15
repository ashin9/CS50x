## node

分量块看

```c
struct node
{
  xxx;
}

typedef xxx
{
  
} node;
```



## 创建 linked list

```c
node *list = NULL;
node *n = malloc(sizeof(node));
n->phrase = "Hi!";
n->next = NULL;
```



## insrting and unloading Linked List



```c
node *n = malloc(sizeof(node));
if (n == NULL)
{
  return 1;
}

n->phrase = phrase;
n->next = NULL;

n->next = list;
list = n;
```



```c
node *ptr = list;

while (ptr != NULL)
{
  ptr = list->next;
  free(list);
  list = ptr;
}
```

 

## hash table



```c
int hash(string phrase)
{
  return toupper(phrase[0]) - 'A';
  // return tolower(phrase[0]) - 'a';  // 两种方式都可
}
```



## Inheritance

create_family，递归创建



rand() % 2，随机两种可能

