#/bin/bash
###
 # @Author: dding3
 # @Date: 2024-10-25 23:55:13
 # @LastEditors: dding3
 # @LastEditTime: 2024-10-27 15:12:24
 # @Description:
 # @FilePath: /work/test/robot/start_agent.sh
###

# docker run -it --rm -e ROS_DOMAIN_ID=20 -v /dev:/dev -v /dev/shm:/dev/shm --privileged --net=host microros/micro-ros-agent:humble udp4 --port 8090 -v4

docker run -it --rm -v /dev:/dev -v /dev/shm:/dev/shm --privileged --net=host microros/micro-ros-agent:humble serial --dev /dev/ttyUSB0 -b 921600 -v4
