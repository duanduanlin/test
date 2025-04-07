// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uchassis_msgs:msg/SweeperStatus.idl
// generated code does not contain a copyright notice

#ifndef UCHASSIS_MSGS__MSG__DETAIL__SWEEPER_STATUS__STRUCT_H_
#define UCHASSIS_MSGS__MSG__DETAIL__SWEEPER_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/SweeperStatus in the package uchassis_msgs.
/**
  * sweeping status
 */
typedef struct uchassis_msgs__msg__SweeperStatus
{
  /// 清扫状态
  bool sweeping;
  /// 剩余水量 0~100
  uint8_t remain_water;
} uchassis_msgs__msg__SweeperStatus;

// Struct for a sequence of uchassis_msgs__msg__SweeperStatus.
typedef struct uchassis_msgs__msg__SweeperStatus__Sequence
{
  uchassis_msgs__msg__SweeperStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uchassis_msgs__msg__SweeperStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCHASSIS_MSGS__MSG__DETAIL__SWEEPER_STATUS__STRUCT_H_
