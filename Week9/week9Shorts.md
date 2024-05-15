C 实现很难、很麻烦、代码量很大

Flask

静态页面，问题：静态



动态时间

```py
from flask import Flask
from datatime import datatime
from pytz import timezone

app = Flask(__name__)

@app.route("/")
def time():
  now = datatime.now(timezone('America/New_York'))
  return "The current data and time is {}".format(now)
```



装饰器，关联修改函数的行为



`url_for()`， 提高了代码的可维护性和灵活性

- 动态生成视图 url，而不是硬编码 url，当需要修改 url 结构时，无需修改所有 url，只需修改视图函数的路由规则
- 传递参数，用于生成带有动态路由参数的 URL
- 生成静态文件（如 CSS、JavaScript 文件）的 URL。这样可以确保当你更改静态文件的存储位置时，不需要修改所有页面中对应的静态文件 URL

`redirect()`

`session()`

`render_template()`

