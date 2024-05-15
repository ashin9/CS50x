## [Static to Dynamic](https://cs50.harvard.edu/x/2024/notes/9/#static-to-dynamic)

http server

静态网页，固定写死 html

动态网站，动态生成 html

URL

folder，目录

path，路径

请求，本质是一条信息

```http
?key=value&key=value
```



## [Flask](https://cs50.harvard.edu/x/2024/notes/9/#flask)

Py 轻量 Web 框架

```shell
$ flask run
```

经典目录结构

```python
templates/
static/
app.py
requirements.txt
```



Index.html 兼容设备视口大小

```html
<meta name="viewport" content="initial-scala=1, width=device-width">
```



```python
from flask import Flask, render_template, request

app = Flask(__name__)
# __name__ 特殊变量, 指当前文件名

@app.route("/")
def index():
  return "hello, world"
```

问题：返回字符串，浏览器查看源码只是文本，并不是 html 文件

解决：渲染模版

```python
@app.route("/")
def index():
  return render_template("index.html")
```



模版变量，双括号，Jinja 模版

```html
<body>
 	hello, {{ name }}
</body>
```



接受传递参数

```python
<body>
 	hello, {{ placeholder }}
</body>

@app.route("/")
def index():
  name = request.args["name"]
  return render_template("index.html", placeholder=name)
```

静态网页和动态网站的区别



异常处理，防御性编码

```python
@app.route("/")
def index():
  if "name" in request.args:
    name = request.args["name"]
  else:
    name = "world"
  return render_template("index.html", placeholder=name)
```

优化

- 用 get api 精简逻辑

- 一致站位名字与参数名

```python
<body>
 	hello, {{ name }}
</body>

@app.route("/")
def index():
  name = request.args.get("name", "world")  # 默认值 world
  return render_template("index.html", name=name)
```



表单 `greet.html`

```html
<form action="/greet" method="get">
  <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
  <button type="submit">
    Greet
  </button>
</form>
```



```python
@app.route("/greet")
def greet():
  name = request.args.get("name", "world")
  return render_template("greet.html", name=name)
```



任何重复的东西都是糟糕的设计



## [Layout](https://cs50.harvard.edu/x/2024/notes/9/#layout)

Jinjia 标签，代码块占用符，用于引入大量代码

```html
{% block body %}{% endblock %}
```



`template/layout.html`

```html
<!DOCTYPE html>

<html lang="en">
  <head>
    <meta name="viewport" content="initial-scale=1, width=device-width">
    <title>hello</title>
  </head>
  <body>
    {% block body %}{% endblock %}
  </body>
</html>
```



`index.html`

```html
{% extends "layout.html" %}

{% block body %}

	<form action="/greet" method="get">
  	<input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
    <button type="submit">
      Greet
    </button>
	</form>
	
{% endblock %}
```



`greet.html`

```html
{% extends "layout.html" %}

{% block body %}

	hello, {{ name }}

{% endblock %}
```



实现解耦和重用，独立管理不同类型和功能的模版



## GET 和 POST

- `form`
- 不会再 URL 中泄露信息，且传输数据量大

```python
# 默认 GET
@app.route("/greet", methods=["POST"])
def greet():
  name = request.form.get("name", "world")
  return render_template("greet.html", name=name)
```

同时支持 GET 和 POST

```python
@app.route("/greet", methods=["GET", "POST"])
def greet():
  if request.method == "POST":
    name = request.form.get("name", "world")
  	return render_template("greet.html", name=name)
  return render_template("index.html")
```



```html
{% extends "layout.html" %}

{% block body %}

	<form action="/" method="post">
  	<input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
    <button type="submit">
      Greet
    </button>
	</form>
	
{% endblock %}
```



Jinja 模版，可实现简单条件逻辑，甚至循环流程等

```html
{% extends "layout.html" %}

{% block body %}

	hello, {% if name %}{{ name }}{% else %}world{% endif %}

{% endblock %}
```



## [Frosh IMs](https://cs50.harvard.edu/x/2024/notes/9/#frosh-ims)

```html
{% extends "layout.html" %}

{% block body %}

	<h1>Register</h1>
	<form action="/register" method="post">
      <input autocomplete="off" autofocus name="name" placeholder="Name" required type="text">
      <select name="sport">
          <option disabled selected value="">Sport</option>
          <option>Basketball</option>
          <option>Soccer</option>
          <option>Ultimate Frisbee</option
      </select>
  </form>
	
{% endblock %}
```

`required` 标记不能为空，但是前端可绕过



```python
@app.route(/register， methods=["POST"])
def register():
  if not request.form.get("name") or not request.form.get('sport'):
    return render_template()"failure.html")  # 后端验证输入不为空
  return render_template("success.html")
```



`success.html`

```html
{% extends "layout.html" %}

{% block body %}

	You are registered! (Not really.)

{% endblock %}
```



`failure.html`

```html
{% extends "layout.html" %}

{% block body %}

	You are not registered!

{% endblock %}
```



前端修改选择的运动，如何控制？后端用白名单

```python
SPORTS = ["Basketball", "Soccer", "Ultimate Frisbee"]

@app.route("/")
def index():
  return render_template("index.html", sports=SPORTS)
```



```html
{% extends "layout.html" %}

{% block body %}

	<h1>Register</h1>
	<form action="/register" method="post">
      <input autocomplete="off" autofocus name="name" placeholder="Name" required type="text">
      <select name="sport">
          <option disabled selected value="">Sport</option>
					{% for sport in sports %}
        			<option value="{{sport}}"> {{ sport }}</option>
          {% endfor %}
      </select>
  </form>
	
{% endblock %}
```

后端修改 sports 列表，前端就可同步更新



永远不要相信用户的输入！



选择的运动互斥，选择点

```html
{% extends "layout.html" %}

{% block body %}

	<h1>Register</h1>
	<form action="/register" method="post">
      <input autocomplete="off" autofocus name="name" placeholder="Name" required type="text">
      <select name="sport">
          <option disabled selected value="">Sport</option>
					{% for sport in sports %}
        			<input name="sport" type="radio" value="{{ sport }}"> {{ sport }}
          {% endfor %}
      </select>
  </form>
	
{% endblock %}
```

复选框

```html
<input name="sport" type="checkbox" value="{{ sport }}"> {{ sport }}
```



```python
@app.route(/register， methods=["POST"])
def register():
  if not request.form.get("name"):
    return render_template()"failure.html")  # 后端验证输入不为空
  for sport in requests.form.getlist("sport"):
    if sport not in SPORTS:
      return render_template("failure.html")
  return render_template("success.html")
```



错误页面 `error.html`

```html
{% extends "layout.html" %}

{% block body %}

	<h1>Error</h1>
	<p>{{ message }}</p>
	<img alt="error-img" src="/static/error-img.jpg">
	
{% endblock %}
```



将人名和对应运动存入字典中

```python
from flask import Flask, redirect, render_template, request

REGISTRANTS = {}

@app.route(/register， methods=["POST"])
def register():
  # Validate name
  if not request.form.get("name"):
    return render_template("error.html", message="Missing name")
  
  # Validate sport
  sport = requests.form.get("sport")
  if not sport:
    return render_template("error.html", message="Missing sport")
  if sport not in SPORTS:
    return render_template("error.html", message="Invalid sport")
  
  # Remeber registrant
  REGISTRANT[name] = sport
	
  # Confirm registrantion, 重定向
	return redirect("/registrant")

@app.route(/registrant)
def registrant():
  return render_template("registrants.html", registrant=REGISTRANTS)
```



`registrant.html`

```html
{% extends "layout.html" %}

{% block body %}

	<h1>Registrants</h1>
  <table>
    <thead>
      <tr>
        <th>Name</th>
        <th>Sport</th>
      </tr>
    </thead>
    <tbody>
      {% for name in registrants %}
        <tr>
          <td>{{ name }}</td>
          <td>{{ registrants[name] }}</td>
        </tr>
      {% endfor %}
    </tbody>
    
{% endblock %}
```



问题：断点内存中数据丢失

解决：数据持久化到数据库



## SQLite for Py



```py
from cs50 import SQL

db = SQL("sqlite:///froshims.db")


..
def register():
  ...
  db.execute("INSERT INTO registrants (name, sport)" VALUES(?, ?), name, sport)
  ...

...
def registrants():
  registrants = db.execute("SELECT * FROM registrants")
  return render_template("registrants.html", registrants=registrants)
```



取消注册

```html
{% extends "layout.html" %}

{% block body %}

	<h1>Registrants</h1>
  <table>
    <thead>
      <tr>
        <th>Name</th>
        <th>Sport</th>
      </tr>
    </thead>
    <tbody>
      {% for name in registrants %}
        <tr>
          <td>{{ registrant.name }}</td>
          <td>{{ registrant.sport }}</td>
          <td>
            <form action="/deregister" method="post">
              <input name="id" type="hidden" value="{{ registrant.id }}">
              <button type="submit">Deregister</button>
            </form>
          </td>
        </tr>
      {% endfor %}
    </tbody>
    
{% endblock %}
```



```py
@app.route("deregister", methods=["POST"])
def deregister():
  
  # Forget registrant
  if = request.form.get("id")
  if id:
    db.execute("DELETE FROM registrants WHERE id = ?", id)
  return redirect("/registrants")
```



MVC 模型

数据库 M

前端 V

后端 Flask C



## Cookie Session

Set-Cookie 头，首次访问

session，会话，记录状态

到期时间



Cookie 头，再次访问



登录

```py
from flask import Flask, redirect, render_template, request, session
from flask_session import Session

app = Flask(__name__)

app.config["SESSION_PERMANET"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

REGISTRANTS = {}

@app.route("/")
def index():
  return render_template("idnex.html", name=session.get("name"))

@app.route("/login", methods=["GET", "POST"])
def login():
  if request.method == "POST":
    session["name"] == request.form.get("name")
    return redirect("/")
  return render_template("login.html")

@app.route("/logout", methods=["GET", "POST"])
def logout():
  session.clear()
  return redirect("/")
```



`index.html`

```html
{% extends "layout.html" %}

{% block body %}

	{% if name %}
			
			You are logged in as {{ name }}.

			<a href="/logout">Log out</a>.

	{% else %}
	
			You are not logged in.
			
			<a href="/login">Log in</a>.
			
  {% endif %}
    
{% endblock %}
```



`login.html`

```html
{% extends "layout.html" %}

{% block body %}
    
		<form action="/login" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <button type="submit">Log In</button>
    </form>
{% endblock %}
```



## Shopping Cart

购物系统

```python
db.execute("SELECT * ...") # 返回字典列表
```



```python
from cs50 import SQL
from flask import Flask, redirect, render_template, request, session
from flask_session import Session

# Configure app
app = Flask(__name__)

# Connect to database
db = SQL("sqlite:///store.db")

# Configure session
app.config["SESSION_PERMANET"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

@app.route("/")
def index():
  books = db.execute("SELECT * FROM books")
  return render_template("books.html", books=books)

@app.route("/cart", methods=["GET", "POST"])
def cart():
  
  # Ensure cart exists
  if "cart" not in session:
    session["cart"] = []
  
  # POST
  if request.method == "POST":
    book_id = request.form.get("id")
    if book_id:
      session["cart"].append(book_id)
    return redirect("/cart")
  
  # GET
  books = db.execute("SELECT * FROM books WHERE id IN (?)", session["cart"])
  return render_template("cart.html", books=books)
```



`books.html`

```html
{% extends "layout.html" %}

{% block body %}
    
    <h1>Books</h1>
    {% for book in books %}

        <h2>{{ book['title'] }}</h2>
        <form action="/cart" method="post">
            <input name="id" type="hidden" value="{{ book['id'] }}">
            <button type="submit">Add to Cart</button>
        </form>

    {% endfor %}
{% endblock %}
```



`cart.html`

```html
{% extends "layout.html" %}

{% block body %}
    
    <h1>Cart</h1>
    <ol>
      {% for book in books %}
          <li>{{ book['title'] }}</li>
      {% endfor%}
    </ol>
{% endblock %}
```





## shows

```py
@app.route("/search")
def search():
  shows = db.execute("SELECT * FROM shows WHERE title = ?", request.args.get("q"))
  return render_template("shows.html", shows=shows)
```



## AJAX

问题：每次都请求，重新加载页面

解决：AJAX

AJAX，异步 JS

- 以前指异步 JS 和 XML
- 现在指  JS 从服务器获取更多数据，而 URL 不变，浏览器屏幕也不会刷新闪烁



表单每输入一个字符就自动发送一次请求，接受新数据，更新页面内容

```js
<script>
  let input = document.querySelector('input');
	input.addEventListener('input', async fucntion(){
      let response = await fetch('/search?q=' + input.value);
      let shows = await response.text();
      document.querySelector('ur').innerHTML = shows;
  });
</script>
```



## APIs

JSON，目前常用数据传输方式

```py
from flask import jsonify
....
shows = db.execute(...)
return jsonify(shows)
```



## [Summing Up](https://cs50.harvard.edu/x/2024/notes/9/#summing-up)

In this lesson, you learned how to utilize Python, SQL, and Flask to create web applications. Specifically, we discussed…

- GET
- POST
- Flask
- Session
- APIs
- AJAX
- JSON
