#!/bin/bash

###
 # @Author: dding3
 # @Date: 2023-09-19 23:37:20
 # @LastEditors: dding3
 # @LastEditTime: 2023-12-14 18:57:52
 # @Description:
 # @FilePath: /test/commonapi/test/other/build_proj.sh
###

set -e
pwd=`pwd`

buildPath=$pwd/build
projectPath=$pwd/project

projectName=$1
if [ -n $1 ];then
    echo "build project:${projectName}"
else
    echo "no project pass"
    exit 0
fi

if [ -d ${projectPath}/${projectName} ];then
    objPath=$buildPath/obj/${projectName}
    echo $objPath
    if [ -d $objPath ];then
        rm -rf $objPath
    fi
    mkdir $objPath -p
    cd $objPath

    cmake ${projectPath}/${projectName}
    make -j12
    if [ $? != 0 ]
    then
    exit 0
    fi
else
    echo "project ${projectName} not find"
    exit 0
fi
