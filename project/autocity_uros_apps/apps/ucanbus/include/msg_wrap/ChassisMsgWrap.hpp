/*
 * @Author: hanson
 * @Date: 2024-08-23 10:35:59
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-25 11:07:52
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\ucanbus\include\msg_wrap\ChassisMsgWrap.hpp
 */
#ifndef APPS_UCANBUS_INCLUDE_MSG_WRAP_CHASSISMSGWRAP_HPP_
#define APPS_UCANBUS_INCLUDE_MSG_WRAP_CHASSISMSGWRAP_HPP_

#include <uchassis_msgs/msg/chassis.h>
#include "msg_wrap/BaseMsgWrap.hpp"

#define ChassisMsgType (ROSIDL_GET_MSG_TYPE_SUPPORT(uchassis_msgs, msg, Chassis))

using ChassisMsg = uchassis_msgs__msg__Chassis;
class ChassisMsgWrap : public BaseMsgWrap<ChassisMsg>
{

private:
    /* data */
    char _chassis_msg__ros_head__frame_id__data_buffer[ROS_HEAD_BUFFER_LEN];
    char _chassis_msg__vehicle_id__vin__data_buffer[ROS_VIN_LEN];
    char _chassis_msg__vehicle_id__plate__data_buffer[ROS_PLATE_LEN];
    char _chassis_msg__vehicle_id__other_unique_id__data_buffer[ROS_UUID_LEN];

    int _device_id;

public:
    ChassisMsgWrap(/* args */);
    ~ChassisMsgWrap();

    void Setup() override;
    void Update() override;
    void Reset() override;

    std::string GetPrintableStr() override;
};
#endif // APPS_UCANBUS_INCLUDE_MSG_WRAP_CHASSISMSGWRAP_HPP_
