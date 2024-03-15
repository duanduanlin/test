#!/bin/bash
###
 # @Author: dding3
 # @Date: 2024-03-11 20:15:27
 # @LastEditors: dding3
 # @LastEditTime: 2024-03-11 20:19:42
 # @Description:
 # @FilePath: /test/test/other/tools/build_tools.sh
###

PWD=$(cd "$(dirname "${SCRIPT}")"; pwd)
# build tools
libs="valgrind"
# libs="capicxx-dbus-runtime"
for lib in ${libs}; do
   echo ${PWD}/$lib/build_$lib.sh
   if [ -e ${PWD}/$lib/build_$lib.sh ];then
       ${PWD}/$lib/build_$lib.sh
   fi
done
