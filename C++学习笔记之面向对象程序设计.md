# C++学习笔记之面向对象程序设计
Created by *Mistery*

**面向对象程序设计**的核心思想是数据抽象、继承和动态绑定。

## 1 定义基类和派生类
### 1.1 定义基类
首先定义Quote类：
```
class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) :
            bookNo(book), price(sales_price) { }
    std::string isbn() const { return bookNo; }
    virtual double net_price(std::size_t n) const
            { return n * price; }
    virtual ~Quote() = default;
private:
    std::string bookNo;
protected:
    double price = 0.0;
};
```

基类通常都应该定义一个虚析构函数，即使该函数不执行任何实际操作也是如此。

#### 成员函数与继承
C++中，有一些函数是基类希望派生类进行重新定义（覆盖）的，而有一些函数是基类希望派生类直接继承而不要改变的。前者通常将其定义为**虚函数**，以关键字**virtual**在类内部的声明语句之前标记。

#### 访问控制与继承
派生类可以继承定义在基类中的成员，但不一定有权限访问。某些成员，基类希望它的派生类可以访问，但禁止其他用户访问，可以用**受保护的（protected）**访问运算符说明。

## 2 虚函数

## 3 抽象基类

## 4 访问控制与继承

## 5 继承中的类作用域

## 6 构造函数与拷贝控制

## 7 容器与继承