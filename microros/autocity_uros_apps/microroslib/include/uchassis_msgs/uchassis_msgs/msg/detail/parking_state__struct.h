// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uchassis_msgs:msg/ParkingState.idl
// generated code does not contain a copyright notice

#ifndef UCHASSIS_MSGS__MSG__DETAIL__PARKING_STATE__STRUCT_H_
#define UCHASSIS_MSGS__MSG__DETAIL__PARKING_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'PARK'.
enum
{
  uchassis_msgs__msg__ParkingState__PARK = 1
};

/// Constant 'ELEASE'.
enum
{
  uchassis_msgs__msg__ParkingState__ELEASE = 2
};

/// Constant 'EXECUTING'.
enum
{
  uchassis_msgs__msg__ParkingState__EXECUTING = 3
};

/// Constant 'EMERGENCYPARK'.
enum
{
  uchassis_msgs__msg__ParkingState__EMERGENCYPARK = 4
};

/// Struct defined in msg/ParkingState in the package uchassis_msgs.
/**
  * Parking State  手刹状态
 */
typedef struct uchassis_msgs__msg__ParkingState
{
  uint8_t value;
} uchassis_msgs__msg__ParkingState;

// Struct for a sequence of uchassis_msgs__msg__ParkingState.
typedef struct uchassis_msgs__msg__ParkingState__Sequence
{
  uchassis_msgs__msg__ParkingState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uchassis_msgs__msg__ParkingState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCHASSIS_MSGS__MSG__DETAIL__PARKING_STATE__STRUCT_H_
