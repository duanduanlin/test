#!/bin/bash

###
 # @Author: dding3
 # @Date: 2023-09-19 23:37:20
 # @LastEditors: dding3
 # @LastEditTime: 2023-12-06 19:32:12
 # @Description:
 # @FilePath: /test/commonapi/test/other/build.sh
###

set -e
pwd=`pwd`

buildPath=$pwd/build

echo "start build obj"
cd $buildPath/obj
objList=`ls`

for i in $objList
do
    if [ -d $i ]
    then
        objPath=$buildPath/obj/$i
        echo $objPath
        cd $objPath

        make -j12
        if [ $? != 0 ]
        then
        exit 0
        fi
        cd -
    fi
done
