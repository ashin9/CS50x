## Welcome Algorithms

对数算法, 及时把电话薄大小增加一倍,  也没什么大不了的, 仅仅是多撕一次, 就可以把多的 1000 页去掉了

计算机每次只能做一次事, 不可能把内存一切尽收眼底, 马上找到

数组可以把抽象出的内存概念, 与实际代码相结合



## [Linear Search ](https://cs50.harvard.edu/x/2024/notes/3/#linear-search)线性查找

打开每个盒子, 就像询问每次内存, 然后判断

伪代码到代码

```
for i from 0 to n-1
	if 50 is behind dorrs[i]
		return true
return false
```

## [Binary Search](https://cs50.harvard.edu/x/2024/notes/3/#binary-search) 二分查找, 前提: 排好序

```
if no doors left
	return false
if 50 is behind doors[middle]
	return true
else if 50 < doors[middle]
	search doors[0] through doors[middle -1]
else if 50 > doors[middle]
	search doors[middle + 1] through doors[n - 1]
```

## [Running Time](https://cs50.harvard.edu/x/2024/notes/3/#running-time)

排序代价

大体估算, 上界$O()$ 最坏情况, 下界$\Omega()$ 最好情况

- 省略小阶项
- 趋近于无穷时的阶数

常见的: $1, logn, n, nlogn, n^2$



线性查找, 下界 1, 运气好第一次就遇到

二分查找, 下界 1, 运气好正好在中间



$\Theta$ , 表示上界下界相同重合



O 用的最广泛, 因为更衡量算法好坏, 不能每次寄希望于最好的情况



线性查找实现

静态数组声明



查找数字

查找字符串

- string 字符串比较 strcmp()

数组越界, 访问内存段, segment fault

return 用处

## [Data Structures](https://cs50.harvard.edu/x/2024/notes/3/#data-structures)

电话薄, 搜索姓名返回电话号码

- string, int, 电话号码也写成 string
- 两个数组实现, 一个存 name, 一个存 numbers

设计问题 : 

- 硬编码
- 同步 name 和 number
- 必须保证两数组顺序一致, 当空间很大时



发明自己数据类型

```c
person peopel[]
  
typedef struct
{
  string name;
  string number;
}
person;
```

封装抽象, 结构体

最好在文件头声明



结构体访问属性, `.`

```c
person people[2]

people[0].name = "Carter";
peeple[0].number = "+1-617-495-1000";

people[1].name = "David";
people[1].number = "+1-949-469-2750";

string name = get_string("Name: ");
for (int i = 0; i < 2; i++){
  if (strcmp(people[i], name) == 0)
  {
    printf("Found %s\n", people[i].number);
    return 0;
  }
}
```



从文件动态读取信息, 而非硬编码



而非零散属性, 组合起来了

设置属性默认值, 相比现代语言, C 不行

"照我说的做, 而不是照我做的做"



## [Sorting](https://cs50.harvard.edu/x/2024/notes/3/#sorting)

排序本身就是需要解决的问题

输入 : unsorted

输出, sorted



## Select Sort

- 每次选择最小的, 交换

计算机没发兼顾全局, 必须有条不紊的步步执行

## [Bubble Sort](https://cs50.harvard.edu/x/2024/notes/3/#bubble-sort)

- 一步一步局部比较交换解决



哪种好?

- 选择

  - $n-1, n-2, n-3 ... , 2, 1  = n(n-1)/2$ 次比较, $O(n^2)$
  - 最好情况任然需要挨个比较, $\Omega(n^2)$

- 冒泡, 到 n-2, 防止越界, 从头开始遍历, 小优化从排好序的地方开始

  - $(n-1)*(n-1)$ , $O(n^2)$
  - 接近有序, $\Omega(n)$

  多余比较导致慢



## [Recursion](https://cs50.harvard.edu/x/2024/notes/3/#recursion) 递归

- f 同时出现在 = 两边
- 调用自己
- 同样的逻辑取操作

递归边界 base case , 递归栈

例子, 递归打印金字塔

 ```c
 void draw(int n)
 {
   if (n == 0)
   {
     return;
   }
   
   draw(n-1);
   
   for (int i = 0; i < n; i++)
   {
     printf("#");
   }
   printf("\n");
 }
 ```

递归返回值, 只能 void ? 不是



录屏看自己, 也是递归



## [Merge Sort](https://cs50.harvard.edu/x/2024/notes/3/#merge-sort) 归并排序

- 对左边排序
- 对右边排序
- 合并有序的两半
  - 两指针同时移动, 比较, 合并
- 问题 : 占用额外空间
- 边界 : 一个, 不用排
- 思想 : 分治

base case 的作用, 划分为一个个的



$O(nlogn)$

- 分治次数, $log_2n$ 
- 每次有 n 步

下界, 也是 $\Omega(nlogn)$

即, $\theta(nlogn)$



实际用现成库



time vs space



## [Summing Up](https://cs50.harvard.edu/x/2024/notes/3/#summing-up)

In this lesson, you learned about algorithmic thinking and building your own data types. Specifically, you learned…

- Algorithms.
- Big *O* notation.
- Binary search and linear search.
- Various sort algorithms, including bubble sort, selection sort, and merge sort.
- Recursion.
