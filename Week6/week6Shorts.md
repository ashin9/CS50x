语法受 C 启发，CPython 由 C 开发



## 循环

```python
for x in range(0, 100, 2):
  print(x)
```



## Array -> List

列表生成式

```python
nums = list()
nums = [x for i in range(50)]
```

列表操作

```python
nums.append(5)
nums.insert(4, 5) # 从第 4 位置插入 5
nums[len(nums):] = [5] # 追加
```



## Tuple



## 格式化

```python
print("{1}, (0)".format(a, b))
```



## dict

迭代 kv

```python
for person in people.items():
  print(person)
```



## main

```python
if __name__ == "__main__":
```



## oop

```python
class Student():
  def __init__(self, name, id):
    self.name = name
    self.id = id
  
  def changeID(self, id):
    self.id = id
  
  def print(self):
    print("{} - {}".format(self.name, self.id))
```

调用方法

```python
object.methed()
```





