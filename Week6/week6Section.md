## Strings

```python
text.strip()	# 去除字符前后空格
text.lower()
text.upper()
text.capitalize() # 仅第一个字符大写
```

字符串切割为 List

```python
str.split() # 默认空格
```

```python
text = "In the great green room"

for word in text.split():
  if "g" in word:
    print(word)
```

切片

```python
text.split()[2:]
```



## dict



## Lib and modules



## FILE IO

```python
with open(filename) as file:
  text = file.read()
  for row in text:
```



```python
import csv

books = []

with open("books.csv", "r") as file:
  reader = csv.DictReader(file)
  for row in reader:
    books.append(row)
```

