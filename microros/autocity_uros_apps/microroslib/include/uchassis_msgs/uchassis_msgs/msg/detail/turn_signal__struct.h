// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uchassis_msgs:msg/TurnSignal.idl
// generated code does not contain a copyright notice

#ifndef UCHASSIS_MSGS__MSG__DETAIL__TURN_SIGNAL__STRUCT_H_
#define UCHASSIS_MSGS__MSG__DETAIL__TURN_SIGNAL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'TURN_NONE'.
enum
{
  uchassis_msgs__msg__TurnSignal__TURN_NONE = 0
};

/// Constant 'TURN_LEFT'.
enum
{
  uchassis_msgs__msg__TurnSignal__TURN_LEFT = 1
};

/// Constant 'TURN_RIGHT'.
enum
{
  uchassis_msgs__msg__TurnSignal__TURN_RIGHT = 2
};

/// Struct defined in msg/TurnSignal in the package uchassis_msgs.
typedef struct uchassis_msgs__msg__TurnSignal
{
  uint8_t value;
} uchassis_msgs__msg__TurnSignal;

// Struct for a sequence of uchassis_msgs__msg__TurnSignal.
typedef struct uchassis_msgs__msg__TurnSignal__Sequence
{
  uchassis_msgs__msg__TurnSignal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uchassis_msgs__msg__TurnSignal__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCHASSIS_MSGS__MSG__DETAIL__TURN_SIGNAL__STRUCT_H_
