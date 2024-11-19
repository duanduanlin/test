// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uchassis_msgs:msg/ErrorCode.idl
// generated code does not contain a copyright notice

#ifndef UCHASSIS_MSGS__MSG__DETAIL__ERROR_CODE__STRUCT_H_
#define UCHASSIS_MSGS__MSG__DETAIL__ERROR_CODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'NO_ERROR'.
/**
  * 无效
 */
enum
{
  uchassis_msgs__msg__ErrorCode__NO_ERROR = 0
};

/// Constant 'CMD_NOT_IN_PERIOD'.
/**
  * 控制指令周期错误
 */
enum
{
  uchassis_msgs__msg__ErrorCode__CMD_NOT_IN_PERIOD = 1
};

/// Constant 'CHASSIS_ERROR'.
/**
  * 底盘错误
 */
enum
{
  uchassis_msgs__msg__ErrorCode__CHASSIS_ERROR = 2
};

/// Constant 'CHASSIS_ERROR_ON_STEER'.
/**
  * 底盘报方向盘错误
 */
enum
{
  uchassis_msgs__msg__ErrorCode__CHASSIS_ERROR_ON_STEER = 3
};

/// Constant 'CHASSIS_ERROR_ON_BRAKE'.
/**
  * 底盘报刹车错误
 */
enum
{
  uchassis_msgs__msg__ErrorCode__CHASSIS_ERROR_ON_BRAKE = 4
};

/// Constant 'CHASSIS_ERROR_ON_THROTTLE'.
/**
  * 底盘报油门错误
 */
enum
{
  uchassis_msgs__msg__ErrorCode__CHASSIS_ERROR_ON_THROTTLE = 5
};

/// Constant 'CHASSIS_ERROR_ON_GEAR'.
/**
  * 底盘报档位错误
 */
enum
{
  uchassis_msgs__msg__ErrorCode__CHASSIS_ERROR_ON_GEAR = 6
};

/// Constant 'MANUAL_INTERVENTION'.
/**
  * 人工介入
 */
enum
{
  uchassis_msgs__msg__ErrorCode__MANUAL_INTERVENTION = 7
};

/// Constant 'CHASSIS_CAN_NOT_IN_PERIOD'.
/**
  * 底盘CAN接口周期错误
 */
enum
{
  uchassis_msgs__msg__ErrorCode__CHASSIS_CAN_NOT_IN_PERIOD = 8
};

/// Constant 'UNKNOWN_ERROR'.
/**
  * 未知错误
 */
enum
{
  uchassis_msgs__msg__ErrorCode__UNKNOWN_ERROR = 9
};

/// Struct defined in msg/ErrorCode in the package uchassis_msgs.
/**
  * chassis error code  底盘信息错误码
 */
typedef struct uchassis_msgs__msg__ErrorCode
{
  uint8_t value;
} uchassis_msgs__msg__ErrorCode;

// Struct for a sequence of uchassis_msgs__msg__ErrorCode.
typedef struct uchassis_msgs__msg__ErrorCode__Sequence
{
  uchassis_msgs__msg__ErrorCode * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uchassis_msgs__msg__ErrorCode__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCHASSIS_MSGS__MSG__DETAIL__ERROR_CODE__STRUCT_H_
