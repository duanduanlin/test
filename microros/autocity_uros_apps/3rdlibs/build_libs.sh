#! /bin/sh
###
 # @Author: hanson
 # @Date: 2024-10-18 14:08:49
 # @LastEditors: hanson
 # @LastEditTime: 2024-10-18 15:09:28
 # @Description:
 # @FilePath: \autocity_uros_apps\3rdlibs\build_libs.sh
###
PWD=`pwd`
echo $PWD
LIBPATH=$PWD
ARCH=`uname -m`
echo $ARCH

tar -zxvf libmodbus-3.1.10.tar.gz

cd libmodbus-3.1.10
mkdir install
sudo ./autogen.sh
sudo ./configure --prefix="$PWD/install" --enable-static

make &&make install

cp install/lib/libmodbus.a $LIBPATH/lib/libmodbus_${ARCH}.a
cp -rf install/include/modbus $LIBPATH/include
