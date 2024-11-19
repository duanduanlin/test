/*
 * @Author: hanson
 * @Date: 2024-08-23 17:26:10
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-24 17:34:36
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\src\msg_wrap\ChassisMsgWrap.cpp
 */
#include <sstream>
#include "msg_wrap/ChassisMsgWrap.hpp"

ChassisMsgWrap::ChassisMsgWrap(/* args */) : BaseMsgWrap(ChassisMsgType)
{
    Setup();
}

ChassisMsgWrap::~ChassisMsgWrap()
{
}

void ChassisMsgWrap::Setup()
{
    ChassisMsg *chassis_msgs = GetMsg();
    Lock();
    chassis_msgs->ros_header.frame_id.data = _chassis_msg__ros_head__frame_id__data_buffer;
    chassis_msgs->ros_header.frame_id.capacity = ROS_HEAD_BUFFER_LEN;

    chassis_msgs->vehicle_id.vin.data = _chassis_msg__vehicle_id__vin__data_buffer;
    chassis_msgs->vehicle_id.vin.capacity = ROS_VIN_LEN;

    sprintf(chassis_msgs->vehicle_id.vin.data, "%s", ROS_VIN_DEFAULT);
    chassis_msgs->vehicle_id.vin.size = strlen(chassis_msgs->vehicle_id.vin.data);

    // chassis_msgs->vehicle_id.plate.data = _chassis_msg__vehicle_id__plate__data_buffer;
    // chassis_msgs->vehicle_id.plate.capacity = ROS_PLATE_LEN;

    // sprintf(chassis_msgs->vehicle_id.plate.data, "%s", ROS_PLATE_DEFAULT);
    // chassis_msgs->vehicle_id.plate.size = strlen(chassis_msgs->vehicle_id.plate.data);

    // chassis_msgs->vehicle_id.other_unique_id.data = _chassis_msg__vehicle_id__other_unique_id__data_buffer;
    // chassis_msgs->vehicle_id.other_unique_id.capacity = ROS_UUID_LEN;

    // sprintf(chassis_msgs->vehicle_id.other_unique_id.data, "%s", ROS_UUID_DEFAULT);
    // chassis_msgs->vehicle_id.other_unique_id.size = strlen(chassis_msgs->vehicle_id.other_unique_id.data);
    Unlock();

    _device_id = rand();
}

void ChassisMsgWrap::Update()
{
    int seq_no = rand();
    ChassisMsg *chassis_msgs = GetMsg();
    Lock();
    sprintf(chassis_msgs->ros_header.frame_id.data, "%d_%d", seq_no, _device_id);
    chassis_msgs->ros_header.frame_id.size = strlen(chassis_msgs->ros_header.frame_id.data);

    // Fill the message timestamp
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    chassis_msgs->ros_header.stamp.sec = ts.tv_sec;
    chassis_msgs->ros_header.stamp.nanosec = ts.tv_nsec;
    Unlock();
}

void ChassisMsgWrap::Reset()
{
}

std::string ChassisMsgWrap::GetPrintableStr()
{
    std::stringstream ss;
    ChassisMsg *chassis_msgs = GetMsg();
    ss << "m_s_r:" << chassis_msgs->vehicle_info.motor_spd_radps << " ";
    ss << "t_per:" << chassis_msgs->vehicle_info.throttle_percentage << " ";
    ss << "b_per:" << chassis_msgs->vehicle_info.brake_percentage << " ";
    ss << "s_per:" << chassis_msgs->vehicle_info.steering_percentage << " ";
    ss << "s_t_nm:" << chassis_msgs->vehicle_info.steering_torque_nm << " ";
    ss << "p_stat:" << chassis_msgs->vehicle_info.parking_state.value << " ";
    ss << "dr_mod:" << chassis_msgs->vehicle_info.driving_mode.value << " ";
    ss << "e_code:" << chassis_msgs->error_code.value << " ";
    ss << "g_loc:" << chassis_msgs->vehicle_info.gear_location.value << " ";
    ss << "odo_m:" << chassis_msgs->vehicle_info.odometer_m << " ";
    ss << "s_mps:" << chassis_msgs->vehicle_info.speed_mps << " | ";

    ss << "fcs:" << chassis_msgs->vehicle_info.front_crash_status << " ";
    ss << "rcs:" << chassis_msgs->vehicle_info.rear_crash_status << " | ";

    ss << "t_l:" << chassis_msgs->vehicle_info.signal.turn_signal.value << " ";
    ss << "l_l:" << chassis_msgs->vehicle_info.signal.low_beam << " ";
    ss << "f_l:" << chassis_msgs->vehicle_info.signal.fog_light << " ";
    ss << "e_l:" << chassis_msgs->vehicle_info.signal.emergency_light << " ";

    ss << "p_rem:" << chassis_msgs->battery_info.power_remain << " ";
    ss << "ch_stat:" << chassis_msgs->battery_info.charging_status << " | ";
    ss << "quan:" << chassis_msgs->rubbish_info.quantity << " ";
    ss << "b_rem" << chassis_msgs->rubbish_info.box_remain << " ";
    ss << "l_stat:" << chassis_msgs->rubbish_info.lift_status << " ";
    ss << "l_pos:" << chassis_msgs->rubbish_info.lift_position << " ";
    ss << "d_stat:" << chassis_msgs->rubbish_info.dump_status << " ";
    ss << "d_pos:" << chassis_msgs->rubbish_info.dump_position << " ";
    ss << "d_stat:" << chassis_msgs->rubbish_info.door_status << " ";
    ss << "d_pos:" << chassis_msgs->rubbish_info.door_position << " ";
    ss << "d_b_c_sta:" << chassis_msgs->rubbish_info.dustbin_box_clean_status << " | ";

    ss << "err:" << chassis_msgs->error_code.value << " ";

    return ss.str();
}
