// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ucontrol_msgs:msg/LightCMD.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ucontrol_msgs/msg/detail/light_cmd__rosidl_typesupport_introspection_c.h"
#include "ucontrol_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ucontrol_msgs/msg/detail/light_cmd__functions.h"
#include "ucontrol_msgs/msg/detail/light_cmd__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void ucontrol_msgs__msg__LightCMD__rosidl_typesupport_introspection_c__LightCMD_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ucontrol_msgs__msg__LightCMD__init(message_memory);
}

void ucontrol_msgs__msg__LightCMD__rosidl_typesupport_introspection_c__LightCMD_fini_function(void * message_memory)
{
  ucontrol_msgs__msg__LightCMD__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember ucontrol_msgs__msg__LightCMD__rosidl_typesupport_introspection_c__LightCMD_message_member_array[5] = {
  {
    "head_lamp_cmd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ucontrol_msgs__msg__LightCMD, head_lamp_cmd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "fog_lamp_cmd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ucontrol_msgs__msg__LightCMD, fog_lamp_cmd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "caution_lamp_cmd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ucontrol_msgs__msg__LightCMD, caution_lamp_cmd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "turn_light_cmd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ucontrol_msgs__msg__LightCMD, turn_light_cmd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "back_light_cmd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ucontrol_msgs__msg__LightCMD, back_light_cmd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ucontrol_msgs__msg__LightCMD__rosidl_typesupport_introspection_c__LightCMD_message_members = {
  "ucontrol_msgs__msg",  // message namespace
  "LightCMD",  // message name
  5,  // number of fields
  sizeof(ucontrol_msgs__msg__LightCMD),
  ucontrol_msgs__msg__LightCMD__rosidl_typesupport_introspection_c__LightCMD_message_member_array,  // message members
  ucontrol_msgs__msg__LightCMD__rosidl_typesupport_introspection_c__LightCMD_init_function,  // function to initialize message memory (memory has to be allocated)
  ucontrol_msgs__msg__LightCMD__rosidl_typesupport_introspection_c__LightCMD_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ucontrol_msgs__msg__LightCMD__rosidl_typesupport_introspection_c__LightCMD_message_type_support_handle = {
  0,
  &ucontrol_msgs__msg__LightCMD__rosidl_typesupport_introspection_c__LightCMD_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ucontrol_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ucontrol_msgs, msg, LightCMD)() {
  if (!ucontrol_msgs__msg__LightCMD__rosidl_typesupport_introspection_c__LightCMD_message_type_support_handle.typesupport_identifier) {
    ucontrol_msgs__msg__LightCMD__rosidl_typesupport_introspection_c__LightCMD_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ucontrol_msgs__msg__LightCMD__rosidl_typesupport_introspection_c__LightCMD_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
