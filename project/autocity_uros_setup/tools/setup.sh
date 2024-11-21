#! /bin/bash
###
 # @Author: hanson
 # @Date: 2024-08-08 15:00:10
 # @LastEditors: hanson
 # @LastEditTime: 2024-08-08 19:04:38
 # @Description:
 # @FilePath: /hanson/uros_ws/src/autocity_uros_setup/tools/setup.sh
###

# Source the ROS 2 installation
source /opt/ros/$ROS_DISTRO/setup.bash

# Update dependencies using rosdep
sudo apt update && rosdep update
rosdep install --from-paths src --ignore-src -y

# Install pip
sudo apt-get install python3-pip

#build
colcon build

source install/setup.bash
#create agent
ros2 run autocity_uros_setup create_agent_ws.sh

#build agent
ros2 run autocity_uros_setup build_agent.sh
