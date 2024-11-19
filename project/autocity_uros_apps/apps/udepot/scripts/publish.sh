###
# @Author: Aiden
# @Email: aiden@citygo.com.cn
# @Date: 2024-05-06 19:20:07
# Copyright (c) 2024 by Auto City, All Rights Reserved.
###

# Usage: ros2 topic pub <话题> <数据结构> <数据>
# For example: ros2 topic pub /command std_msgs/msg/String "{data: forward}"
source /autocity/sweeper/install/setup.bash
TOPIC_NAME=/udepot/water_depot_cmd
STRUCT=udepot_cmd_msgs/msg/WaterDepotCmd
ros2 topic pub -r 10 ${TOPIC_NAME} ${STRUCT} \
    "{ \
        network_light_cmd: 1,  \
        work_light_cmd: 0,  \
        fault_light_cmd: 0,  \
        flow_reset_cmd: 0,  \
        water_valve_cmd: 0  \
}"
