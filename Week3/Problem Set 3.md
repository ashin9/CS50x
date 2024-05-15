## Sort

猜解排序算法

### 已排好序的, 下界

快到慢 : 冒泡, 归并, 选择 

### 逆序的, 上界

快到慢 : 归并, 冒泡 = 选择

### 随机的, 上界

快到慢 : 归并, 冒泡, 选择



### sorted

```
$ time ./sort1 sorted5000.txt		归并
real    0m0.075s
user    0m0.006s
sys     0m0.029s

$ time ./sort2 sorted5000.txt		冒泡
real    0m0.048s
user    0m0.000s
sys     0m0.033s

time ./sort3 sorted5000.txt			选择
real    0m0.085s
user    0m0.026s
sys     0m0.030s

$ time ./sort1 sorted50000.txt	冒泡
real    0m0.514s
user    0m0.020s
sys     0m0.264s

$ time ./sort2 sorted50000.txt	归并
real    0m0.593s
user    0m0.036s
sys     0m0.264s

$ time ./sort3 sorted50000.txt	选择
real    0m2.328s
user    0m1.886s
sys     0m0.255s
```

### reversed

```
$ time ./sort3 reversed5000.txt	 选择
real    0m0.107s
user    0m0.036s
sys     0m0.039s

$ time ./sort3 reversed5000.txt  冒泡
real    0m0.044s
user    0m0.000s
sys     0m0.032s

$ time ./sort3 reversed5000.txt  归并
real    0m0.048s
user    0m0.020s
sys     0m0.027s


$ time ./sort1 reversed50000.txt	选择
real    0m5.124s
user    0m4.483s
sys     0m0.286s

$ time ./sort2 reversed50000.txt	归并
real    0m0.550s
user    0m0.032s
sys     0m0.268s

$ time ./sort3 reversed50000.txt	冒泡
real    0m2.494s
user    0m2.023s
sys     0m0.276s
```



### random

```
sort1 random            选择
real    0m0.127s
user    0m0.036s
sys     0m0.039s

sort2 random						冒泡
real    0m0.064s
user    0m0.009s
sys     0m0.023s

sort3 random						归并
real    0m0.048s
user    0m0.020s
sys     0m0.028s

$ time ./sort1 random50000.txt	选择
real    0m5.680s
user    0m5.150s
sys     0m0.293s

$ time ./sort2 random50000.txt	归并
real    0m0.531s
user    0m0.044s
sys     0m0.250s

$ time ./sort3 random50000.txt	冒泡
real    0m2.547s
user    0m1.972s
sys     0m0.285s
```



## Plurality

填程序

遍历判断名字, 操作结构体属性

遍历记录最大值



## Runoff
