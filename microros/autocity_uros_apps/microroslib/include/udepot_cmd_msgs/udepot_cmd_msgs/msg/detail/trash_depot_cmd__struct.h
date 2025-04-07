// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from udepot_cmd_msgs:msg/TrashDepotCmd.idl
// generated code does not contain a copyright notice

#ifndef UDEPOT_CMD_MSGS__MSG__DETAIL__TRASH_DEPOT_CMD__STRUCT_H_
#define UDEPOT_CMD_MSGS__MSG__DETAIL__TRASH_DEPOT_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/TrashDepotCmd in the package udepot_cmd_msgs.
/**
  * trash depot control command
  * 控制指令
 */
typedef struct udepot_cmd_msgs__msg__TrashDepotCmd
{
  /// 网络指示灯
  int8_t network_light_cmd;
  /// 故障指示灯
  int8_t fault_light_cmd;
  /// 语音播报
  int8_t audio_play_cmd;
  /// 开盖指令
  int8_t trash_open_cmd;
} udepot_cmd_msgs__msg__TrashDepotCmd;

// Struct for a sequence of udepot_cmd_msgs__msg__TrashDepotCmd.
typedef struct udepot_cmd_msgs__msg__TrashDepotCmd__Sequence
{
  udepot_cmd_msgs__msg__TrashDepotCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} udepot_cmd_msgs__msg__TrashDepotCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UDEPOT_CMD_MSGS__MSG__DETAIL__TRASH_DEPOT_CMD__STRUCT_H_
