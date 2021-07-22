## Notes of Learning Redis

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