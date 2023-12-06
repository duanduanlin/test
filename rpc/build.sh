#!/bin/bash

###
 # @Author: dding3
 # @Date: 2023-09-19 23:37:20
 # @LastEditors: dding3
 # @LastEditTime: 2023-12-05 19:23:12
 # @Description:
 # @FilePath: /test/commonapi/test/rpc/build.sh
###

set -e
pwd=`pwd`

projectPath=$pwd/project
libPath=$pwd/lib
buildPath=$pwd/build

#清空build
if [ -d $buildPath ]
then
rm $buildPath -rf
fi

#编译lib
echo "start build lib"
cd $libPath
libList=`ls`
for i in $libList
do
    if [ -d $i ]
    then
        objPath=$buildPath/obj/$i
        echo $objPath
        mkdir $objPath -p
        cd $objPath

        cmake $libPath/$i
        make -j12
        if [ $? != 0 ]
        then
        exit 0
        fi
        cd -
    fi
done

echo "start build project"
cd $projectPath
proList=`ls`
for i in $proList
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
