###
# @Author: Aiden
# @Email: aiden@citygo.com.cn
# @Date: 2024-05-06 19:20:07
# Copyright (c) 2024 by Auto City, All Rights Reserved.
###

# Usage: ros2 topic pub <话题> <数据结构> <数据>
# For example: ros2 topic pub /command std_msgs/msg/String "{data: forward}"

TOPIC_NAME=/ucanbus/control_cmd
STRUCT=ucontrol_msgs/msg/ControlCMD
ros2 topic pub -r 10 ${TOPIC_NAME} ${STRUCT} \
    "{ \
    chassis_cmd: \
    { \
        drivingmode: 1, \
        controlmode: 0, \
        drivemode: 1, \
        gear_cmd: 3, \
        front_angle_rad: 0.0, \
        rear_angle_rad: 0.0, \
        front_angular_speed: 0.0, \
        rear_angular_speed: 0.0, \
        linear_v_mps: 0.0, \
        a_mpss: 0.0, \
        gas_pedal_cmd: 0.0, \
        brake_pedal_cmd: 0.0, \
        clear_crash_cmd: 0 \
    }, \
 \
    sweeper_cmd: \
    { \
        sweeping: False, \
        blow_motor_cmd: 0, \
        sweep_brush_cmd: 0, \
        water_pump_cmd: 0, \
        blow_water_pump_cmd: 0, \
        suction_water_pump_cmd: 0, \
        jaw_plate_cmd: 0, \
        left_front_brush_tgt_abd_dist_mm: 0, \
        right_front_brush_tgt_abd_dist_mm: 0, \
        task_request: 0  \
    }, \
 \
    light_cmd: \
    { \
        head_lamp_cmd: 0,  \
        fog_lamp_cmd: 0,  \
        caution_lamp_cmd: 0,  \
        turn_light_cmd: 0,  \
        back_light_cmd: 0,  \
    }, \
    \
    audio_cmd: \
    { \
        audio_cmd: 1,  \
        audio_num: 0,  \
        audio_volume: 100,  \
        audio_mode: 0,  \
        play_cycle_cnt: 0,  \
        play_cycle_duration: 0,  \
        play_cycle_interval: 0,  \
        horn_cmd: 0\
    }\
}"
