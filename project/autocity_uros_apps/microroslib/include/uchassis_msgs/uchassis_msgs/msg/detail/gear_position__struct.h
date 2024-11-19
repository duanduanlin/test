// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uchassis_msgs:msg/GearPosition.idl
// generated code does not contain a copyright notice

#ifndef UCHASSIS_MSGS__MSG__DETAIL__GEAR_POSITION__STRUCT_H_
#define UCHASSIS_MSGS__MSG__DETAIL__GEAR_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'GEAR_INVALID'.
/**
  * 无效
 */
enum
{
  uchassis_msgs__msg__GearPosition__GEAR_INVALID = 0
};

/// Constant 'GEAR_PARKING'.
/**
  * 驻车
 */
enum
{
  uchassis_msgs__msg__GearPosition__GEAR_PARKING = 1
};

/// Constant 'GEAR_REVERSE'.
/**
  * 倒挡
 */
enum
{
  uchassis_msgs__msg__GearPosition__GEAR_REVERSE = 2
};

/// Constant 'GEAR_NEUTRAL'.
/**
  * 空挡
 */
enum
{
  uchassis_msgs__msg__GearPosition__GEAR_NEUTRAL = 3
};

/// Constant 'GEAR_DRIVE'.
/**
  * 前进挡
 */
enum
{
  uchassis_msgs__msg__GearPosition__GEAR_DRIVE = 4
};

/// Struct defined in msg/GearPosition in the package uchassis_msgs.
/**
  * Gear Position  档位状态
 */
typedef struct uchassis_msgs__msg__GearPosition
{
  uint8_t value;
} uchassis_msgs__msg__GearPosition;

// Struct for a sequence of uchassis_msgs__msg__GearPosition.
typedef struct uchassis_msgs__msg__GearPosition__Sequence
{
  uchassis_msgs__msg__GearPosition * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uchassis_msgs__msg__GearPosition__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCHASSIS_MSGS__MSG__DETAIL__GEAR_POSITION__STRUCT_H_
