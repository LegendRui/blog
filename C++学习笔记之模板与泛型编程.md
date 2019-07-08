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

