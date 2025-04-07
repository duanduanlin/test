// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uchassis_msgs:msg/VehicleID.idl
// generated code does not contain a copyright notice

#ifndef UCHASSIS_MSGS__MSG__DETAIL__VEHICLE_ID__STRUCT_H_
#define UCHASSIS_MSGS__MSG__DETAIL__VEHICLE_ID__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'vin'
// Member 'plate'
// Member 'other_unique_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/VehicleID in the package uchassis_msgs.
/**
  * Vehicle ID
 */
typedef struct uchassis_msgs__msg__VehicleID
{
  /// 车辆识别号码(VIN)
  rosidl_runtime_c__String vin;
  /// 车辆底盘号
  rosidl_runtime_c__String plate;
  /// 其他唯一识别码
  rosidl_runtime_c__String other_unique_id;
} uchassis_msgs__msg__VehicleID;

// Struct for a sequence of uchassis_msgs__msg__VehicleID.
typedef struct uchassis_msgs__msg__VehicleID__Sequence
{
  uchassis_msgs__msg__VehicleID * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uchassis_msgs__msg__VehicleID__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCHASSIS_MSGS__MSG__DETAIL__VEHICLE_ID__STRUCT_H_
