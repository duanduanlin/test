# dbus测试
## 环境搭建
git clone https://github.com/GENIVI/capicxx-core-runtime.git
git clone https://github.com/GENIVI/capicxx-dbus-runtime.git
wget http://dbus.freedesktop.org/releases/dbus/dbus-1.10.10.tar.gz
git clone https://github.com/COVESA/capicxx-dbus-tools.git
git clone https://github.com/COVESA/capicxx-core-tools.git
## 测试程序
### hello world程序
#### 1-生成代码
    `cd project/helloworld/fidl
    ../../tools/commonapi_core_generator/commonapi-core-generator-linux-x86_64 -sk fidl/HelloWorld.fidl
    ../../tools/commonapi_dbus_generator/commonapi-dbus-generator-linux-x86_64 fidl/HelloWorld.fidl`
#### 2-编译
    `cd project
    ./buildProject.sh helloworld`
#### 3-运行
#### 准备
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/
    export DBUS_SESSION_BUS_ADDRESS=unix:path=/tmp/dbus-o6ujiqBKsY

    dbus-daemon --fork --session --address=unix:path=/tmp/dbus-o6ujiqBKsY
#### 运行
    ./output/apps/bin/HelloWorldService
    ./output/apps/bin/HelloWorldClient
### 测试
#### 查看线程数
$ ps -xH | grep Hello
 27715 pts/2    SNl    0:00 ./output/apps/bin/HelloWorldClient
 27715 pts/2    SNl    0:00 ./output/apps/bin/HelloWorldClient
 27715 pts/2    SNl    0:00 ./output/apps/bin/HelloWorldClient
 27814 pts/2    SNl    0:00 ./output/apps/bin/HelloWorldService
 27814 pts/2    SNl    0:00 ./output/apps/bin/HelloWorldService
 27814 pts/2    SNl    0:00 ./output/apps/bin/HelloWorldService
#### 查看资源开销
$ ps -aux | grep Hello
dding3    28775  0.0  0.0 107564  4332 pts/2    SNl  01:31   0:00 ./output/apps/bin/HelloWorldService
dding3    28797  0.0  0.0 173024  4208 pts/2    SNl  01:32   0:00 ./output/apps/bin/HelloWorldClient

cat /proc/28775/status
Name:   HelloWorldServi
Umask:  0002
State:  S (sleeping)
Tgid:   28775
Ngid:   0
Pid:    28775
PPid:   17540
TracerPid:      0
Uid:    1000    1000    1000    1000
Gid:    1000    1000    1000    1000
FDSize: 64
Groups: 4 24 27 30 46 113 128 1000
NStgid: 28775
NSpid:  28775
NSpgid: 28775
NSsid:  17540
VmPeak:   173100 kB
VmSize:   107564 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:      4332 kB
VmRSS:      4332 kB
RssAnon:             252 kB
RssFile:            4080 kB
RssShmem:              0 kB
VmData:    16864 kB
VmStk:       132 kB
VmExe:       396 kB
VmLib:      6244 kB
VmPTE:        96 kB
VmSwap:        0 kB
HugetlbPages:          0 kB
CoreDumping:    0
Threads:        3
SigQ:   0/31574
SigPnd: 0000000000000000
ShdPnd: 0000000000000000
SigBlk: 0000000000000000
SigIgn: 0000000000000000
SigCgt: 0000000180000000
CapInh: 0000000000000000
CapPrm: 0000000000000000
CapEff: 0000000000000000
CapBnd: 0000003fffffffff
CapAmb: 0000000000000000
NoNewPrivs:     0
Seccomp:        0
Speculation_Store_Bypass:       thread vulnerable
Cpus_allowed:   ffffffff,ffffffff,ffffffff,ffffffff
Cpus_allowed_list:      0-127
Mems_allowed:   00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000001
Mems_allowed_list:      0
voluntary_ctxt_switches:        4
nonvoluntary_ctxt_switches:     12

$ cat /proc/28797/status
Name:   HelloWorldClien
Umask:  0002
State:  S (sleeping)
Tgid:   28797
Ngid:   0
Pid:    28797
PPid:   17540
TracerPid:      0
Uid:    1000    1000    1000    1000
Gid:    1000    1000    1000    1000
FDSize: 64
Groups: 4 24 27 30 46 113 128 1000
NStgid: 28797
NSpid:  28797
NSpgid: 28797
NSsid:  17540
VmPeak:   238560 kB
VmSize:   173024 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:      4208 kB
VmRSS:      4208 kB
RssAnon:             256 kB
RssFile:            3952 kB
RssShmem:              0 kB
VmData:    16996 kB
VmStk:       132 kB
VmExe:       320 kB
VmLib:      6244 kB
VmPTE:       104 kB
VmSwap:        0 kB
HugetlbPages:          0 kB
CoreDumping:    0
Threads:        3
SigQ:   0/31574
SigPnd: 0000000000000000
ShdPnd: 0000000000000000
SigBlk: 0000000000000000
SigIgn: 0000000000000000
SigCgt: 0000000180000000
CapInh: 0000000000000000
CapPrm: 0000000000000000
CapEff: 0000000000000000
CapBnd: 0000003fffffffff
CapAmb: 0000000000000000
NoNewPrivs:     0
Seccomp:        0
Speculation_Store_Bypass:       thread vulnerable
Cpus_allowed:   ffffffff,ffffffff,ffffffff,ffffffff
Cpus_allowed_list:      0-127
Mems_allowed:   00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000001
Mems_allowed_list:      0
voluntary_ctxt_switches:        90
nonvoluntary_ctxt_switches:     2

#### 总结
- 看起来不管是server和是client都消耗了三个线程，这个和代码中看到的是一致的，一个dispatch线程，一个timeout线程，一个async线程。
- 132KB的栈，这个也可以解释，因为不管是client还是server其本质上都是client，应用代码不是很多的话栈开销应该是类似的
- 6M的库
