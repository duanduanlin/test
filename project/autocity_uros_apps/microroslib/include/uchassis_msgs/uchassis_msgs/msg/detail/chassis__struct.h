// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uchassis_msgs:msg/Chassis.idl
// generated code does not contain a copyright notice

#ifndef UCHASSIS_MSGS__MSG__DETAIL__CHASSIS__STRUCT_H_
#define UCHASSIS_MSGS__MSG__DETAIL__CHASSIS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'ros_header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'rubbish_info'
#include "uchassis_msgs/msg/detail/rubbish_info__struct.h"
// Member 'battery_info'
#include "uchassis_msgs/msg/detail/battery_info__struct.h"
// Member 'vehicle_id'
#include "uchassis_msgs/msg/detail/vehicle_id__struct.h"
// Member 'vehicle_info'
#include "uchassis_msgs/msg/detail/vehicle_info__struct.h"
// Member 'sweeper_status'
#include "uchassis_msgs/msg/detail/sweeper_status__struct.h"
// Member 'error_code'
#include "uchassis_msgs/msg/detail/error_code__struct.h"

/// Struct defined in msg/Chassis in the package uchassis_msgs.
/**
  * UChassis Info
 */
typedef struct uchassis_msgs__msg__Chassis
{
  /// ROS信息头
  std_msgs__msg__Header ros_header;
  /// 垃圾箱信息
  uchassis_msgs__msg__RubbishInfo rubbish_info;
  /// 电池信息
  uchassis_msgs__msg__BatteryInfo battery_info;
  /// 车辆ID
  uchassis_msgs__msg__VehicleID vehicle_id;
  /// 车辆信息
  uchassis_msgs__msg__VehicleInfo vehicle_info;
  /// 清扫状态
  uchassis_msgs__msg__SweeperStatus sweeper_status;
  /// 底盘错误码
  uchassis_msgs__msg__ErrorCode error_code;
} uchassis_msgs__msg__Chassis;

// Struct for a sequence of uchassis_msgs__msg__Chassis.
typedef struct uchassis_msgs__msg__Chassis__Sequence
{
  uchassis_msgs__msg__Chassis * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uchassis_msgs__msg__Chassis__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCHASSIS_MSGS__MSG__DETAIL__CHASSIS__STRUCT_H_
