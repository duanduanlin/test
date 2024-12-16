## 安装agent
$ git clone https://github.com/eProsima/Micro-XRCE-DDS-Agent.git
$ cd Micro-XRCE-DDS-Agent
$ mkdir build && cd build
$ cmake ..
$ make
$ sudo make install
$ sudo ldconfig /usr/local/lib/

## 安装client
$ git clone https://github.com/eProsima/Micro-XRCE-DDS-Client.git
$ cd Micro-XRCE-DDS-Client
$ mkdir build && cd build
$ cmake .. -DUCLIENT_BUILD_EXAMPLES=ON
$ make

## 安装代码生成工具
$ git clone https://github.com/eProsima/Micro-XRCE-DDS-Gen.git
$ cd Micro-XRCE-DDS-Gen
$ git submodule init
$ git submodule update
$ ./gradlew assemble
