# C++面试高频题

### 1. TCP三次握手与四次挥手
+ 三次握手
    * 第一次：Client将SYN标志位置为1，随机产生一个序号seq=x，将该数据包发送给Server，Client进入SYN_SENT状态，等待Server回应
    * 第二次：Server收到数据包后根据SYN为1判断Cl6ient请求建立连接。Server将标志位SYN与ACK都置为1，ack=x+1，随机产生一个序号seq=y，将该数据包发送给Client，Server进入SYN_RCVD状态
    * 第三次：Client收到确认数据包后，检查是否ack=x+1，如果正确则将ACK置为1，ack=y+1，seq=x+1，并将该数据包发送给Server，Server收到后确认是否ACK=1，是否ack=y+1，如果正确则连接建立成功，Client和Server进入ESTABLISHED状态，三次握手结束
![握手过程](../pics/woshou.jpg "woshou")

+ 四次挥手
    * 第一次：Client将FIN标志位置为1，随机产生一个序号seq=u,将该数据包发送给Server，此后关闭了Client到Server的数据传送，Client进入FIN_WAIT_1状态
    * 第二次：Server收到数据包后根据FIN=1判断Client请求断开连接，Server将ACK=1，将ack=u+1，随机产生一个序号seq=v，发送该数据包，Server进入CLOSE_WAIT状态，等待将数据发送完；Client收到该数据包后进入CLOSE_WAIT_2状态
    * 第三次：Server将FIN=1，ACK=1，ack=u+1，随机产生一个序号seq=w，将该数据包发送给Client，Server进入LAST_ACK状态
    * 第四次：Client收到数据包后检查其中FIN，发现为1，接着将ACK=1，seq=u+1，ack=w+1，发送给数据包给Server，Client进入TIME_WAIT状态；Server收到后关闭连接，进入CLOSE状态，Client在发送给数据包后等待2MSL（报文最大生存时间）然后关闭连接，进入CLOSE状态
![挥手过程](../pics/uhishou.jpg "huishou")