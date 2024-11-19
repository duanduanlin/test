// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uchassis_msgs:msg/VehicleSignal.idl
// generated code does not contain a copyright notice

#ifndef UCHASSIS_MSGS__MSG__DETAIL__VEHICLE_SIGNAL__STRUCT_H_
#define UCHASSIS_MSGS__MSG__DETAIL__VEHICLE_SIGNAL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'turn_signal'
#include "uchassis_msgs/msg/detail/turn_signal__struct.h"

/// Struct defined in msg/VehicleSignal in the package uchassis_msgs.
/**
  * vehicle signal
 */
typedef struct uchassis_msgs__msg__VehicleSignal
{
  /// 左右转信号灯
  uchassis_msgs__msg__TurnSignal turn_signal;
  /// 远光灯
  bool high_beam;
  /// 大灯
  bool low_beam;
  /// 雾灯
  bool fog_light;
  /// 紧急信号灯
  bool emergency_light;
  /// 喇叭
  bool horn;
} uchassis_msgs__msg__VehicleSignal;

// Struct for a sequence of uchassis_msgs__msg__VehicleSignal.
typedef struct uchassis_msgs__msg__VehicleSignal__Sequence
{
  uchassis_msgs__msg__VehicleSignal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uchassis_msgs__msg__VehicleSignal__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCHASSIS_MSGS__MSG__DETAIL__VEHICLE_SIGNAL__STRUCT_H_
