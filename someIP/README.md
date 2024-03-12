## 编译并安装commonAPi-core
下载地址：https://github.com/COVESA/common-api-runtime
$ cd common-api-runtime
$ mkdir build
$ cd build
$ cmake -D CMAKE_INSTALL_PREFIX=/usr/local ..
$ make
$ sudo make install
## 安装cmake指定版本
sudo wget https://cmake.org/files/v3.13/cmake-3.13.0.tar.gz
sudo ./configure
sudo make -j8
sudo make install
//sudo make uninstall
## 下载并安装boost
wget -O boost_1_83_0.tar.gz https://sourceforge.net/projects/boost/files/boost/1.83.0/boost_1_83_0.tar.gz/download
./bootstrap.sh --prefix=/usr/
./b2
sudo ./b2 install

or
sudo apt-get install libboost-all-dev
//sudo apt -y remove libboost-all-dev
## 安装dl
sudo apt-get install cmake zlib1g-dev libdbus-glib-1-dev build-essential libsystemd-dev -y
https://github.com/COVESA/dlt-daemon
## 编译并安装vsomeIP
下载地址：https://github.com/COVESA/vsomeip
sed -r -i "s#-Werror ##" ../CMakeLists.txt
cmake -D CMAKE_INSTALL_PREFIX=/usr/local -DENABLE_SIGNAL_HANDLING=1 ..
make
sudo make install
## 编译someip-runtime
下载地址：https://github.com/COVESA/capicxx-someip-runtime
cmake -D CMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_PREFIX_PATH=/usr/local -DUSE_INSTALLED_COMMONAPI=OFF ..
cmake
make
make install
## 下载工具
https://github.com/COVESA/capicxx-core-tools
https://github.com/COVESA/capicxx-someip-tools/releases
