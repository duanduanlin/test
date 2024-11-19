#!/bin/bash
###
 # @Author: hanson
 # @Date: 2024-07-23 16:14:11
 # @LastEditors: hanson
 # @LastEditTime: 2024-09-05 11:09:21
 # @Description:
 # @FilePath: \ucanbus\scripts\stop.sh
###
pkill -9 start
pkill -9 zephyr
pkill -9 micro_ros_agent
pkill -9 ros2
