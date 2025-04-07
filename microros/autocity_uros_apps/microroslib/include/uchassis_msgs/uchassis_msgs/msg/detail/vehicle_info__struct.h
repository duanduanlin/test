// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uchassis_msgs:msg/VehicleInfo.idl
// generated code does not contain a copyright notice

#ifndef UCHASSIS_MSGS__MSG__DETAIL__VEHICLE_INFO__STRUCT_H_
#define UCHASSIS_MSGS__MSG__DETAIL__VEHICLE_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'driving_mode'
#include "uchassis_msgs/msg/detail/driving_mode__struct.h"
// Member 'gear_location'
#include "uchassis_msgs/msg/detail/gear_position__struct.h"
// Member 'parking_state'
#include "uchassis_msgs/msg/detail/parking_state__struct.h"
// Member 'signal'
#include "uchassis_msgs/msg/detail/vehicle_signal__struct.h"

/// Struct defined in msg/VehicleInfo in the package uchassis_msgs.
/**
  * vehicle info
 */
typedef struct uchassis_msgs__msg__VehicleInfo
{
  /// 驾驶模式
  uchassis_msgs__msg__DrivingMode driving_mode;
  /// 档位
  uchassis_msgs__msg__GearPosition gear_location;
  /// 电机转速
  float motor_spd_radps;
  /// 车辆速度
  float speed_mps;
  /// 车辆里程计
  float odometer_m;
  /// 油门开度  [0, 100]
  float throttle_percentage;
  /// 刹车踏板开度  [0, 100]
  float brake_percentage;
  /// 方向盘转动比例 [-100, 100]
  float steering_percentage;
  /// 方向盘上施加的扭矩
  float steering_torque_nm;
  /// 手刹状态
  uchassis_msgs__msg__ParkingState parking_state;
  /// 前触边碰撞状态
  uint8_t front_crash_status;
  /// 后触边碰撞状态
  uint8_t rear_crash_status;
  /// 急停原因
  uint8_t emgcy_stop_reason;
  /// 车辆车灯信号
  uchassis_msgs__msg__VehicleSignal signal;
} uchassis_msgs__msg__VehicleInfo;

// Struct for a sequence of uchassis_msgs__msg__VehicleInfo.
typedef struct uchassis_msgs__msg__VehicleInfo__Sequence
{
  uchassis_msgs__msg__VehicleInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uchassis_msgs__msg__VehicleInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCHASSIS_MSGS__MSG__DETAIL__VEHICLE_INFO__STRUCT_H_
