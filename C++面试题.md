# C++面试题
## 1. 编写一个标准的strcpy函数
基本答案：
```
void strcpy(char *dst, const char *src) {
    assert( (dst != NULL) && (src != NULL));   // 需要有断言
    while ((*dst++ = *src++) != '\0');
}
```
更进一步，可以将目的地址返回，便于实现链式操作：
```
char* strcpy(char *dst, const char* src) {
    assert((src != NULL) && (dst != NULL));
    char *origin = dst;
    while ((*dst = *src) != '\0');
    return origin;
}
```
