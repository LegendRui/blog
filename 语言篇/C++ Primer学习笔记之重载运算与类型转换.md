# C++ Primer学习笔记之重载运算与类型转换
Created by *mistery*

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

### 1.2 重载输入运算符
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
C++并不要求递增和递减运算符必须是类的成员。但因它们能改变对象的状态，因此建议设定为成员函数。

定义递增和递减运算符的类应该同时定义前置版本和后置版本。
#### 前置递增/递减运算符
以StrBlobPtr类为例：
```
class StrBlobPtr
{
public:
    StrBlobPtr operator++();    // 前置版本
    StrBlobPtr operator--();
};

StrBlobPtr& StrBlobPtr::operator++()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator--()
{
    --curr;
    check(curr, "decrement past begin StrBlobPtr");
    return *this;
}
```

#### 后置递增/递减运算符
为了与前置版本区别，后置版本接收一个额外的int型的形参。
```
class StrBlobPtr
{
public:
    StrBlobPtr operator++(int);
    StrBlobPtr operator--(int);
};

StrBlobPtr StrBlobPtr::operator++(int)
{
    // 此处无须检查有效性
    StrBlobPtr ret = *this;
    ++*this;
    return ret;
}

StrBlobPtr StrBlobPtr::operator--(int)
{
    StrBlobPtr ret = * this;
    --*this;
    return ret;
}
```

#### 显式地调用后置运算符
```
    StrBlobPtr p(a1);
    p.operator(0);      // 后置版本
    p.operator();       // 前置版本
```

## 6. 成员访问运算符
在迭代器和智能指针类中常常用到解引用运算（*）和箭头运算符（->）。以StrBlobPtr类为例：
```
class StrBloPtr {
public:
    std::string& operator*() const
    {   
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    std::string& operator->() const
    {
        return & this->operator*();
    }
};

StrBlob a1 = {"hi", "bye", "now"};
StrBlobPtr p(a1);       // p指向a1
*p = "okay";
cout << p->size() << endl;
cout << (*p).size() << endl;
```

#### 对箭头运算符返回值的限定
point->mem的执行过程如下：

1. 如果point是指针，则我们应用内置的箭头运算符，表达式等价于(*point).mem。首先解引用该指针，然后从所获得的对象中获取指定的成员。如果point所指的类型没有名为mem的成员，程序会发生错误。
2. 如果point是定义了operator->的类的一个对象，则C++使用point.operator->()的结果来获取men。其中，如果该结果是一个指针，则执行第一步；如果该结果本身含有重载的operator->()，则重复调用当前步骤。最终，当这一过程结束是程序或者返回了所需的内容，或者返回一些表示程序错误的信息。

## 7. 函数调用运算符
如果类重载了重载了函数调用运算符，可以像使用函数一样使用该类的对象。因为这样的类同时也能存储状态，所以比普通函数更加灵活。
```
struct absInt
{
    int operator()(int val) const {
        return val < 0 ? -val : val;
    }
};
int i =  42;
absInt absObj;
int ui = absObi(i); 
```

函数调用运算符必须是成员函数。定义了调用运算符的类的对象被称为函数对象。

函数对象类通常含有一些数据成员，这些成员通常被用于定制调用运算符中的操作。例如：
```
class PrintString {
public:
    PrintString(ostream &o = cout, char c = ' ') :
            os(o), sep(c) { }
            void operator() const(string &s) const {  os << s << sep; }
private:
    ostream &os;
    char sep;
};

PrintString printer;
printer(s);         // 在cout中打印s，后面跟一个空格
PrintString errors(cerr, '\n');
errors(s);          // 在cerr中打印s，后面跟一个换行符
```

函数对象常常作为泛型算法的实参。例如：
`for_each(vs.begin(), vs.end(), PrintString(cerr, '\n'));`


### 7.1 lambda是函数对象
当我们编写一个lambda后，编译器将该表达式翻译成一个未命名类的未命名对象。在lambda表达式产生的类中含有一个重载的函数调用运算符，例如：
```
stable_sort(words.begin(), words.end(), 
                [](const string &a, const string &b) 
                { return a.size() < b.size(); });
```

其行为类似于下面这个类的未命名对象：
```
class ShortString {
public:
    bool operator()(const string &s1, const string &s2) const
    {
        return s1.size() < s2.size();
    }
};
```

默认情况下，lambda不能改变它捕获的变量。因此，由lambda产生的类中的函数调用运算符是一个const成员函数。

#### 表示lambda及相应捕获行为的类
当一个lambda表达式通过引用捕获变量时，将由程序负责确保lambda执行时引用所引的对象却是存在。通过值捕获的变量被拷贝到lambda中，因此，这种lambda产生的类必须为每个值捕获的变量建立对应的数据成员，同时创建构造函数。例如：
```
auto wc = find_if(words.begin(), words.end(),
                [sz](const string &a)
                    { return a.size() >= sz;});
```

该表达式产生的类将形如：
```
class SizeComp {
    SizeComp(size_t n) : sz(n) { } // 该形参对应捕获的变量
    bool operator()(const string &s) const
        { return s.size() >= sz; }
private:
    size_t sz;
}
```

这个合成的类不含有默构造函数，因此要是用必须提供一个实参：
```
auto wc = find_if(words.begin(), words.end(), SizeComp(sz));
```

lambda表达式产生的类不含默认构造函数、赋值运算符及默认析构函数；它是否含有默认的拷贝/移动构造函数则通常要视捕获的数据成员类型而定。

### 7.2 标准库定义的函数对象
标准库定义了一组表示算术运算符、关系运算符和逻辑运算符的类，每个类分别定义了一个执行明明操作的调用运算符。这些类型被定义为functional头文件中。

|标准库函数对象|||
|:-------:|:-------:|:-------:|
|算术|关系|逻辑|
| plus<Type> | equal_to<Type> | logical_and<Type> |
| minus<Type> | not_equal_to<Type> | logical_or<Type> |
| multiplies<Type> | grater<Type> | logical_not<Type> |
| divides<Type> | greater_equal<Type> |     |
| modulus<Type> | less<Type> |      |  
| negate<Type> | less_equal<Type> |      |   


```
plus<int> int Add;          // 可执行int加法的函数对象
negate<int> intNegate;      // 可执行int值取反的函数对象
int sum = intAdd(10, 20);
sum = int Negate(intAdd(10, 20));
sum = intAdd(10, intNegate(10));
```

### 7.3 可调用对象与function
C++中可调用的对象有：函数、函数指针、lambda表达式、bind创建的对象以及重载了函数调用运算符的类。不同类型的可调用对象可能共享同一种调用形式：
```
int add(int i,int j) { return i + j; }
auto mod = [](int i, int j) { return i % j; }
struct divide {
    int operator()(int denominator, int divisor) {
        return denominitor / divisor;
    }
};
```

上面三个可调用对象共享一种调用形式：
```
int(int, int)
```

#### 标准库function类型
有时候，我们可能希望将add，mod和divide放入一个数据结构中，然而它们的类型不兼容。为了解决这一问题，标准库在functional头文件中定义了function库：
```
map<string, function<int(int, int)>> binops = {
    {"+", add},                                         // 函数指针
    {"-", std::minus<int>()},                           // 标准库函数对象
    {"/", divide()},                                    // 定义的对象
    {"*", []int(int i, int j) { return i * j; }},       // lambda表达式
    {"%", mod}                                          // lambda表达式
};

binops["+"](10, 5);
binops["-"](10, 5);
binops["*"](10, 5);
binops["/"](10, 5);
binops["%"](10, 5);
```

#### 重载的函数与function
不可以直接将重载的函数名字存入function类型的对象中：

```
int add(int i, int j) { return i + j; }
Sales_data add(const Sales_data&, const Sales_data&);
map<string, funtion<int(int, int>> binops;
binops.insert({"+", add}); // 错误，产生歧义
```

消除歧义的方法有两种：一是使用函数指针，二是使用lambda表达式：
```
int (*fp)(int, int) = add;
binops.insert( {"+", fp} );     // 正确
// binops.insert( {"+", [](int a, int b) { return add(a, b);} } ); // 正确
```

## 8. 重载、类型转换与运算符
类型转换运算符既没有显式的返回类型，也没有形参，还必须被定义成类的成员函数，而且由于通常不应改变带转换对象的内容，被定义为const成员。一般形式如下：
```
operator type() const;
```

举个例子：
```
class SmallInt {
public:
    SmallInt(int i = 0) : val(i)
    {
        if (i < 0 || i > 255)
            throw std::out_of_range("Bad SmallInt value");
    }
    operator int() const { return val; 
private:
    std::size_t val;
}

SmallInt si;
si = 4;     // 将4隐式转换为SmallInt，再调用SmallInt::operator=
si + 3;     // 隐式转换为int
```

为了防止隐式类型转换可能带来的异常，C++11标准引入了显式的类型转换运算符：
```
class SmllInt {
public:
    explict operator int() const { return val; }
};

SmallInt si = 3;            // 正确
si + 3;                     // 错误
static_cast<int>(si) + 3;   // 正确
```

但这条规则有例外：当表达式被用作条件时，显式类型转换会自动执行。
