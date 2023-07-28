#!/bin/bash
###
 # @Author: dding3
 # @Date: 2023-07-27 17:22:53
 # @LastEditors: dding3
 # @LastEditTime: 2023-07-28 10:33:12
 # @Description:
 # @FilePath: \test\commonApi\build.sh
###
set -e

pwd=`pwd`

fidlPath=$pwd/fidl
projectPath=$pwd/project
toolsPath=$pwd/tools
buildPath=$pwd/build

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

#清空build
if [ -d $buildPath ]
then
rm $buildPath -rf
fi

#编译工程
echo "start build project"
cd $projectPath
projectList=`ls`
for i in $projectList
do
    if [ -d $i ]
    then
        objPath=$buildPath/obj/$i
        echo $objPath
        mkdir $objPath -p
        cd $objPath

        cmake $projectPath/$i
        make -j12
        if [ $? != 0 ]
        then
        exit 0
        fi
        cd -
    fi
done
