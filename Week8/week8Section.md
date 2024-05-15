## HTML

DOM，文件对象模型，树型

table 标签下更多子树，及其对象组件



## CSS

语法

- 选择器，id、class、...

- 属性: 值

```css
selector
{
   property: value;
}
```



原理：遍历扫描 DOM 树，查找对应的标签



例如：选择 table 下的 td 标签

```css
td
{
  ...
}
```



例如：选择某个标签 id 为 score1 的

```css
<button id="score1">...

#score1
{
  ...
}
```



例如：选择某个特定类，在对应标签中声明 `class="类名"`

```css
<td class="team">...

.team
{
  ...
}
```



抽象 css 为单独文件，解耦合，然后关联

```html
<link rel="stylesheet" href="styles.css">
```



## Js

使页面具有交互性

```js
let team1 = 0;

document.querySelector('#add1'.onclick = function() {
    team1 = team1 + 1;
    document.querySelector('#score1').innerHTML = team1;
  	if (tem1 == 5) {
      // alert("Team 1 Won!")
      document.querySelector('#result').innerHTML = "Team 1 Won!";
    }
}
);
```

js 底层，在 DOM 树种，自上而下搜索
