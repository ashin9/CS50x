## Linear Search

## Binary Search

## Bubble Sort

## Select Sort

找然后与第一个未排序的交换

## Merge Sort



## Recurion

简单, 漂亮, 优雅代码

```c
void recurion(void)
{
   // base case      , 递归边界
   // recursion case , 递归体
}
```

代替非递归中的循环

```c
int fact1(int n)
{
  if (n == 1)
    return 1;
  else
    return n * fact1(n-1);
  
}
```



```c
int fact2(int n)
{
  int product = 1;
  while (n > 0)
  {
    product *= n;
    n--;
  }
  return product;
}
```



Fibonacci number sequence

collatz

