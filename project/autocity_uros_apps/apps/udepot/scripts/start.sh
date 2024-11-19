#!/bin/bash
###
 # @Author: hanson
 # @Date: 2024-07-23 16:14:11
 # @LastEditors: hanson
 # @LastEditTime: 2024-11-14 14:35:48
 # @Description:
 # @FilePath: \autocity_uros_apps\apps\udepot\scripts\start.sh
###

# 重定ros2 log 到/autocity/data/log"
function redirect_log_dir()
{
    if [ -z "$ROS_LOG_DIR" ];then
        ROS_LOG_DIR="/autocity/data/logs"
    fi
    RUN_TIME=$(date '+%Y%m%d_%H%M%S')
    export RUN_TIME=$RUN_TIME

    export ROS_LOG_DIR=$ROS_LOG_DIR/$1/${RUN_TIME}
    echo "ROS_LOG_DIR = $ROS_LOG_DIR"
    mkdir -p ${ROS_LOG_DIR}

    RUN_LOG_FILE=${ROS_LOG_DIR}/run_${RUN_TIME}
    AGENT_LOG_FILE=${ROS_LOG_DIR}/agent_${RUN_TIME}
    echo "RUN_LOG_FILE = $RUN_LOG_FILE"
}
redirect_log_dir "udepot"

UDEPOT_CON_FILE="/autocity/sweeper/install/udepot/config/depot_conf.json"
echo "UDEPOT_CON_FILE:$UDEPOT_CON_FILE"
export UDEPOT_CON_FILE=$UDEPOT_CON_FILE
if [ ! -f ${UDEPOT_CON_FILE} ];then
    echo "file: ${UDEPOT_CON_FILE} not exist,launch failed"
        exit 1
fi

# PRODUCT=$(grep -o '"product":"[^"]*' ${CON_FILE} | grep -o '[^"]*$')
# echo "product: $PRODUCT"
# if [ $PRODUCT == "YK-T" ];then
#     echo "检测到当前车型为: PC"
#     LAUNCH_FILE=launch_pc_rdcu.py
# else
#     echo "未检测到当前车型，请确认文件: ${CON_FILE}"
#     exit 1
# fi

# source /autocity/rdcu/install/setup.bash
# stdbuf -oL -eL ros2 launch canbus ${LAUNCH_FILE} &> ${RUN_LOG_FILE} &

source /autocity/sweeper/install/setup.bash
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 &>${AGENT_LOG_FILE} &

/autocity/sweeper/install/udepot/zephyr.elf &>${RUN_LOG_FILE} &
