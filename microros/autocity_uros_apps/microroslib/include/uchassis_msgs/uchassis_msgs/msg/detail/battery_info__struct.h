// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uchassis_msgs:msg/BatteryInfo.idl
// generated code does not contain a copyright notice

#ifndef UCHASSIS_MSGS__MSG__DETAIL__BATTERY_INFO__STRUCT_H_
#define UCHASSIS_MSGS__MSG__DETAIL__BATTERY_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'NONE'.
/**
  * 无效
 */
enum
{
  uchassis_msgs__msg__BatteryInfo__NONE = 0
};

/// Constant 'WAITING'.
/**
  * 等待
 */
enum
{
  uchassis_msgs__msg__BatteryInfo__WAITING = 1
};

/// Constant 'CHARGING'.
/**
  * 正在充电
 */
enum
{
  uchassis_msgs__msg__BatteryInfo__CHARGING = 2
};

/// Constant 'COMPLETE'.
/**
  * 充电完成
 */
enum
{
  uchassis_msgs__msg__BatteryInfo__COMPLETE = 3
};

/// Constant 'HOLDING_SUCCEED'.
/**
  * 握手成功
 */
enum
{
  uchassis_msgs__msg__BatteryInfo__HOLDING_SUCCEED = 4
};

/// Constant 'HOLDING_FAIL'.
/**
  * 握手失败
 */
enum
{
  uchassis_msgs__msg__BatteryInfo__HOLDING_FAIL = 5
};

/// Constant 'ERROR'.
/**
  * 设备错误
 */
enum
{
  uchassis_msgs__msg__BatteryInfo__ERROR = 6
};

/// Struct defined in msg/BatteryInfo in the package uchassis_msgs.
/**
  * Battery Info
 */
typedef struct uchassis_msgs__msg__BatteryInfo
{
  /// 电池可以行驶里程  [0, +∞]
  float range_km;
  /// 电池剩余电量      0~100%
  float power_remain;
  /// 电池温度
  float battery_temperature;
  /// 电池电流
  float battery_current;
  /// 电池电压
  float battery_voltage;
  /// 电池充电状态
  uint8_t charging_status;
} uchassis_msgs__msg__BatteryInfo;

// Struct for a sequence of uchassis_msgs__msg__BatteryInfo.
typedef struct uchassis_msgs__msg__BatteryInfo__Sequence
{
  uchassis_msgs__msg__BatteryInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uchassis_msgs__msg__BatteryInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCHASSIS_MSGS__MSG__DETAIL__BATTERY_INFO__STRUCT_H_
