Excel

flat-file database 平面文件数据库

csv 逗号分隔文本数据文件



`csv.Reader()`

```python
import csv

with open("favorites.csv", "r") as file:
  reader = csv.reader(file)
  next(reader)	# 跳过文件头
  for row in reader:
    favorite = row[1]
    print(favorite)
```

`DictReader()` 标题为 key，数值为值

```python
with open("favorites.csv", "r") as file:
  reader = csv.Dictreader(file)
  for row in reader:
    print(row["language"])
```

计算 favorite

```python
with open("favorites.csv", "r") as file:
  reader = csv.Dictreader(file)
  scratch, c, python = 0, 0, 0
  
  for row in reader:
    favorite = row["language"]
    if favorite == "scratch":
      scratch += 1
    elif favorite == "c":
      c += 1
    elif favorite == "python":
      python += 1
```

用 dict 存喜好和计数

```python
with open("favorites.csv", "r") as file:
  reader = csv.Dictreader(file)
  counts = {}
  
  for row in reader:
    favorite = row["language"]
    if favorite in counts:
      counts[favorite] += 1
    else:
      counts[favorite] = 1

for favorite in counts:
  print(f"{favorite}: {counts[favorite]}")
```

字典排序

```python
键排序：sorted(counts)
值排序：sorted(counts, key=counts.get)

逆序：sorted(counts, key=counts.get, reverse=True)
```

优化，用计数器

```python
from collections import Counter

with open("favorites.csv", "r") as file:
  reader = csv.Dictreader(file)
  counts = Counter()
  
  for row in reader:
    favorite = row["language"]
    counts[favorite] += 1

for favorite, count in counts.most_common():
  print(f"{favorite}: {counts}")
```

交互

```python
favorite = input("Favorite: ")
print(f"{favorite}: {counts[favorite]}")
```



relational database 关系数据库

SQL，结构性查询语言

CRUD

- CREATE，INSERT
- READ
- UPDATE
- DELETE，DROP



```sql
CREATE TABLE table (column type, ...);
```



sqlite3

移动端比较流行

```shell
sqlite3 favorite.db
> .mode csv
> .import favorites.csv favorites
> .quit

> .schema # 显示该数据库的架构
```



```sql
SELECT columns FROM table;
select * from favorite;
select language from favorite;
select language from favorite limit 10;
```

聚合函数

- AVG、COUNT、DISTINCT、LOWER、MAX、MIN、UPPER

```sql
select count(*) from favorite;
select count(language) from favorite;
```

限定词

- WHERE、LIKE、ORDER BY、LIMIT、GROUP BY

```sql
select count(*) from favorite where language = 'C' and problem = 'Hello, World';

select language, count(*) from favorite group by language;

select language, count(*) from favorite group by language order by count(*) DESC;
```



插入

```sql
INSERT INTO table (column, ...) VALUES (...)

insert into favorite (language, problem) VALUES('sql', 'query');
-- 留空，默认 NULL
```



删除

```sql
DELETE FROM table WHERE condition;

delete from favorites where Timestamp is NULL;
```



imdb

问题：冗余数据

解决：分表，id关联，消除关系表的冗余

- 外键关联其他表的主键字段，将两个表关联

one-to-one，一对一关系



sqlite 数据库数据类型

- BLOB
- INTEGER
- NUMERIC
- REAL
- TEXT



NOT NULL，插入更新时不能为空

UNIQUE，避免重复，比如：相同邮件注册用户



PRIMARY KEY：主键

FOREIGN KEY：外键



嵌套查询

```sql
select * from shows where id in (select show_id from rating where rating >= 6.0 limit 10);
```



join on

两张表连接，临时表中查询

```sql
select * from shows join ratings on show.id = ratings.show_id;
```

`.` 表示表的列，与 C 中结构体，oop 中对象调用方法无关



ont-t-many，一对多关系

比如：节目有多重类型



```sql
select genre from genres where show_id = (select id from shows where title = 'Catweazle');
```

链接，补充，临时表，查询

```sql
select * from shows join genres on show.id = genres.show_id where id = 63881;
```

临时表只是为了查询看到数据，并非存储在数据库中的表



many-to-many，多对多关系

需要第三个表来连接两个表

```sql
select * from shows where title = 'The Office';
select * from shows where title = 'The Office' and year = 2005;

select person_id from stars where show_id = (select id from shows where title = 'The Office' and year = 2005);

select name from people where id in (select person_id from stars where show_id = (select id from shows where title = 'The Office' and year = 2005));
```



习惯上，sql 关键字大写，但非必要的，数据库并不关心大小写



其他解决方法：三个表链接，join

```sql
select title from shows
> join stars on shows.id = stars.show_id
> join people on stars.showid = people.id
> where name = 'Steve';
```



```sql
select title from shows, stars, people
> where shows.id = stars.show_id
> and people.id = stars.person_id
> and name = 'Steve';
```



indexes

```
> .timer ON
```



问题：慢

解决：索引

```sql
create index name on table (column, ...);

create index title_index on shows (title);
```

对比后，建立索引查询速度飞快

非线性查找

B-trees

主键自动建立索引

```sql
select title from shows, stars, people
> where shows.id = stars.show_id
> and people.id = stars.person_id
> and name = 'Steve';
```



```sql
create index person_index on stars (person_id);
create index show_index on shows (show_id);
create index name_index on people (name);
```

查询速度飞快



为什么不给每个字段都建立索引？因为耗费大量内存和存储，空间换时间

权衡思想



python sql

```python
from cs50 import SQL

db = SQL("sqlite://favorites.db")

favorite = input("Favorite: ")
rows = db.execute("select count(*) as n from favorites where problem = ?", favorite)
row = rows[0]

print(row["n"])
```



race condition，条件竞争

```sql
rows = db.execute("select likes from posts where id = ?", id);
lieks = rows[0]["lieks"]
db.execute("update posts set like = ? where id = ?", likes + 1, id);
```

多任务处理大量用户请求

比如：家人发现冰箱空了需要买东西个，多人都去买了



因为并发时，不一定顺序执行

事务，绑定几条语句为原子的，要么全发生，要么全不发生



sql injection attck

接受用户输入时很危险的，输入意想不到的东西

` 闭合 sql

-- 注释

```sql
rows = db.execute(f"select * from user where username = '{username}' and password = '{password}'");
输入：admin';--
rows = db.execute(f"select * from user where username = 'admin';--' and password = {password}");
```

