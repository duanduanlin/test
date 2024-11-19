#!/bin/bash
###
 # @Author: hanson
 # @Date: 2024-07-23 16:14:11
 # @LastEditors: hanson
 # @LastEditTime: 2024-09-26 16:46:34
 # @Description:
 # @FilePath: \autocity_uros_apps\apps\ucanbus\scripts\start.sh
###

# 重定ros2 log 到/autocity/data/log"
function redirect_log_dir()
{
    if [ -z "$ROS_LOG_DIR" ];then
        ROS_LOG_DIR="/autocity/rdcu/data/logs"
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
redirect_log_dir "ucanbus"

UCANBUS_CON_FILE="/autocity/rdcu/install/ucanbus/config/ecar3_conf.json"
echo "UCANBUS_CON_FILE:$UCANBUS_CON_FILE"
export UCANBUS_CON_FILE=$UCANBUS_CON_FILE
if [ ! -f ${UCANBUS_CON_FILE} ];then
    echo "file: ${UCANBUS_CON_FILE} not exist,launch failed"
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

source /autocity/rdcu/install/setup.bash
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 &>${AGENT_LOG_FILE} &

/autocity/rdcu/install/ucanbus/zephyr.elf
