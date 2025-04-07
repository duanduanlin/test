// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ucontrol_msgs:msg/ChassisCMD.idl
// generated code does not contain a copyright notice

#ifndef UCONTROL_MSGS__MSG__DETAIL__CHASSIS_CMD__STRUCT_H_
#define UCONTROL_MSGS__MSG__DETAIL__CHASSIS_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'DRIVEMODE_PEDAL'.
enum
{
  ucontrol_msgs__msg__ChassisCMD__DRIVEMODE_PEDAL = 0
};

/// Constant 'DRIVEMODE_SPEED'.
enum
{
  ucontrol_msgs__msg__ChassisCMD__DRIVEMODE_SPEED = 1
};

/// Struct defined in msg/ChassisCMD in the package ucontrol_msgs.
/**
  * Chassis Control Command
 */
typedef struct ucontrol_msgs__msg__ChassisCMD
{
  int8_t drivingmode;
  int8_t controlmode;
  int8_t drivemode;
  int8_t gear_cmd;
  float front_angle_rad;
  float rear_angle_rad;
  float front_angular_speed;
  float rear_angular_speed;
  float linear_v_mps;
  float a_mpss;
  float gas_pedal_cmd;
  float brake_pedal_cmd;
  /// 触边碰撞状态清除
  int8_t clear_crash_cmd;
} ucontrol_msgs__msg__ChassisCMD;

// Struct for a sequence of ucontrol_msgs__msg__ChassisCMD.
typedef struct ucontrol_msgs__msg__ChassisCMD__Sequence
{
  ucontrol_msgs__msg__ChassisCMD * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ucontrol_msgs__msg__ChassisCMD__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCONTROL_MSGS__MSG__DETAIL__CHASSIS_CMD__STRUCT_H_
