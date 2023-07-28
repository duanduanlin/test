# dbus测试
## 环境搭建
- git clone https://github.com/GENIVI/capicxx-core-runtime.git
- git clone https://github.com/GENIVI/capicxx-dbus-runtime.git
- wget http://dbus.freedesktop.org/releases/dbus/dbus-1.10.10.tar.gz
- git clone https://github.com/COVESA/capicxx-dbus-tools.git
- git clone https://github.com/COVESA/capicxx-core-tools.git
## 测试程序
- 编译
    ./build.sh
- 准备
    -- export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/
    -- export DBUS_SESSION_BUS_ADDRESS=unix:path=/tmp/dbus-o6ujiqBKsY

    -- dbus-daemon --fork --session --address=unix:path=/tmp/dbus-o6ujiqBKsY
### hello world程序
- HelloWorldService 会提供一个sayHello的方法。
- HelloWorldClient 会去调用HelloWorldService的sayHello方法。

#### 运行
- ./output/apps/bin/HelloWorldService&
- ./output/apps/bin/HelloWorldClient&
#### 查看资源开销
 ps -xH | grep Hello
 27715 pts/2    SNl    0:00 ./output/apps/bin/HelloWorldClient
 27715 pts/2    SNl    0:00 ./output/apps/bin/HelloWorldClient
 27715 pts/2    SNl    0:00 ./output/apps/bin/HelloWorldClient
 27814 pts/2    SNl    0:00 ./output/apps/bin/HelloWorldService
 27814 pts/2    SNl    0:00 ./output/apps/bin/HelloWorldService
 27814 pts/2    SNl    0:00 ./output/apps/bin/HelloWorldService
#### 查看资源开销
 ps -aux | grep Hello
dding3    28775  0.0  0.0 107564  4332 pts/2    SNl  01:31   0:00 ./output/apps/bin/HelloWorldService
dding3    28797  0.0  0.0 173024  4208 pts/2    SNl  01:32   0:00 ./output/apps/bin/HelloWorldClient

cat /proc/28775/status

VmData:    16864 kB
VmStk:       132 kB
VmExe:       172 kB
VmLib:      6244 kB
VmPTE:        92 kB
VmSwap:        0 kB

Threads:        3

cat /proc/28797/status
Name:   HelloWorldClien

VmData:    16996 kB
VmStk:       132 kB
VmExe:       172 kB
VmLib:      6244 kB
VmPTE:       112 kB
VmSwap:        0 kB

Threads:        3

#### 总结
- 看起来不管是server和是client都消耗了三个线程，这个和代码中看到的是一致的，一个dispatch线程，一个timeout线程，一个async线程。
- 132KB的栈，这个也可以解释，因为不管是client还是server其本质上都是client，应用代码不是很多的话栈开销应该是类似的
- 6M的库

### good bye程序
- HelloWorldService 会提供一个sayHello的方法。
- GoodByeService 会提供一个sayGoodBye的方法。
- GoodByeClien会轮流调用sayHello和sayGoodBye方法。
#### 运行
- ./output/apps/bin/HelloWorldService&
- ./output/apps/bin/GoodByeService&
- ./output/apps/bin/GoodByeClient&
#### 查看资源开销
ps -aux | grep Good
dding3    42658  0.0  0.0 107796  4448 pts/6    SNl  19:38   0:00 ./output/apps/bin/GoodByeService
dding3    42759  0.0  0.0 173612  5148 pts/6    SNl  19:39   0:00 ./output/apps/bin/GoodByeClient

cat /proc/42658/status
Name:   GoodByeService

VmData:    16864 kB
VmStk:       132 kB
VmExe:       168 kB
VmLib:      6244 kB
VmPTE:       104 kB
VmSwap:        0 kB

Threads:        3

cat /proc/42759/status
Name:   GoodByeClient

VmData:    16996 kB
VmStk:       132 kB
VmExe:       276 kB
VmLib:      6244 kB
VmPTE:        96 kB
VmSwap:        0 kB

Threads:        3

#### 总结
- 线程数还是三个？这个和代码里是能对的上的，runtime是单例的，只有一个连接，而不管有几个proxy都是经过同一个连接处理的。
- 栈空间并没有明显变化，这说明资源开销最大的其实是建立连接。
- client的进程大小276KB，比单个proxy的大了100KB左右。这个也可以解释，因为多了一套proxy的实现。

### welcome 程序
- WelcomeService提供一个sayHi的方法和welcome广播。
- WelcomeClient订阅welcome广播，并在收到广播是调用sayHi。
#### 运行
- ./output/apps/bin/WelcomeService&
- ./output/apps/bin/WelcomeClient&

#### 查看资源开销
ps -aux | grep Wel
dding3    48445  0.0  0.0 107380  4200 pts/2    SNl  23:04   0:00 ./output/apps/bin/WelcomeService
dding3    48553  0.0  0.0 172920  4280 pts/2    SNl  23:04   0:00 ./output/apps/bin/WelcomeClient

cat /proc/48445/status
Name:   WelcomeService

VmData:    16864 kB
VmStk:       132 kB
VmExe:       212 kB
VmLib:      6244 kB
VmPTE:       104 kB
VmSwap:        0 kB

Threads:        3

cat /proc/48553/status
Name:   WelcomeClient

VmData:    16996 kB
VmStk:       132 kB
VmExe:       216 kB
VmLib:      6244 kB
VmPTE:       108 kB
VmSwap:        0 kB

Threads:        3

#### 总结
- 可以看到，多了一个广播，只是进程大小多了40K左右，除此之外并无其他影响。
