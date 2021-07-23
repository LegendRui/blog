## Notes of Learning Redis

### 客户端
一个服务器可以对应多个客户端，这些客户端在服务器中以链表`clients`保存。

#### 客户端属性
##### 套接字描述符
```
typedef struct redisClient {
    // ...
    int fd;
    // ...
} redisClient;
```
+ 伪客户端：来源于AOF文件或LUA脚本，该值为-1，表示不需要套接字
+ 普通客户端：值为大于-1的整数，记录的是套接字描述符

可以通过命令`client list`查看套接字描述符。

##### 名字
```
typedef struct redisClient {
    // ...
    robj *name;
    // ...
} redisClient;
```
可以通过命令`client list`查看客户端名字。

##### 标志
```
typedef struct redisClient {
    // ...
    int flags; // 记录了客户端的角色以及所处的状态
    // ...
} redisClient;
```
角色部分：
+ `REDIS_MASTER`：表示客户端代表的是主服务器
+ `REDIS_SLAVE`：表示客户端代表的是从服务器
+ `REDIS_PRE_PSYNC`：表示客户端是低于Redis2.8的版本，主服务器不能用`PSYNC`命令与从服务器进行同步
+ `REDIS_LUA_CLIENT`：表示客户端是处理Lua脚本的伪客户端

状态部分：
+ `REDIS_MONITOR`：表示客户端正在处理`MONITOR`命令
+ `REDIS_UNIX_SOCKET`：表示客服务器是在用unix套接字连接客户端
+ `REDIS_BLOCKED`：表示客户端正在被`BRPOP`、`BLPOP`等命令阻塞
+ \\ todo ...

##### 输入缓冲区
```
typedef struct redisClient {
    // ...
    sds querybuf; // 保存客户端发送的命令请求
    // ...
} redisClient;
```
输入缓冲区的大小会根据输入内容动态地缩小或者扩大，但它的最大大小不能超过1GB，否则服务器将关闭这个客户端。

##### 命令与命令参数
```
typedef struct redisClient {
    // ...
    robj **argv; // 字符串数组，保存命令的参数
    int argc;    // 参数的数目
    // ...
} redisClient;
```

##### 命令的实现函数
```
typedef struct redisClient {
    // ...
    struct redisCommand *cmd; // 保存命令的实现函数
    // ...
} redisClient;
```
命令表是一个字典，字典的键是一个SDS结构，保存命令的名字。字典的值是命令所对应的`redisCommand`结构，记录了命令的实现函数、命令的标志、命令应该给定的参数个数、命令的总执行次数和总消耗时长等统计信息。当在命令表中成功找到`argv[0]`所对应`redisCommand`结构后，会将客户端状态的cmd指向它。

##### 输出缓冲区
每个客户端有两个输出缓冲区可用，一个大小固定，一个大小可变：
+ 固定大小的缓冲区用于保存长度较小的回复，例如OK、错误回复、整数等
+ 可变大小的缓冲区用于保存长度较大的回复，例如长字符串、列表等
```
typedef struct redisClient {
    // ...
    char buf[REDIS_REPLY_CHUNK_BYTES]; // 固定缓冲区，默认是16*1024
    int bufpos;                        // 已使用的字节数 
    // ...
    list *reply;                        // 可变大小缓冲区
    // ...
} redisClient;
```

##### 身份验证
```
typedef struct redisClient {
    // ...
    int authenticated;  // 记录客户端是否通过身份验证，0表示未通过，1表示通过
    // ...
} redisClient;
```
`authenticated`属性仅在服务器启用身份验证的功能时使用。启用后，`authenticated`为0，只能执行`AUTH`命令，其他命令会拒绝。

##### 时间
```
typedef struct redisClient {
    // ...
    time_t ctime;   // 创建客户端的时间
    time_t lastinteraction;     // 最后一次交互的时间
    time_t obuf_soft_limit_reached_time;   // 输出缓冲区第一次到达软性限制的时间
    // ...
} redisClient;
```

#### 客户端的创建与关闭
##### 创建普通客户端
通过网络与服务器进行连接的普通客户端，服务器会调用连接时间处理器为客户端创建相应的客户端状态，并将这个新的客户端状态添加到服务器状态结构的`clients`链表的末尾。

##### 关闭普通客户端
普通客户端关闭的原因有：
+ 客户端进程退出或被杀死
+ 客户端发送了不符合协议的命令
+ 客户端成为`CLIENT KILL`命令的目标
+ 服务器的空转时间超过了`timeout`设置的目标值
+ 客户端发送的命令请求的大小超过了输入缓冲区的大小限制（默认1GB）
+ 要给客户端的命令回复超过了输出缓冲区的大小限制

##### LUA脚本的伪客户端的创建与关闭
在服务器初始化时创建，在服务器运行的整个生命期一直存在。
```
struct redisServer {
    // ... 
    redisClient *lua_client;
    // ...
}
```

##### AOF文件伪客户端的创建与关闭
服务器在载入AOF文件时，会创建用于执行AOF文件包含的Redis命令的伪客户端；在载入完成后关闭。

### 服务器
#### 命令请求的执行过程
```flow
st=>start: 开始
op=>operation: 更新服务器时间缓存
op1=>operation: 更新LRU时钟
op2=>operation: 更新服务器每秒执行命令的次数
op3=>operation: 更新服务器内存峰值记录
op4=>operation: 处理SIGTERM信号
op5=>operation: 管理客户端资源
op6=>operation: 管理数据库资源
op7=>operation: 执行被延迟的BGREWRITEAOF
op8=>operation: 检查持久化操作的运行状态
op9=>operation: 将AOF缓冲区的内容写到AOF文件
op10=>operation: 关闭异步客户端
op11=>operation: 增加cronloops计数器的值
e=>end
st->op->op1->op2->op3->op4->op5->op6->op7->op8->op9->op10->op11->e
` ``
