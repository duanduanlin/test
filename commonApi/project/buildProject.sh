#!/bin/bash
###
 # @Author: dding3
 # @Date: 2023-07-27 11:52:15
 # @LastEditors: dding3
 # @LastEditTime: 2023-07-27 13:42:30
 # @Description:
 # @FilePath: \test\dbus\project\buildProject.sh
###
set -e

project_name=$1
pwd=`pwd`
project_path=""
build_path=""

if [ $project_name ];then
    project_path="$pwd/$project_name"
	echo "build project:"$project_path
else
	echo "need a project"
    exit 0
fi

build_path=$project_path"/build"
if [-e $build_path]
then
    rm $build_path -rf
fi

mkdir $build_path -p

cd $build_path
cmake ..
make -j12
