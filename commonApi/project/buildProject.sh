#!/bin/bash
###
 # @Author: dding3
 # @Date: 2023-07-27 11:52:15
 # @LastEditors: dding3
 # @LastEditTime: 2023-07-27 15:29:06
 # @Description:
 # @FilePath: \test\commonApi\project\buildProject.sh
###
set -e

project_name=$1
pwd=`pwd`
project_path=""
build_path=""
tools_path=""

#检查项目
if [ $project_name ];then
    project_path="$pwd/$project_name"
	echo "build project:"$project_path
else
	echo "need a project"
    exit 0
fi

#检查并解压文件生成工具
tools_path=$project_path"/../../tools"
if [ ! -d $tools_path/commonapi_core_generator ]
then
    unzip -d $tools_path/commonapi_core_generator $tools_path/commonapi_core_generator.zip
fi

if [ ! -d $tools_path/commonapi_dbus_generator ]
then
    unzip -d $tools_path/commonapi_dbus_generator $tools_path/commonapi_dbus_generator.zip
fi

#生成文件
cd $project_path
list=`find fidl | grep .fidl`
for i in $list
do
    if [ -f $i ]
    then
        echo $i
        $tools_path/commonapi_core_generator/commonapi-core-generator-linux-x86_64 -sk $i
        $tools_path/commonapi_dbus_generator/commonapi-dbus-generator-linux-x86_64 $i
    fi
done

#检查并清空build目录
build_path=$project_path"/build"
if [ -e $build_path ]
then
    rm $build_path -rf
fi
mkdir $build_path -p

#编译
cd $build_path
cmake ..
make -j12
