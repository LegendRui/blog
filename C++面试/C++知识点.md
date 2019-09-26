# C++知识点

<font size="3">
<br><br>

## 1.顶层/底层const

**顶层const：**表示指针本身是个常量  
**底层const：**表示指针所指的对象是一个常量

更一般的，顶层const可以表示任意的对象是常量，这一点对任何数据类型都适用，如算数类型、类、指针等。底层const则与指针和引用等复合类型的基本类型部分有关。比较特殊的是，指针类型既可以是顶层const也可以是底层const，这一点和其他类型相比区别明显：
```
int i = 0;
int *const p1 = &i;         // 不能改变p1的值，这是一个顶层const
const int ci = 42;          // 不能改变ci的值，这是一个顶层const
const int *p2 = &ci;        // 允许改变p2的值，这是一个底层const
const int *const p3 = p2;   // 第一个是底层const，第二个是顶层const
const int &r = ci;          // 用于声明引用的都是底层const
```

---
## 2.new和delete操作的过程

**new**操作分三步：

+ i) new表达式调用一个名为operator new（或者operator new[]）的标准库函数，该函数分配一块足够大的、原始的、未命名的内存空间以便存储特定类型的对象
+ ii) 编译器运行相应的构造函数以构造这些对象，为其传入初始值
+ iii) 对象被分配了空间并且构造完成，返回一个指向该对象的指针

**delete**操作分两步：

- i) 对sp所指的对象或者arr所指的数组中的元素执行对应的析构函数
- ii) 编译器调用名为operator delete（或者operator delete[]）的标准库函数释放内存空间

因为operator new用在对象构造之前，而operator delete用在对象销毁之后，所以这两个函数如果定义为类成员时必须是static的（默认就是static的）。

---
## 3.dynamic_cast与typeid运算符
**dynamic_cast**运算符的使用形式如下：  
dynamic_cast<type*>(e)  
dynamic_cast<type&>(e)  
dynamic_cast<type&&>(e)  
其中type必须是一个类类型，并且通常应该含有虚函数。指针类型的使用例子：
```
if (Derived *dp = dynamic_cast<Derived *>(bp))
{
    // 使用dp指向的Derived对象
} else {
    // bp指向一个Base对象，使用指向的Base对象
}
```

引用类型的使用例子：
```
void f(const Base &b) 
{
    try {
        const Derived &d = dynamic_cast<const Derived&>(b);
        // 使用b引用的Derived对象
    } catch(bad_cast) {
        // 处理类型转换失败的情况
    }
}
```


**typeid**运算符可以作用于任意类型的表达式。如果表达式是一个引用，返回该引用所引对象的类型。当typeid作用于数组或者函数时，不会执行向标准类型的转换。

当运算对象不属于类类型或者不包含任何虚函数的类时，typeid运算符指示的是运算对象的静态类型，而当运算对象是定义了至少一个虚函数的类的左值时，typeid的结果知道运行时才会求得。
```
Derived *dp = new Derived;
Base *bp = dp;
if (typeid(*bp) == typeid(*dp)) {
    // bp和dp指向同一类型的对象
}
if (typeid(*bp) == typeid(Derived)) {
    / bp实际指向Derived类型
}
```


</font><br />