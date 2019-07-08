# C++学习笔记之模板与泛型编程
Created by *Mistery* at Jun 8, 2019.
<br><br>

## 1. 定义模板
### 1.1 函数模板
一个函数模板就是一个公式，可以用来生成特定类型的函数版本。例如：
```
template <typename T>
int compare(const T &v1, const T &v2) 
{
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}
```

#### 实例化函数模板
编译器用推断出来的模板参数为我们**实例化**一个特定版本的函数。例如
```
cout << compare(1, 0) << endl;              // T为int
```
编译器为这个调用生成的函数实例为：
```
int compare(const int &v1, const int &v2)
{
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}
```

#### 模板类型参数
一般来说，可以将类型参数看作类型说明符，像内置类型或类类型说明符一样使用。例如，类型参数可以用来指定返回类型或函数的参数类型，以及在函数体内用于变量声明或类型转换：
```
template <typename T> T foo(T* p)
{
    T tmp = *p;
    /* ... */
    return tmp;
}  
```

#### 非类型模板参数
除了定义类型参数，还可以在模板中定义非类型参数。一个非类型参数表示一个值而非一个类型。
例如，我们可以编写一个compare版本处理字符串字面常量。这种字面常量是const char数组。由于不能拷贝一个数组，所以我们将自己的参数定义为数组的引用。由于我们希望能比较不同长度的字符串，因此为模板定义了两个非类型的参数：
```
template <unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M])
{
    return strcmp(p1, p2);
}
```
一个非类型参数可以是一个整型，或者是一个指向对象或函数类型的指针或引用。绑定到非类型整形参数的实参必须是一个常量表达式；绑定到指针或引用非类型参数的实参必须具有静态的生存期。

#### inline和constexpr的函数模板
函数模板可以声明为inline或constexpr的，相应的说明符放在模板参数列表之后，返回类型之前：
```
template <typename T> inline T min(const T&, const T&);
```

#### 编写类型无关的代码
以上定义的compare函数虽然简单，但它说明了编写泛型代码的两个重要原则：

* 模板中的函数参数是const的引用（可以用于不能拷贝的类型）
* 函数体中的条件判断仅使用<比较运算（较低对要处理的类型的要求）
