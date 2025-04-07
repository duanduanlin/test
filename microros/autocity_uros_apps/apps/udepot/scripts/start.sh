#!/bin/bash
###
 # @Author: hanson
 # @Date: 2024-07-23 16:14:11
 # @LastEditors: hanson
 # @LastEditTime: 2024-12-13 16:59:31
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

    RUN_LOG_FILE=${ROS_LOG_DIR}/$1/run
    echo "RUN_LOG_FILE = $RUN_LOG_FILE"

    export ROS_LOG_DIR=$ROS_LOG_DIR/$1/${RUN_TIME}
    echo "ROS_LOG_DIR = $ROS_LOG_DIR"
    mkdir -p ${ROS_LOG_DIR}

    AGENT_LOG_FILE=${ROS_LOG_DIR}/agent_${RUN_TIME}

}
redirect_log_dir "udepot"
CON_FILE=/autocity/config/config.json
PRODUCT=$(grep -o '"product":"[^"]*' ${CON_FILE} | grep -o '[^"]*$')
echo "product: $PRODUCT"
if [ $PRODUCT == "WD" ];then
    echo "检测到当前产品为: water_depot"
    UDEPOT_CON_FILE="/autocity/sweeper/udepot/config/water_depot_conf.json"
elif [ $PRODUCT == "TD" ];then
    echo "检测到当前产品为: trash_depot"
    UDEPOT_CON_FILE="/autocity/sweeper/udepot/config/trash_depot_conf.json"
else
    echo "未检测到当前产品，请确认文件: ${CON_FILE}"
    exit 1
fi

echo "UDEPOT_CON_FILE:$UDEPOT_CON_FILE"
export UDEPOT_CON_FILE=$UDEPOT_CON_FILE
if [ ! -f ${UDEPOT_CON_FILE} ];then
    echo "file: ${UDEPOT_CON_FILE} not exist,launch failed"
        exit 1
fi

# source /autocity/sweeper/setup.bash
# ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 &>${AGENT_LOG_FILE} &

/autocity/sweeper/udepot/zephyr.elf &>${RUN_LOG_FILE} &
