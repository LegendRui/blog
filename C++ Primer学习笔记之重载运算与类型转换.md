<center>
# C++ Primer学习笔记之重载运算与类型转换
</center>

关于重载运算符值得注意的几点：

+ 运算对象求值顺序的规则无法应用到重载的运算符上
+ 重载的&&和||运算符无法保留短路求值属性

通常情况下，**不应该重载逗号、取址、逻辑与和逻辑或运算符**。

## 1. 输入、输出运算符
### 1.1 重载输入运算符<<
通常情况下，输入运算符的第一个形参是一个非常量ostream对象的引用（因为向流写入内容会改变其状态，并且我们没法直接复制ostream对象），第二个形参是我们要打印的类类型的引用。

输入输出运算符一般被声明为友元。
```
ostream &operator(ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
        << item.revenue << " " << item.avg_price();

    return os;
}
```

# 1.2 重载输入运算符
通常情况下，输入运算符的第一个形参是运算符将要读取的流的引用，第二个形参是将要读入的对象的引用。

在执行输入运算符时可能发生下列错误：

+ 当流含有错误类型的数据时读取操作可能失败 
+ 当读取操作到达文件末尾或者遇到输入流的其他错误时也会失败

因此，输入运算符必须处理可能失败的情况。
```
istream &operator(istream &is, Sales_data &item)
{
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is)     // 检查是否输入成功
    
        item.revenue = item.units_sold * price;
    else
        item = Sales_data();     // 输入失败，对象被赋予默认状态
    
    return is;
}
```
## 2. 算数、关系运算符
通常情况下，算数和关系运算符应被定义为非成员函数以允许对左侧或右侧的运算对象进行转换。  
如果类同时定义了算术运算符和相关的复合赋值运算符，则通常情况下应该使用复合赋值来实现算术运算符，因为这样可以提高效率。

### 2.1 相等运算符
如果某个类在逻辑上有相等性的含义，则该类应该定义operator==，这样做可以使得用户更容易使用标准库算法来处理这个类。
```
bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn() &&
            lhs.units_sold == rhs.units_sold &&
            lhs.revenue == rhs.revenue;
}

bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
{
    return !(lhs == rhs);
}
```

### 2.2 关系运算符
通常情况下关系运算符应该  
1. 定义顺序关系，令其与关联容器中对关键字的要求一致；并且  
2. 如果类同时也含有==运算符的话，则定义一种关系令其与==保持一致。特别是，如果两个对象是！=的，那么一个对象应该<另外一个。  

## 3. 赋值运算符
在拷贝控制一章已经提到过拷贝赋值和移动赋值运算符。此外，类还可以定义其他赋值运算符以使用别的类型作为右值运算对象。例如：
```
class StrVec {
public:
    StrVec &operator=(std::initializer_list<std::string>);
};

StrVec &StrVec::operator=(std::initializer_list<std::string>)
{
    auto data = alloc_n_copy(il.begin(), il.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

vector<string> v;
v = {"a", "an", "the"};
```

不管形参的类型是什么，赋值运算符都必须定义为成员函数。

**复合赋值运算符**不非得是类的成员，但我们还是倾向如此。
```
Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}
```

## 4. 下标运算符
表示容器的类通常可以通过元素在容器中的位置访问元素，这些类一般会定义下标运算符operator[]。

下标运算符必须是成员函数。为了兼容内置原始定义，下标运算符通常以所访问元素的引用作为返回值，使得下标可以出现在赋值运算符的任一端。

定义下标运算符时通常定义两个版本：一个返回**普通引用**，另一个返回**常量引用**。例如：
```
class StrVec{
public:
    sdt::string& operator[](std::size_t n)
            {   return elements[n];     }
    const std::string& operator[]{std::string size_t} const
            {   return elements[n];     }
private:
    std::string *elements;      // 指向数组首元素的指针
};

const StrVec cvec = svec;
if (svec.size() && svec[0].empty()) 
{
    svec[0] = "zero";   // 正确：下标运算符返回string的引用
    cvec[0] = "Zip";    // 错误：对cvec取下标返回的是常量引用
}
```




## 5. 递增、递减运算符

## 6. 成员访问运算符

## 7. 函数调用运算符

## 8. 重载、类型转换与运算符