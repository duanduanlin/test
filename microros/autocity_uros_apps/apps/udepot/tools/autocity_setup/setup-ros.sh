#!/bin/bash
###
 # @Author: hanson
 # @Date: 2024-11-27 11:48:58
 # @LastEditors: hanson
 # @LastEditTime: 2024-11-27 15:03:22
 # @Description:
 # @FilePath: \autocity_uros_apps\apps\udepot\tools\autocity_setup\setup-ros.sh
###

echo "1. setup ros humble start"

locale  # check for UTF-8

sudo apt update && sudo apt install locales -y
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8

locale  # verify settings

sudo apt install software-properties-common -y
sudo add-apt-repository universe

sudo apt update && sudo apt install curl -y
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg

echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

sudo apt update

sudo apt upgrade -y

sudo apt reinstall libzstd1=1.4.8+dfsg-3build1 -y

sudo apt install ros-humble-ros-base -y

echo "setup ros humble done"

exit 0
