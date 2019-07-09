# C++知识点

## 1 顶层/底层const
**顶层const：**表示指针本身是个常量  
**底层const：**表示指针所指的对象是一个常量

更一般的，顶层const可以表示任意的对象时常量，这一点对任何数据类型都适用，如算数类型、类、指针等。底层const则与指针和引用等复合类型的基本类型部分有关。比较特殊的是，指针类型既可以是顶层const也可以是底层const，这一点和其他类型相比区别明显：
```
int i = 0;
int *const p1 = &i;         // 不能改变p1的值，这是一个顶层const
const int ci = 42;          // 不能改变ci的值，这是一个顶层const
const int *p2 = &ci;        // 允许改变p2的值，这是一个底层const
const int *const p3 = p2;   // 第一个是底层const，第二个是顶层const
const int &r = ci;          // 用于声明引用的都是底层const
```
