Internet

Ipv4 ipv6

DHCP

DNS

Access Points 接入点



IP（Internet Protocol）

Router

路由表

类比 GPS



TCP

常用端口号



HTTP

其他应用层协议：DDS、RDP、XMPP

GET、POST

响应码

- 301，永久迁移，自动重定向
- 302，找到，临时

- 401，未授权
- 403，拒绝
- 404，未找到
- 500，服务器错误



HTML

标记语言，而非编程语言，没有变量逻辑等等

```html
// 文件头
<!DOCTYPE html>
// 注释
<!-- -->

// 段落
<p>

// x 级别 header
<h1>
<h2>
...
<h6>
  
  
// 列表
<ul> 无序
<ol> 有序
<li> 有序或无序

// 表格
<table>
<tr>
<td>

// 表单
<form>
<div> // division 分割区
<input name="" type="">

// 超链接
<a href="...">
// 图片
<img src="...">
```



CSS

样式语言，不是编程语言

```css
// 边界
border: style color width
// 背景颜色
backgroud-color: [keyword | #<6-digit hex]
// 颜色
color: [keyword | #<6-digit hex]

// 文本格式
// 字体大小, 绝对大小, 相对大小
font-size: [absolute size | relative size]
// 字体, 用安全的字体
font-family: [font name | generic name]
// 字体布局位置
text-align: [left | right | center | justify]
```

选择器：标签选择器、ID 选择器、class 选择器

```css
tagname{
  
}

#idname{
  
}
.classname{
  
}
```

抽象拆分解耦，单独文件，引用



JS

主要实现页面交互逻辑

变量

```js
var x = 22;
```

数组

```js
var nums = [1, True, mix, a, 5];
```

条件，和 C 几乎一样

```js
if
else if
else

switch

?:
```

循环

```js
while
do-while
for
  
for (var key of object)
{
  // use key in here
}
```

函数

```js
function funcname()

// 匿名函数
function (){}
```

对象

- 结构 vs 对象

```js
// 调用对象方法
object.function();
```



字符串

```js
// 拼接
arr[2]+ 'string link'
```



数组对象操作

```js
arr.size()
arr.pop()
arr.push(x)
arr.shift()
```



函数式编程，自动迭代所有元素

- map
- 匿名函数

```js
var nums = [1, 2, 3, 4, 5];

nums = nums.map(function (num){
  return num * 2;
})
```



Events，事件

```html
<buttion onclick=""></buttion>
<buttion onclick="alertName(event)"></buttion>

fucntion alertName(event)
{
	var trigger = event.srcElement;
	alert('You clicked on ' + trigger.innerHTML);
}
```



DOM

文档对象，将单个网页内容组织到文档对象中，然后用 JS 操作文档对象

浏览器控制台查看 DOM

```js
console.dir(document)
```

DOM 属性

```js
innerHTML  // 将 HTML 保存在一组标签内
nodeName   // HTML 元素或元素属性
id				 // HTML 元素
parentNode // 上层 DOM 树节点
childNodes // 下层 DOM 树节点
attributes // HTML 元素属性组
style			 // 元素样式
```

DOM 方法

```js
getElementById(id) 				// 通过 ID 取 Element
getElementByTagName(tag)  // 通过 tag 取 Element
appendChild(node)					// 增加节点
removeChild(node)					// 删除节点
```



jQuery

封装 DOM 操作，最流行的 Js 库

简化 Js 编写复杂度

更好执行 AJAX 查询

```js
// JS 原生操作 DOM
document.getElementById('colorDiv').style.backgroudnColor = 'green'
// jQuery 操作
$('#colorDiv').css('background-col')
```

