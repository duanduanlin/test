#!/bin/bash

###
 # @Author: dding3
 # @Date: 2023-09-19 23:37:20
 # @LastEditors: dding3
 # @LastEditTime: 2024-03-14 19:02:17
 # @Description:
 # @FilePath: /test/test/commonApi/generateCode.sh
###

set -e
pwd=`pwd`

fidlPath=$pwd/fidl
toolsPath=$pwd/tools

#检查并解压文件生成工具
echo "check and unzip tools"
if [ ! -d $toolsPath/commonapi_core_generator ]
then
    unzip -d $toolsPath/commonapi_core_generator $toolsPath/commonapi_core_generator.zip
fi

if [ ! -d $toolsPath/commonapi_dbus_generator ]
then
    unzip -d $toolsPath/commonapi_dbus_generator $toolsPath/commonapi_dbus_generator.zip
fi

#检查文件是否已生成
echo "check and rm src-gen"
if [ -d $fidlPath/src-gen ]
then
    rm $fidlPath/src-gen -rf
fi

#重新生成文件
echo "gen src by fidl"
cd $fidlPath
fidlList=`find . | grep ".fidl"`
for i in $fidlList
do
    if [ -f $i ]
    then
        echo $i
        $toolsPath/commonapi_core_generator/commonapi-core-generator-linux-x86_64 -sk $i
        $toolsPath/commonapi_dbus_generator/commonapi-dbus-generator-linux-x86_64 $i
    fi
done
