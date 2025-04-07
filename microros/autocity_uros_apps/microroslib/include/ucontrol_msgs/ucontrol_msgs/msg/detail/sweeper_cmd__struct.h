// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ucontrol_msgs:msg/SweeperCMD.idl
// generated code does not contain a copyright notice

#ifndef UCONTROL_MSGS__MSG__DETAIL__SWEEPER_CMD__STRUCT_H_
#define UCONTROL_MSGS__MSG__DETAIL__SWEEPER_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'TURN_OFF'.
enum
{
  ucontrol_msgs__msg__SweeperCMD__TURN_OFF = 0
};

/// Constant 'TURN_ON'.
enum
{
  ucontrol_msgs__msg__SweeperCMD__TURN_ON = 1
};

/// Constant 'EXIT_CONTROL'.
enum
{
  ucontrol_msgs__msg__SweeperCMD__EXIT_CONTROL = 2
};

/// Constant 'LOW_SPEED'.
enum
{
  ucontrol_msgs__msg__SweeperCMD__LOW_SPEED = 3
};

/// Constant 'MEDIUM_SPEED'.
enum
{
  ucontrol_msgs__msg__SweeperCMD__MEDIUM_SPEED = 4
};

/// Constant 'HIGH_SPEED'.
enum
{
  ucontrol_msgs__msg__SweeperCMD__HIGH_SPEED = 5
};

/// Constant 'NONE'.
/**
  * 无任务需求
 */
enum
{
  ucontrol_msgs__msg__SweeperCMD__NONE = 0
};

/// Constant 'DUSTBIN_LIFTING_TASK'.
/**
  * 垃圾箱升举到最高位置（dustbin_docking）
 */
enum
{
  ucontrol_msgs__msg__SweeperCMD__DUSTBIN_LIFTING_TASK = 1
};

/// Constant 'DUSTBIN_DUMPING_CLEANING_TASK'.
/**
  * 垃圾箱倾倒到最大位置，垃圾箱打开，清洗（dustbin_docking）
 */
enum
{
  ucontrol_msgs__msg__SweeperCMD__DUSTBIN_DUMPING_CLEANING_TASK = 2
};

/// Constant 'DUSTBIN_RESET_TASK'.
/**
  * 垃圾桶复位，垃圾箱关闭（dustbin_docking）
 */
enum
{
  ucontrol_msgs__msg__SweeperCMD__DUSTBIN_RESET_TASK = 3
};

/// Constant 'WIRELESS_CHARGE_TASK'.
enum
{
  ucontrol_msgs__msg__SweeperCMD__WIRELESS_CHARGE_TASK = 4
};

/// Constant 'ADD_WATER_TASK'.
enum
{
  ucontrol_msgs__msg__SweeperCMD__ADD_WATER_TASK = 5
};

/// Constant 'ADD_WATER_CHARGE_TASK'.
enum
{
  ucontrol_msgs__msg__SweeperCMD__ADD_WATER_CHARGE_TASK = 6
};

/// Struct defined in msg/SweeperCMD in the package ucontrol_msgs.
/**
  * Sweeper Control Command
 */
typedef struct ucontrol_msgs__msg__SweeperCMD
{
  bool sweeping;
  int8_t blow_motor_cmd;
  int8_t sweep_brush_cmd;
  int8_t water_pump_cmd;
  int8_t blow_water_pump_cmd;
  int8_t suction_water_pump_cmd;
  int8_t jaw_plate_cmd;
  int8_t left_front_brush_tgt_abd_dist_mm;
  int8_t right_front_brush_tgt_abd_dist_mm;
  int8_t task_request;
} ucontrol_msgs__msg__SweeperCMD;

// Struct for a sequence of ucontrol_msgs__msg__SweeperCMD.
typedef struct ucontrol_msgs__msg__SweeperCMD__Sequence
{
  ucontrol_msgs__msg__SweeperCMD * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ucontrol_msgs__msg__SweeperCMD__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCONTROL_MSGS__MSG__DETAIL__SWEEPER_CMD__STRUCT_H_
