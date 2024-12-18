# XRCE-DDS
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

# FAST-DDS
## 依赖安装
sudo apt install cmake g++ python3-pip wget git
sudo apt install libasio-dev libtinyxml2-dev
sudo apt install libssl-dev
sudo apt install libp11-dev
sudo apt install softhsm2
pip3 install -U colcon-common-extensions vcstool

## 下载并编译fast-dds
mkdir ~/Fast-DDS
cd ~/Fast-DDS
wget https://raw.githubusercontent.com/eProsima/Fast-DDS/master/fastdds.repos
mkdir src
vcs import src < fastdds.repos

colcon build --packages-up-to fastdds

## 安装gen
sudo apt install openjdk-11-jdk
cd src/fastddsgen
./gradlew assemble
