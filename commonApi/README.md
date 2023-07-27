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
