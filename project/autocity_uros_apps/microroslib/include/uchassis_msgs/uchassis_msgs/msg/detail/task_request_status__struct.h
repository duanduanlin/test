// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uchassis_msgs:msg/TaskRequestStatus.idl
// generated code does not contain a copyright notice

#ifndef UCHASSIS_MSGS__MSG__DETAIL__TASK_REQUEST_STATUS__STRUCT_H_
#define UCHASSIS_MSGS__MSG__DETAIL__TASK_REQUEST_STATUS__STRUCT_H_

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
  uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_UNCOMPLETED = 0
};

/// Constant 'CLEANING_TASK_STATUS_COMPLETED'.
/**
  * 目标清扫部件完成
 */
enum
{
  uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_COMPLETED = 1
};

/// Constant 'CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED'.
/**
  * 前置条件的清扫部件未完成，无法执行
 */
enum
{
  uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_PRECONDITIONUNCOMPLETED = 2
};

/// Constant 'CLEANING_TASK_STATUS_FAULT'.
/**
  * 故障
 */
enum
{
  uchassis_msgs__msg__TaskRequestStatus__CLEANING_TASK_STATUS_FAULT = 3
};

/// Struct defined in msg/TaskRequestStatus in the package uchassis_msgs.
/**
  * TaskRequestStatus Info
 */
typedef struct uchassis_msgs__msg__TaskRequestStatus
{
  /// 清扫状态
  uint8_t sweeping_task_status;
  /// 垃圾箱升举状态
  uint8_t dustbin_lifting_task_status;
  /// 垃圾箱倾倒、清洗状态
  uint8_t dustbin_dumping_cleaning_task_status;
  /// 垃圾桶复位状态
  uint8_t dustbin_reset_task_status;
  /// 充电状态
  uint8_t wireless_charge_task_status;
  /// 左前置边刷目标外展距离
  float left_front_brush_tgt_abd_dist_mm;
  /// 右前置边刷目标外展距离
  float right_front_brush_tgt_abd_dist_mm;
} uchassis_msgs__msg__TaskRequestStatus;

// Struct for a sequence of uchassis_msgs__msg__TaskRequestStatus.
typedef struct uchassis_msgs__msg__TaskRequestStatus__Sequence
{
  uchassis_msgs__msg__TaskRequestStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uchassis_msgs__msg__TaskRequestStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCHASSIS_MSGS__MSG__DETAIL__TASK_REQUEST_STATUS__STRUCT_H_
