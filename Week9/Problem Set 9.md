## Birthdays

实现生日统计 Web 程序

### 要求

`/` 路由，GET，展示数据库所有生日信息

- `app.py` 查询所有
- `index.html` 添加渲染展示逻辑

`/` 路由，POST，添加新生日数据到数据库，并重新渲染前端页面

- `index.html` 添加表单
- `app.py` 插入新数据逻辑

可选，删改逻辑



## Finance

实现买卖股票网站程序

### 背景

通过 API 获取 JSON 格式的股票价格

```
https://api.iex.cloud/v1/data/core/quote/nflx?token=API_KEY
```

### 运行

- 查看数据库
  - `sqlite3`
  - `phpLiteAdmin`

### 理解

#### `app.py`

配置

- 禁用响应缓存，避免修改了代码，而浏览器不及时生效
- 配置 jinja 的 filter，格式化 US dollars
- 配置 sessions，存储本地文件系统

路由

- `login` 和 `logout` 完全实现
  - 查询数据库
  - `check_password_hash` 比较用户密码的哈希值
  - 会话中存储用户 `user_id` 来记住用户的登录
  - 登陆成功重定向
  - 清除会话，以注销用户

- 其他，等待实现，目前只是返回报错信息

装饰器，检查是否登录

- `helper.py` 中实现，确保访问路由时是登录状态，否则重定向到登录页面

#### `helpers.py`

- `apology` 返回渲染错误页面
- `escape` 替换特殊字符，定义在 `apology` 内，因此只有 `apology` 可调用
- `login_required`
- `lookup`，查询股票信息：浮点数价格，字符型符号

#### `requirements.txt`

依赖库

#### `static/`

静态资源和 css

#### `templates/`

前端页面模版

`apology.html`，code 和 bottom 传给前端模版

`layout.html` ，jinja 控制显示逻辑，嵌入不同导航栏

### 要求

#### register

实现注册

- 创建类似 `login.html` 的模版 `register.html`

- 用户输入 text 类型 username，若空或 username 已存在则返回 apology 页面
- 用户输入 text 类型 password，再次输入相同 password，名称为 confirmation，若空或两次不匹配则返回 apology 页面
- POST 提交表单，到 `/register` 路由
- 插入信息到 `users` 表，存储 password 的 hash 值

#### quote

实现用户查询股票当前价格

- 用户输入：text 类型的股票名 symbol
- POST 提交表单，到 `/quote` 路由
- 创建俩模版 `quote.html` `quoted.html`，GET 访问呈现表单，POST 访问呈现响应，嵌入多个查找值

#### buy

实现用户买入股票

- 用户输入：text 类型的股票名 symbol，若空或股票不存在则返回 apology 页面
- 用户输入：股票数 shares，若非正整数则返回 apology 页面
- POST 提交表单，到 `/buy` 路由
- 以上完成后，重定向到用户 home page

可能用到

- lookup 查询当前股票价格
- 查询用户当前有多少余额，若买不起，则返回 apology 页面
- 向数据库添加多个新表，跟踪购买情况，以便知道谁在什么时间，以多少价格购买了多少什么股票
  - SQLite 类型
  - UNIQUE
  - non-UNIQUE
- 不考虑条件竞争（或使用事务）

```sql
CREATE TABLE holding_stock (
	id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	userid INTEGER NOT NULL,
	symbol TEXT UNIQUE NOT NULL,
	shares NUMERIC NOT NULL DEFAULT 0.00
);

CREATE TABLE transactions (
	id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	userid INTEGER NOT NULL,
	time DATETIME NOT NULL,
	symbol TEXT NOT NULL,
	price NUMERIC NOT NULL,
	shares NUMERIC NOT NULL
);
```

#### index

完成首页，显示 HTML 表格

- 汇总当前用户拥有的股票、股票数、每只股票当前价格、每只股票的总价值
- 汇总用户的现金余额及总资产（股票总价值+余额）

可能用到

- 多表查询，条件 WHERE，分组 GROUP BY，过滤 HAVING，求和 SUM，等
- lookup 查询每只股票信息

#### sell

实现用户卖出股票

- 用户输入：股票的 symbol，若用户不选择股票或用户不拥有该股票的股份，则返回 apology 页面
- 用户输入：股份数量 shares，若输入非正整数或大于用户拥有的股份，则返回 apology 页面
- POST 提交表单，到 `/sell` 路由
- 以上完成后，重定向到 home page

不考虑条件竞争

#### history

实现所有交易历史信息页面

- 每行，买入或卖出，股票 symbol，股票价格，股份数量，交易日期时间
- 可能需要更改 buy 功能创建的表或补充额外表，尽量减少冗余

#### personal touch

- 用户修改密码
- 用户添加额外零钱
- 用户可通过 index 买卖股票，无需手动输入股票代码
- 其他

### 提示

- usd filter 格式化价格，Jinja 模版可用 `{{ value | usd }}`

- CS50.SQL，execute(SQL) 返回值
  - select，返回 dict 列表
  - insert，若包含自动递增 PRIMARY KEY，返回新插入行的主键值
  - delete 或 update，返回删除或更新的行数

- CS50.SQL，execute(SQL) 回记录到终端窗口，以便检查
- 占位符绑定参数，不可 SQL 拼接，可能导致 SQL 注入风险
- 若已经熟悉 SQL，可以SQLAlchemy Core 或 Flask-SQLAlchemy（即 SQLAlchemy ORM）而不是 cs50.SQL
- 欢迎添加 css 样式静态文件
