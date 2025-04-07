#!/bin/bash
###
 # @Author: hanson
 # @Date: 2024-11-27 11:48:58
 # @LastEditors: hanson
 # @LastEditTime: 2024-11-28 09:59:41
 # @Description:
 # @FilePath: \autocity_uros_apps\apps\udepot\tools\autocity_setup\setup-env.sh
###

echo "2. setup env start"

sudo apt install libmodbus-dev -y
sudo apt-get install python3-pip -y
sudo pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple debugpy loguru paho.mqtt

echo "setup env done"
