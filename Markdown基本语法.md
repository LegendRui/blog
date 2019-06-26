# Markdown基本语法
参考：
[Markdown基本语法 - 高鸿祥](https://www.jianshu.com/p/191d1e21f7ed)

## 一、标题

`# 一级标题`
# 一级标题

`# 二级标题`
## 二级标题

`# 三级标题`
### 三级标题

`# 四级标题`
#### 四级标题

`# 五级标题`
##### 五级标题

`# 六级标题`
###### 六级标题

## 二、字体

* ### 加粗
要加粗的文字两端用2个* 包起来。  
示例：  
`**笔记**`  
**笔记**

* ### 斜体
要倾斜的文字；两端用1个* 包起来。  
示例：  
`*笔记*`  
*笔记*

* ### 斜体加粗
要同时倾斜和加粗的文字两端用3个* 包起来。  
示例：  
`***笔记***`  
***笔记***

* ### 删除线
要加删除线的文字两端用2个~~ 包起来。  
示例：  
`~~笔记~~`  
~~笔记~~

## 三、引用

在引用的文字前加>即可。
示例：
```
>鲁迅说的
>>鲁迅说的
>>>鲁迅说的
```
>鲁迅说的
>>鲁迅说的
>>>鲁迅说的

## 四、分割线  

三个或更多个- 或者* 都可以。  
示例：  
`---`  
---  
`***`  
***

## 五、图片

语法：
```
![图片ALT](图片地址 "图片title")
```
实例：
```
![quadrotor](https://github.com/LegendRui/blog/blob/master/pics/0.png "quadrotor")
```
![quadrotor](https://github.com/LegendRui/blog/blob/master/pics/0.png "quadrotor")

## 六、超链接
语法：  
`[超链接名](超链接地址 "超链接title")`  
示例：   
```
[GitHub](https://github.com/)
[Google](http://google.com/)
```

[GitHub](https://github.com/)  
[Google](http://google.com/)

## 七、列表
 * ### 无序列表
语法：  
无序列表用- + * 任何一个都可以

示例：  
```
- 北京
+ 上海
* 广州
```   
效果：   
- 北京
+ 上海
* 广州

## 八、数学公式
Markdown是不只是latex的，但是可以在[CodeCogs Equation Editor](http://latex.codecogs.com/)生成然后引用。语法：
```
![](http://latex.codecogs.com/gif.latex?\\frac{1}{1+sin(x)})
```  
效果：
![](http://latex.codecogs.com/gif.latex?f=ma)
**注：**转义字符为2个\ 。