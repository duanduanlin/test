// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from udepot_status_msgs:msg/TrashDepotStatus.idl
// generated code does not contain a copyright notice

#ifndef UDEPOT_STATUS_MSGS__MSG__DETAIL__TRASH_DEPOT_STATUS__STRUCT_H_
#define UDEPOT_STATUS_MSGS__MSG__DETAIL__TRASH_DEPOT_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'TRASH_CLOSE'.
/**
  * 垃圾箱关闭
 */
enum
{
  udepot_status_msgs__msg__TrashDepotStatus__TRASH_CLOSE = 0
};

/// Constant 'TRASH_OPENING'.
/**
  * 垃圾箱打开中
 */
enum
{
  udepot_status_msgs__msg__TrashDepotStatus__TRASH_OPENING = 1
};

/// Constant 'TRASH_OPEN'.
/**
  * 垃圾箱打开
 */
enum
{
  udepot_status_msgs__msg__TrashDepotStatus__TRASH_OPEN = 2
};

/// Struct defined in msg/TrashDepotStatus in the package udepot_status_msgs.
/**
  * trash depot status command
  * 控制指令
 */
typedef struct udepot_status_msgs__msg__TrashDepotStatus
{
  /// 网络指示灯
  int8_t network_light_status;
  /// 故障指示灯
  int8_t fault_light_status;
  /// 语音播报状态
  int8_t audio_play_status;
  /// 开盖状态
  int8_t trash_open_status;
  /// 急停按钮
  int8_t estop_button_status;
  /// 开盖按钮
  int8_t trash_open_button_status;
  /// 满溢状态
  int8_t trash_full_status;
  /// 垃圾桶状态
  int8_t trash_status;
} udepot_status_msgs__msg__TrashDepotStatus;

// Struct for a sequence of udepot_status_msgs__msg__TrashDepotStatus.
typedef struct udepot_status_msgs__msg__TrashDepotStatus__Sequence
{
  udepot_status_msgs__msg__TrashDepotStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} udepot_status_msgs__msg__TrashDepotStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UDEPOT_STATUS_MSGS__MSG__DETAIL__TRASH_DEPOT_STATUS__STRUCT_H_
