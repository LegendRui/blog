# CPU调度

### 衡量调度算法的指标
+ CPU使用率：CPU处于忙状态所占时间的百分比
+ 吞吐量：在单位时间内完成的进程数量
+ 周转时间：一个进程从初始化到结束，包含所有等待时间所花费的时间
+ 等待时间：进程在就绪队列中的总时间
+ 响应时间：从一个请求被提交到产生第一次响应所花费的时间

### 调度算法
+ FCFS：先来先服务
    + 优点：简单
    + 缺点
        + 平均等待时间波动较大
        + 花费时间少的任务可能排在花费时间长的任务后面
        + 可能导致I/O和CPU之间的重叠处理
+ SPN/SJF/SRT：短进程优先/短作业优先/短剩余时间优先
    + 优点：平均等待时间最小
    + 缺点：
        + 可能导致饥饿
        + 需要预知未来
+ HRRN：最高响应比优先
    + 缺点： 
        + 不可抢占
        + 需要预知抢占时间
+ Round Robin：轮循
    + 需要额外的上下文切换
    + 时间量子过大/过小会导致性能退化
+ Multilevel Feedback Queues：多级反馈队列
    + 优点：
        + CPU密集型任务的优先级下降很快
        + I/O密集型任务停留在高优先级
+ Fair Share Scheduling：公平共享调度

### 实时调度
+ 定义
    + 正确性依赖于其时间和功能两方面的一种操作系统

###  共享变量保护
+ 屏蔽中断法
+ 软件锁
    + Peterson算法
    + 互斥
    + 有限等待
    + 前进
+ 高级抽象
    + test-and-set
    + exchange

+ 信号量
    + P()：sem减1，如果sem<0，等待，否则继续
    + V()：sem加1，如果sem<=0,唤醒一个等待的P

### 死锁
+ 出现的条件
    + 互斥：在一个时间只能有一个进程使用资源
    + 占用并等待：进程保持至少一个资源并正在等待获取其他进程持有的额外资源
    + 无抢占：一个资源只能被进程自愿释放
    + 循环等待：存在等待进程集合{P0，P1，···，Pn}，P0正在等待P1所占用的资源，P1正在等待P2占用的资源，···，Pn-1正在等待Pn所占用的资源，Pn正在等待P0所占用的资源。

+ 处理办法
    + 死锁预防
    + 死锁避免
        + 银行家算法
            - 多个实例
            - 每个进程必须能最大限度地利用资源
            - 当一个进程请求一个资源，就不得不等待
            - 当一个进程获得所有的资源就必须在一段有限的时间释放它们
    + 死锁检测
    + 死锁恢复

### IPC 
