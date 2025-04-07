// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from udepot_status_msgs:msg/WaterDepotStatus.idl
// generated code does not contain a copyright notice

#ifndef UDEPOT_STATUS_MSGS__MSG__DETAIL__WATER_DEPOT_STATUS__STRUCT_H_
#define UDEPOT_STATUS_MSGS__MSG__DETAIL__WATER_DEPOT_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/WaterDepotStatus in the package udepot_status_msgs.
/**
  * water depot status command
  * 控制指令
 */
typedef struct udepot_status_msgs__msg__WaterDepotStatus
{
  /// 网络指示灯
  int8_t network_light_status;
  /// 加水作业指示灯
  int8_t work_light_status;
  /// 故障指示灯
  int8_t fault_light_status;
  /// 瞬时流量
  float instantaneous_flow;
  /// 总流量
  float total_flow;
  /// 水阀开关
  int8_t water_valve_status;
  /// 急停按钮
  int8_t estop_button_status;
  /// 加水按钮
  int8_t water_button_status;
} udepot_status_msgs__msg__WaterDepotStatus;

// Struct for a sequence of udepot_status_msgs__msg__WaterDepotStatus.
typedef struct udepot_status_msgs__msg__WaterDepotStatus__Sequence
{
  udepot_status_msgs__msg__WaterDepotStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} udepot_status_msgs__msg__WaterDepotStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UDEPOT_STATUS_MSGS__MSG__DETAIL__WATER_DEPOT_STATUS__STRUCT_H_
