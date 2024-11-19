// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ucontrol_msgs:msg/LightCMD.idl
// generated code does not contain a copyright notice

#ifndef UCONTROL_MSGS__MSG__DETAIL__LIGHT_CMD__STRUCT_H_
#define UCONTROL_MSGS__MSG__DETAIL__LIGHT_CMD__STRUCT_H_

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
  ucontrol_msgs__msg__LightCMD__TURN_OFF = 0
};

/// Constant 'TURN_LEFT'.
enum
{
  ucontrol_msgs__msg__LightCMD__TURN_LEFT = 1
};

/// Constant 'TURN_RIGHT'.
enum
{
  ucontrol_msgs__msg__LightCMD__TURN_RIGHT = 2
};

/// Constant 'EMERGENCY_LIGHT'.
enum
{
  ucontrol_msgs__msg__LightCMD__EMERGENCY_LIGHT = 3
};

/// Constant 'AUTO'.
enum
{
  ucontrol_msgs__msg__LightCMD__AUTO = 4
};

/// Struct defined in msg/LightCMD in the package ucontrol_msgs.
/**
  * Light control command
 */
typedef struct ucontrol_msgs__msg__LightCMD
{
  int8_t head_lamp_cmd;
  int8_t fog_lamp_cmd;
  int8_t caution_lamp_cmd;
  int8_t turn_light_cmd;
  int8_t back_light_cmd;
} ucontrol_msgs__msg__LightCMD;

// Struct for a sequence of ucontrol_msgs__msg__LightCMD.
typedef struct ucontrol_msgs__msg__LightCMD__Sequence
{
  ucontrol_msgs__msg__LightCMD * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ucontrol_msgs__msg__LightCMD__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UCONTROL_MSGS__MSG__DETAIL__LIGHT_CMD__STRUCT_H_
