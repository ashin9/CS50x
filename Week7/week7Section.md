数据库

数据库管理系统 DBMS



SQL

外键，引用了其他表的主键



设计原则

- 实体一张表
- 必须有主键



```sql
CREATE TABLE authored (
	authori_id INTEGER,
  book_id INTEGER,
  PRIMARY KEY(author_id, book_id),
  FOREIGN KEY(author_id) REFERENCES authors(id),
  FOREIGN KEY(book_id) REFERENCES authors(id)
);
```



Songs

```sql
> .read 1.sql # sqlite 读取 sql
```

