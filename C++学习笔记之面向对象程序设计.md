# C++学习笔记之面向对象程序设计
Created by *Mistery*
<br><br>

**面向对象程序设计**的核心思想是数据抽象、继承和动态绑定。
<br><br>

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

基类通常都应该定义一个**虚析构函数**，即使该函数不执行任何实际操作也是如此。

#### 成员函数与继承
C++中，有一些函数是基类希望派生类进行重新定义（覆盖）的，而有一些函数是基类希望派生类直接继承而不要改变的。前者通常将其定义为**虚函数**，以关键字**virtual**在类内部的声明语句之前标记。

#### 访问控制与继承
派生类可以继承定义在基类中的成员，但不一定有权限访问。某些成员，基类希望它的派生类可以访问，但禁止其他用户访问，可以用**受保护的（protected）**访问运算符说明。

<br><br>
### 1.2 定义派生类
派生类必须通过使用**类派生列表**明确指出它是从哪个（哪些）基类继承而来的。针对Bulk_Quote类，定义如下：
```
class Bulk_Quote : public Quote
{
public:
    Bulk_Quote() = default;
    Bulk_Quote(const std::string&, double, std::size_t, double);
    double net_price(std::string size_t) const override;
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};
```

#### 派生类中的虚函数
派生类经常（但不总是）覆盖它继承的虚函数。派生类可以在它覆盖的函数前使用virtual关键字，但不是非得这么做。C++允许我们在覆盖的函数的声明后面用**override**显式地注明。

#### 派生类对象及派生类向基类的类型转换
因为在派生类对象中含有与其基类对应的组成部分，所以我们能把派生类的对象当成基类对象来使用，而且我们也能将基类的指针或引用绑定到派生类对象中的基类部分上。
```
    Quote item;
    Bulk_quote bulk;
    Quote *p = &item;
    p = &bulk;
    Quote &r = bulk;
```

这类转换通常称为**派生类到基类的**（derived-to-base）类型转换。

#### 派生类构造函数
派生类对象的基类部分与派生类对象自己的数据成员都是在构造函数的初始化阶段执行初始化操作的。例如：
```
Bulk_quote::Bulk_quote(const std::string& book, double p,
                std::size_t qty, double disc) :
                Quote(book, p), min_qty(qty), discount(disc) { }
```

首先初始化基类的部分，然后按照声明的顺序依次初始化派生类的成员。

#### 派生类使用基类的成员
派生类可以访问基类的公有成员和受保护成员：
```
double Bulk_quote::net_price(size_t cnt) const
{
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}
```

#### 继承与静态成员
如果基类定义了一个静态成员，则在整个继承体系中只存在该成员的唯一定义。不论从基类中派生出来多少个派生类，对于每个静态成员来说都只存在唯一的实例。
```
class Base {
public:
    static void statmem();
};

class Derived : public Base {
    void f(const Derived&);
};
```

静态成员遵循通用的访问控制规则，如果基类中的成员是private的，则派生类无权访问它。假设某静态成员是可访问的，则我们既能通过基类使用它也能通过派生类使用它：
```
void Derived::f(const Derived & derived_obj)
{
    Base::statmem();        
    Derived::statmem();
    derived_obj.statmem();
    statmem();      // 通过this指针访问
}
```

#### 派生类的声明
声明中包含类名但是不包含它的派生列表：
```
class Bulk_quote : public Quote;        // 错误
class Bulk_quote;                       // 正确
```

#### 被用作基类的类
如果我们想将某个类用作基类，则该类必须已经完成定义而非仅仅声明：
```
class Quote;    
class Bulk_quote : public Quote { ... };    // 错误
```

#### 防止继承的发生
有时我们会定义一种不希望被其他类继承的类，或者不想考虑它是否适合作为一个基类。C++11提供关键字**final**实现这一目的：
```
class NoDerived final { /* */ };        // NoDerived不能作为基类
class base { /* */ };
class Last final : Base { /* */ };      // Last不能作为基类
class Bad : NoDerived { /* */ };        // 错误
class Bad2 : Last { /* */ };            // 错误
```

<br><br>
### 1.3 类型转换与继承
我们可以将基类的指针或引用绑定到派生类对象上。

#### 静态类型与动态类型
**静态类型**在编译时总是已知的，它是变量声明时的类型或表达式生成的类型；  
**动态类型**则是变量或表达式表示的内存中的对象的类型，到运行时才知道类型。

#### 不存在从基类向派生类的隐式类型转换
因为派生类对象含有基类的部分，因此可以将基类指针/引用绑定到派生类上。反过来，派生类指针/引用不可以绑定到基类上。
```
Quote base;
Bulk_quote bulkP = &base;       // 错误
Bulk_quote bulkRef = base;      // 错误
Bulk_quote bulk;
Quote *item = &bulk;            // 正确
```

#### 在对象之间不存在类型转换
派生类向基类的自动类型转换只针对指针或引用类型有效，在派生类类型和基类类型之间不存在这样的转换。

当我们用一个派生类对象为一个基类对象初始化或赋值时，只有该派生类对象中的基类部分会被拷贝、移动或复制，它的派生类部分会被忽略掉。

<br><br>
## 2 虚函数

#### 对虚函数的调用可能运行时才被解析
当某个函数通过指针或引用调用时，编译器产生的代码直到运行时才能确定应该调用哪个版本的函数。

#### 派生类中的虚函数
基类中的虚函数在派生类中隐含地也是一个虚函数。当派生类覆盖了某个虚函数时，该函数在积累中的形参必须与派生类中的形参严格匹配。

#### final和override说明符
C++11中我们可以使用override关键字说明派生类中的虚函数，使得程序员的意图更加明显并且让编译器为我们发现一些错误。
```
struct B {
    virtual void f1(int) const;
    virtual void f2();
    void f3();
};

struct D1 : B {
    void f1(int) const override;        // 正确
    void f2(int) override;              // 错误
    void f3() override;                 // 错误
    void f4() override;                 // 错误
}；
```

#### 虚函数与默认实参
如果虚函数使用默认实参，则基类和派生类中定义的默认实参最好一致。

#### 回避虚函数的机制
在某些情况下，我们希望对虚函数的调用不要进行动态绑定：
```
double undiscounted = baseP->Quote::net_price(42);
```

<br><br>
## 3 抽象基类

#### 纯虚函数
可以将函数定义为纯虚函数，告诉用户该函数是没有实际意义的。纯虚函数的声明是在虚函数声明后加=0实现的：
```
class Disc_quote : public Quote {
public: 
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price,
            std::size_t qty, double disc) :
            Quote(book, price), quantity(qty), discount(disc) { }
    double net_price(std::size_t) const = 0;        // 纯虚函数
proteceted：
    std::size_t quantity = 0;
    double discount = 0.0;
};
```

含有纯虚函数的类是抽象基类，抽象基类是不可以（直接）创建对象的。

<br><br>
## 4 访问控制与继承

#### 受保护的成员
protected成员：

+ 对类的用户来说是不可访问的
+ 对派生类的成员和友元来说是可访问的
+ 派生类的成员或友元只能通过派生类对象来访问基类的受保护的成员

#### 友元与继承
友元关系不可被继承，基类的友元在访问派生类成员时不具有特殊性。

#### 改变个别成员的可访问性
有时我们需要改变派生类继承的某个成员的访问级别。可以使用using声明达到这一目的：
```
class Base {
public:
    std::size_t() const { return n; }
protected:
    std::size_t n;
};

class Derived : private Base {
public:
    usnig Base::size;       // 没有括号，只用名字就行
protected:
    using Base::n;
};
```

注：派生类只能为它可以访问的名字提供using声明。

#### 默认的继承保护级别
默认情况下，使用class关键字定义的派生类是私有继承的，而使用struct关键字定义的派生类是公有继承的：
```
class Base { /* ... */ };
struct D1 : Base { /* ... */ };     // public继承
class D2 : Base { /* ... */ };      // private继承
```

<br><br>
## 5 继承中的类作用域
当存在继承关系时，派生类的作用域嵌套在其基类的作用域之内。如果一个名字在派生类的作用域内无法正确解析，则编译器将继续在外层的基类作用域中寻找该名字的定义。

#### 名字冲突与继承
派生类可以重用定义在其直接基类或间接基类中的名字，此时定义在内层作用域的名字将隐藏定义在外层作用域的名字。被隐藏的基类成员可以使用域运算符使用。
```
struct Base {
    Base() : mem(0) { }
protected:
    int mem;
};

struct Derived : Base {
    Derived(int i) : mem(i) { }         // 用i初始化Derived::mem，Base::mem进行默认初始化
    int get_mem() { return mem; }       // 返回Derived::mem
protected:
    int mem;                            // 隐藏基类中的mem
};
Derived d(42);
cout << d.get_mem() << endl;            // 42
```

#### 通过作用域运算符使用隐藏的成员
```
struct Derived : Base {
    int get_mem() { return Base::mem; }    
    /* ... */
}；
Derived d(42);
cout << d.get_mem() << endl;            // 0
```

#### 名字查找先于类型检查
派生类的成员和基类成员同名时，会隐藏基类的成员，即使派生类成员和基类成员的形参列表不一致：
```
struct Base {
    int memfcn();
};

struct Derived : Base {
    int memfcn(int);                    // 隐藏基类的memfcn
};

Derived d; Base b;
b.memfcn();
d.memfcn(10);
d.memfcn();                             // 错误
d.Base::memfcn();                       // 正确
```

<br><br>
## 6 构造函数与拷贝控制
### 6.1 虚析构函数
当我们delete一个动态分配的对象的指针时将执行析构函数。如果该指针指向继承体系中的某个类型，则有可能出现指针的静态类型与被删除对象的动态类型不符的情况。可以在基类中将析构函数定义成虚函数解决这一问题：
```
class Quote {
public:
    virtual ~Quote() = default;     // 动态绑定虚构函数
};

Quote *itemP = new Quote;       
delete itemP;                       // 调用Quote的析构函数
itemP = new Bulk_quote;             
delete itemP;                       // 调用Bulk_quote的析构函数
```

根据经验，一个类需要析构函数通常需要拷贝和赋值操作。但是虚析构函数是个例外。但是，如果一个类定义了析构函数，即使是合成版本的，编译器也不会为这个类合成移动操作。

<br><br>
### 6.2 合成拷贝控制与继承
#### 派生类中删除的拷贝控制与基类的关系
某些定义基类的方式可能导致有的派生类成员被成为删除函数：
* 基类中的默认/拷贝构造函数、拷贝复制运算符或析构函数是删除函数或者不可访问的，则派生类中对应的成员将是删除的
* 基类中有一个不可访问或删除掉的析构函数，则派生类中合成的默认和拷贝构造函数是删除的
* 编译器不会合成一个删除掉的移动操作
例如：
```
class B {
public:
    B();
    B(const B&) = delete;
};

class D {
    // 不声明任何构造函数
};

D d;                            // 正确
D d2(d);                        // 错误，D的合成拷贝构造函数是被删除的
D d3(std::move(d));             // 错误，隐式地使用D的被删除的拷贝构造函数
```

#### 移动操作与继承
由于大多数基类会定义虚析构函数，所以基类通常不含合成的移动操作，其派生类因而也没有移动操作。当派生类需要移动操作的时候，应该在基类定义移动操作：
```
class Quote {
public:
    Quote() = default;              
    Quote(const Quote&) = default;              
    Quote(Quoe&&) = default;
    Quote& operator=(const Quote&) = default;
    Quote& operator=(Quote&&) = default;
    virtual ~Quote() = default;
};
```

通过以上的定义，派生类就会获得合成的移动操作（除非含有排斥移动的成员）。

<br><br>
### 6.3 派生类的拷贝控制成员
当为派生类定义拷贝或移动构造函数时，通常使用对应的基类构造函数初始化化对象的基类部分：
```
class Base { /* ... */ };
class D : public Base {
public:
    D(const D& d) : Base(d)             // 拷贝基类成员
            /* D的成员的初始值 */  { /* ... */ }
    D(D&& d) : Base(std::move(d))       // 移动基类成员
            /* D的成员的初始值 */ { /* ... */ }
}；
```

默认情况下，基类默认构造函数初始化派生类对象的基类部分。如果我们想拷贝（移动）基类部分，则必须咋子派生类的构造函数初始值列表中显式地使用基类的拷贝（移动）构造函数。

#### 派生类赋值运算符
派生类的赋值运算符必须显式地为其基类部分赋值：
```
D &D::operator=(const D &rhs) 
{
    Base::operator=(rhs);       // 显式为基类部分赋值
    /* ... */
    return *this;
};
```

#### 派生类析构函数
执行完析构函数体后，对象的基类部分是隐式地销毁的，派生类析构函数只负责销毁由派生类自己分配的资源：
```
class D : public Base {
public:
    // Base::~Base被自动调用执行
    ~D() { /* ... */}
};
```
对象销毁的顺序正好与其创建的顺序相反：派生类析构函数首先执行，然后是基类的析构函数。

#### 在构造函数和析构函数中调用虚函数
如果构造函数或析构函数调用了某个虚函数，则我们应该执行与构造函数或析构函数所属类型相对应的虚函数版本。

<br><br>
### 6.4 继承的构造函数
<br/><br/>
## 7 容器与继承

