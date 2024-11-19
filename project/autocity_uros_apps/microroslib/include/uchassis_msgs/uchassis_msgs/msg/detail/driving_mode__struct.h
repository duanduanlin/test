// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uchassis_msgs:msg/DrivingMode.idl
// generated code does not contain a copyright notice

#ifndef UCHASSIS_MSGS__MSG__DETAIL__DRIVING_MODE__STRUCT_H_
#define UCHASSIS_MSGS__MSG__DETAIL__DRIVING_MODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'STANDBY'.
/**
  * 待机
 */
enum
{
  uchassis_msgs__msg__DrivingMode__STANDBY = 0
};

/// Constant 'AUTO'.
/**
  * 自动驾驶
 */
enum
{
  uchassis_msgs__msg__DrivingMode__AUTO = 1
};

/// Constant 'MANUAL'.
/**
  * 手动驾驶模式
 */
enum
{
  uchassis_msgs__msg__DrivingMode__MANUAL = 2
};

/// Constant 'REMOTE'.
/**
  * 遥控驾驶模式
 */
enum
{
  uchassis_msgs__msg__DrivingMode__REMOTE = 3
};

/// Constant 'INTERRUPTED'.
/**
  * 中断控制模式
 */
enum
{
  uchassis_msgs__msg__DrivingMode__INTERRUPTED = 4
};

/// Constant 'CLOUD'.
/**
  * 远程驾驶模式
 */
enum
{
  uchassis_msgs__msg__DrivingMode__CLOUD = 5
};

/// Constant 'ESTOP'.
/**
  * 紧急停车模式
 */
enum
{
  uchassis_msgs__msg__DrivingMode__ESTOP = 15
};

/// Struct defined in msg/DrivingMode in the package uchassis_msgs.
/**
  * Driving Mode  驾驶模式
 */
typedef struct uchassis_msgs__msg__DrivingMode
{
  uint8_t value;
} uchassis_msgs__msg__DrivingMode;

// Struct for a sequence of uchassis_msgs__msg__DrivingMode.
typedef struct uchassis_msgs__msg__DrivingMode__Sequence
{
  uchassis_msgs__msg__DrivingMode * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uchassis_msgs__msg__DrivingMode__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCHASSIS_MSGS__MSG__DETAIL__DRIVING_MODE__STRUCT_H_
