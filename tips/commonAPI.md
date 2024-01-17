# 资源
环境搭建：CommonAPI环境搭建_commonapi dbus_熟练工的博客-CSDN博客

使用说明：(126条消息) CommonAPI 使用说明文档_commonapi dbus_C_Silence_K的博客-CSDN博客

fidl介绍：CommonAPI C++(fdepl)介绍-腾讯云开发者社区-腾讯云 (tencent.com)

官方文档：Home · COVESA/capicxx-core-tools Wiki (github.com)

源码：GitHub - COVESA/capicxx-core-runtime: Common API C++ core runtime

源码：GitHub - COVESA/capicxx-dbus-runtime: Common API C++ dbus runtime

工具：COVESA/capicxx-dbus-tools: Common API C++ dbus tooling (github.com)

工具：COVESA/capicxx-core-tools: Common API C++ core tools (github.com)

## dbus工具
dbus-send
用于发送一个消息到消息通道上，使用格式如下：

dbus-send [--system | --session] --type=TYPE --print-reply --dest=连接名对象路径接口名.方法名参数类型:参数值参数类型:参数值
dbus-send --session --type=method_call --print-reply --dest=连接名对象路径接口名.方法名 参数类型:参数值 参数类型:参数值

dbus-send支持的参数类型包括：string,uint16,int16, int32, uint32, double, byte, boolean。

模拟广播发送：

dbus-send --session --type=signal /com/commonapi/mcu_transceiver mcu_transceiver.McuTransceiver.handShakeStatus uint32:3

模拟函数调用

dbus-send --session --type=method_call --print-reply --dest=vehicle_agent.VehicleAgent_com.commonapi.vehicle_agent /com/commonapi/vehicle_agent vehicle_agent.VehicleAgent.getCommonInfo

## dbus-monitor
用于打印消息通道上的消息，使用格式如下：

dbus-monitor [--system | --session | --address ADDRESS] [--profile | --monitor] [watch expressions]
dbus-monitor "type='signal', sender='org.gnome.TypingMonitor', interface='org.gnome.TypingMonitor'"



监听当前DBUS_SESSION_BUS_ADDRESS地址上的所有会话消息：

dbus-monitor --session --monitor

监听所有信号：

dbus-monitor --session --monitor "type=signal"

监听指定接口的消息：

dbus-monitor --session --monitor "interface=mcu_transceiver.McuTransceiver"

监听指定接口的所有信号：

dbus-monitor --session --monitor "type=signal,interface=mcu_transceiver.McuTransceiver"

或者监听指定的信号：

dbus-monitor --session --monitor "type=signal,interface=mcu_transceiver.McuTransceiver"

## dbus简介
参考文档：https://blog.csdn.net/f110300641/article/details/106823611


dbus中的消息由一个消息头（标识是哪一种消息）和消息数据组成，比socket的流式数据更方便一些。

bus daemon 就像是一个路由器，与各个应用程序进行连接，分派这些消息。

bus daemon 在一台机器上有多个实例，第一个实例是全局的实例，类似于sendmail和或者apache，这个实例有很严格的安全限制，只接受一些特定的系统消息， 用于系统通信。

其他bus daemon是一些会话，用于用户登录之后，在当前会话(session)中进行的通讯。

系统的bus daemon 和会话的bus daemon 是分开的，彼此不会互相影响，会话bus daemon 不会去调用系统的bus daemon 。

### D-Bus的基本概念
D-Bus是一个消息总线系统，其功能已涵盖进程间通信的所有需求，并具备一些特殊的用途。D-Bus是三层架构的进程间通信系统，其中包括：

接口层：接口层由函数库libdbus提供，进程可通过该库使用D-Bus的能力。

总线层：总线层实际上是由D-Bus总线守护进程提供的。它在Linux系统启动时运行，负责进程间的消息路由和传递，其中包括Linux内核和Linux桌面环境的消息传递。

包装层：包装层一系列基于特定应用程序框架的Wrapper库。

D-Bus具备自身的协议，协议基于二进制数据设计，与数据结构和编码方式无关。该协议无需对数据进行序列化，保证了信息传递的高效性。无论是libdbus，还是D-Bus总线守护进程，均不需要太大的系统开销。

总线是D-Bus的进程间通信机制，一个系统中通常存在多条总线，这些总线由D-Bus总线守护进程管理。最重要的总线为系统总线（System Bus），Linux内核引导时，该总线就已被装入内存。只有Linux内核、Linux桌面环境和权限较高的程序才能向该总线写入消息，以此保障系统安 全性，防止有恶意进程假冒Linux发送消息。

会话总线（Session Buses）由普通进程创建，可同时存在多条。会话总线属于某个进程私有，它用于进程间传递消息。

进程必须注册后才能收到总线中的消息，并且可同时连接到多条总线中。D-Bus提供了匹配器（Matchers）使进程可以有选择性的接收消息，另 外运行进程注册回调函数，在收到指定消息时进行处理。匹配器的功能等同与路由，用于避免处理无关消息造成进程的性能下降。除此以外，D-Bus机制的重要 概念有以下几个。

对象：对象是封装后的匹配器与回调函数，它以对等（peer-to-peer）协议使每个消息都有一个源地址和一个目的地址。这些地址又称为对象路 径，或者称之为总线名称。对象的接口是回调函数，它以类似C++的虚拟函数实现。当一个进程注册到某个总线时，都要创建相应的消息对象。

消息：D-Bus的消息分为信号（signals）、方法调用（method calls）、方法返回（method returns）和错误（errors）。信号是最基本的消息，注册的进程可简单地发送信号到总线上，其他进程通过总线读取消息。方法调用是通过总线传递 参数，执行另一个进程接口函数的机制，用于某个进程控制另一个进程。方法返回是注册的进程在收到相关信息后，自动做出反应的机制，由回调函数实现。错误是 信号的一种，是注册进程错误处理机制之一。

服务：服务（Services）是进程注册的抽象。进程注册某个地址后，即可获得对应总线的服务。D-Bus提供了服务查询接口，进程可通过该接口查询某个服务是否存在。或者在服务结束时自动收到来自系统的消息。

### 类型
D-Bus有一个类型系统，其中各种类型的值可以是 以标准方式序列化为称为连线格式的字节序列。 将值从某种其他表示形式转换为连线 格式称为封送处理和转换 它从线路格式返回是解封的。

D-Bus 协议在封送数据中不包含类型标记;一个 封送处理值块必须具有已知类型 签名。类型签名由零个或多个单个完整组成 类型，每个类型由一个或多个类型代码组成。

类型代码是一个 ASCII 字符，表示 值的类型。由于使用了 ASCII 字符，因此类型签名 将始终形成有效的 ASCII 字符串。一个简单的字符串比较 确定两个类型签名是否等效。

### 认证
该协议是基于行的协议，每行以 \r\n 结尾。每行以全大写 ASCII 命令名称开头，仅包含字符范围 [A-Z_]、空格、命令的任何参数，然后以 \r\n 结束该行。该协议区分大小写。所有字节必须位于 ASCII 字符集中。

客户端向服务器端发送的命令如下：

AUTH [mechanism] [initial-response]
CANCEL
BEGIN
DATA <data in hex encoding>
ERROR [human-readable error explanation]
NEGOTIATE_UNIX_FD

从服务端到客户端的流程如下：

REJECTED <space-separated list of mechanism names>
OK <GUID in hex>
DATA <data in hex encoding>
ERROR [human-readable error explanation]
AGREE_UNIX_FD
服务器地址
服务器地址由传输名称后跟冒号组成，并且 然后是 key=value 格式中以逗号分隔的可选键和值列表。 每个值都被转义。

例如：

unix:path=/tmp/dbus-test

这是路径为 /tmp/dbus-test 的 unix 套接字的地址。


### 消息总线
消息总线接受来自一个或多个应用程序的连接。 连接后，应用程序可以与其他应用程序交换消息 也连接到总线的应用程序。

为了在连接之间路由消息，消息总线保留 从名称到连接的映射。每个连接都有一个 自动分配总线生命周期内唯一的名称。
