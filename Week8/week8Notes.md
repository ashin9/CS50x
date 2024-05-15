## Internet

## routers，路由

传输数据包

最快路线，动态适应

## TCP/IP 协议栈

IP 协议，唯一标识

ipv4，ipv6

port，

## DNS

## DHCP

## 80 HTTP HTTP/2 HTTP/3

- GET
- POST

443 HTTPS，数据包加密，拦截也无法解密

状态码 Status Code

- 200
- 301
- 404
- ..

浏览器调试器 Inspect



## HTML 标记语言

- 树层次结构

tags

attributes



http-server

```shell
$ http-server
```

路径与目录

记录访问日志记录



浏览器是 HTML 的解释器

- 刷新重新加载

直接用框架还是仔细学 HTML？



vscode ports 界面可看用的端口



注释 `<!-- -->`

标签

段落标签 `<p>`

无序列表 `<ul>`

列表 `<li>`

表格 `<table>`

- `tr`
- `td`

图片

```html
<img src = "...">
```

视频

```html
<veido> <source src= "..." type = "video/mp4">
```

超链接，一般访问后浏览器标记为紫色

```html
<a href="...">显示内容</a>
```

表单 ，动作

- 输入框，占位符提示，自动填充开关，自动聚焦到输入框 autofocus

```html
<form action = "..." method= "get">
  <input autocomplete = "off" autofocus = name = "q" placeholder = "Query" type = "search">
  <button>
    Search
  </button>
</form>
```

- re 正则，匹配输入

```html
<form action = "..." method= "get">
  <input autocomplete = "off" autofocus name = "q" pattern = ".+@.+.edu" placeholder = "Query" type = "search">
  <button>
    Search
  </button>
</form>
```



问题：不安全，本地修改前端页面或抓包，绕过前端正则



## CSS

属性

```html
<p style="font-size: large; text-align: center;">
  
</p>

<div> 页面划块分区
  
</div>
```

级联效果

```html
<body style="">   会影响所有子标签
  <div style="">
    
  </div>
  <div>
    
  </div>
</body>
```

版权页脚

```html
<footer>
  Copyright &#169; Ashing
</footer>
```



```html
<header></header>
<main></main>
<footer></footer>
```



样式标签

```html
<style>
  body
  {
    text-align: center;
  }
  
  footer
  {
    font-size: small;
  }
</style>
```



css 类，抽象出来，解耦合，可以直接调用

```css
.centered
{
  color: red;
  text-align: center;
}

.large
{
  font-size: large;
}


<header class="centered"></header>
```



css 独立，单独文件写 css，从 html 中引入

- rel="stylesheet" 表示当前链接是一个样式表链接，它告诉浏览器该链接是一个外部样式表文件，浏览器会根据这个链接加载并应用该样式表到当前文档中。这使得我们可以在HTML文档中引入外部CSS样式表，从而对文档进行样式控制，实现页面的美化和布局。

```html
<head>
  <link href="xxx.css" rel="stylesheet">
</head>
```



鼠标指到上面，下划线强调

```css
a
{
  color: red
  text-decoration: none;
}

a:hover
{
  text-decoration: underline;
}
```



选择器

- type selector
- class selector
- ID selector
- attribute selector
- ...



id 选择器

```html
#id
{
	color: red;
}

<a id="id"></a>
```



## Bootstrap 框架

写了很多 css 样式类，查手册来使用

- 在标签用 `class` 选择需要的样式标记标签



## JavaScript

弹窗

直接嵌入

```js
function greet()
{
  alert('hello, ' + document.querySelector('#name').value);
}

<form onsubmit="greet(); return false;">
  <input autocomplete="off" autofocus id="name" placeholder="Name" type="text">
</form>
```

标签标记分离，匿名函数

```html
<form>
  
</form>

<script>
  document.querySelector('form').addEventListener('submit', function(e))
  {
    alert('hello, ' + document.querySelector('#name').value);
  	e.preventDefault();
  }
</script>
```



DOM，文档对象模型，内存中以树来组织

若所有页面对象已经加载到内存，再执行下面的代码：

- DOMContenLoaded，标记是否已经加载

```html
<script>
  document.addEventListner('DOMContentLoaded', function()){
      document.querySelector('form').addEventListener('submit', function(e))
  		{
    		alert('hello, ' + document.querySelector('#name').value);
  			e.preventDefault();
  		}
  }
</script>
```



点击按钮，触发更换页面背景事件

```html
<button id="red">R</buttion>

<script>
	let body = document.querySelector('body');
  document.querySelector('#red').addEventListener('click', function(){
     body.style.backgroundColor = 'red'; 
  });
</script>
```



眨眼标签，丑陋的标签，现在很少用

```js
blink()
{

}

window.setInterval(blink(), 500); 每 500ms 眨眼一次
```



autocomplete

实时生成，动态创建页面内容

- 若监听到键盘事件，则触发匿名函数，执行逻辑生成页面

```js
let input = document.querySelector('input');
input.addEventListener('keyup', function(event){
		let html = '';
    if (input.value) {
        for (word of WORDS) {
            if (word.startsWith(input.value)) {
                html += `<li>${word}</li>`;
            }
        }
    }
    document.querySelector('ul').innerHTML = html;
});
```



获取定位（若有访问权限）

```js
navigator.geolocation.getCurrentPosition(function(position) {
  document.write(position.coords.latitude + ", " + position.coords.longitude);
});
```



## [Summing Up](https://cs50.harvard.edu/x/2024/notes/8/#summing-up)

In this lesson, you learned how to create your own HTML files, style them, leverage third-party frameworks, and utilize JavaScript. Specifically, we discussed…

- TCP/IP
- DNS
- HTML
- Regular expressions.
- CSS
- Frameworks
- JavaScript
