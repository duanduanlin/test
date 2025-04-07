// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ucontrol_msgs:msg/ControlCMD.idl
// generated code does not contain a copyright notice

#ifndef UCONTROL_MSGS__MSG__DETAIL__CONTROL_CMD__STRUCT_H_
#define UCONTROL_MSGS__MSG__DETAIL__CONTROL_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'chassis_cmd'
#include "ucontrol_msgs/msg/detail/chassis_cmd__struct.h"
// Member 'sweeper_cmd'
#include "ucontrol_msgs/msg/detail/sweeper_cmd__struct.h"
// Member 'light_cmd'
#include "ucontrol_msgs/msg/detail/light_cmd__struct.h"
// Member 'audio_cmd'
#include "ucontrol_msgs/msg/detail/audio_cmd__struct.h"

/// Struct defined in msg/ControlCMD in the package ucontrol_msgs.
typedef struct ucontrol_msgs__msg__ControlCMD
{
  std_msgs__msg__Header header;
  ucontrol_msgs__msg__ChassisCMD chassis_cmd;
  ucontrol_msgs__msg__SweeperCMD sweeper_cmd;
  ucontrol_msgs__msg__LightCMD light_cmd;
  ucontrol_msgs__msg__AudioCMD audio_cmd;
} ucontrol_msgs__msg__ControlCMD;

// Struct for a sequence of ucontrol_msgs__msg__ControlCMD.
typedef struct ucontrol_msgs__msg__ControlCMD__Sequence
{
  ucontrol_msgs__msg__ControlCMD * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ucontrol_msgs__msg__ControlCMD__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCONTROL_MSGS__MSG__DETAIL__CONTROL_CMD__STRUCT_H_
