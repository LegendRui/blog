# C++ Primer学习笔记之标准库特殊设施
Created by *mistery* at Jun 12, 2019.

<br><br>
## 1 tuple类型
#### 定义和初始化tuple
tuple可以看作是一个“快速而随意”的数据结构。创建tuple必须直接初始化：
```
tuple<size_t, size_t, size_t> threeD;       // 值初始化，三个成员都设置为0
tuple<string, vector<double>, int, list<int>> someVal("constants", {3.14, 2.718}, 42, {0, 1, 2, 3, 4, 5});
auto item = make_tuple("0-999-78345-X", 3, 20.00);
```

#### 访问tuple的成员
使用get标准库函数模板：
```
auto book = get<0>(item);           // 返回item的第一个成员
auto cnt = get<1>(item);            // 返回第二个
auto price = get<2>(item);          // 第三个
get<2>(item) *= 0.8;                // 返回的是引用
```

#### 查询成员数量与类型
```
typedef decltype(item) trans;           // trans与item同类型
size_t sz = tuple_size<trans>::value;       // 返回成员数量，3
tuple_element<1, trans>::type cnt = get<1>(item);   // cnt是int
```

#### 比较
具有相同数量的成员的tuple之间可以比较：
```
tuple<string, string> duo("1", "2");
tuple<size_t, size_t> twoD(1, 2);
bool b = (duo == twoD);         // 错，size_t和string无法比较
tuple<size_t, size_t, size_t> threeD(1, 2, 3);
b = (twoD <threeD);             // 错，成员数量不同
tuple<size_t, size_t> origin(0, 0);
b = (origin < twoD);            // 对，b为true
```

#### 用tuple返回多个值
例如：
```
typedef tuple<vector<Sales_datta>::size_type, 
              vector<Sales_data>::const_iterator,
              vector<Sales_data>::const_iteratir> matches;

vector<matched< findBook(const vector<vector<Sales_data>> &files,
                        const string &book)
{
    /* ... */
}
```