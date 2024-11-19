// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uchassis_msgs:msg/RubbishInfo.idl
// generated code does not contain a copyright notice

#ifndef UCHASSIS_MSGS__MSG__DETAIL__RUBBISH_INFO__STRUCT_H_
#define UCHASSIS_MSGS__MSG__DETAIL__RUBBISH_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'CLEANING_TASK_STATUS_UNCOMPLETED'.
/**
  * 目标清扫部件未完成
 */
enum
{
  uchassis_msgs__msg__RubbishInfo__CLEANING_TASK_STATUS_UNCOMPLETED = 0
};

/// Constant 'CLEANING_TASK_STATUS_COMPLETED'.
/**
  * 目标清扫部件完成
 */
enum
{
  uchassis_msgs__msg__RubbishInfo__CLEANING_TASK_STATUS_COMPLETED = 1
};

/// Constant 'CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED'.
/**
  * 前置条件的清扫部件未完成，无法执行
 */
enum
{
  uchassis_msgs__msg__RubbishInfo__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED = 2
};

/// Constant 'CLEANING_TASK_STATUS_FAULT'.
/**
  * 故障
 */
enum
{
  uchassis_msgs__msg__RubbishInfo__CLEANING_TASK_STATUS_FAULT = 3
};

// Include directives for member types
// Member 'task_request_status'
#include "uchassis_msgs/msg/detail/task_request_status__struct.h"

/// Struct defined in msg/RubbishInfo in the package uchassis_msgs.
/**
  * Rubbish Info
 */
typedef struct uchassis_msgs__msg__RubbishInfo
{
  /// 垃圾箱占用量  min_h~max_h
  float quantity;
  /// 垃圾箱剩余量  0~100%
  float box_remain;
  /// 垃圾箱举升状态
  uint8_t lift_status;
  /// 垃圾箱举升位置
  uint8_t lift_position;
  /// 垃圾箱倾倒状态
  uint8_t dump_status;
  /// 垃圾箱倾倒位置
  uint8_t dump_position;
  /// 垃圾箱门状态
  uint8_t door_status;
  /// 垃圾箱门位置
  uint8_t door_position;
  /// 垃圾箱清洗状态
  bool dustbin_box_clean_status;
  /// 垃圾箱复位状态
  uint8_t reset_status;
  uchassis_msgs__msg__TaskRequestStatus task_request_status;
} uchassis_msgs__msg__RubbishInfo;

// Struct for a sequence of uchassis_msgs__msg__RubbishInfo.
typedef struct uchassis_msgs__msg__RubbishInfo__Sequence
{
  uchassis_msgs__msg__RubbishInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uchassis_msgs__msg__RubbishInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCHASSIS_MSGS__MSG__DETAIL__RUBBISH_INFO__STRUCT_H_
