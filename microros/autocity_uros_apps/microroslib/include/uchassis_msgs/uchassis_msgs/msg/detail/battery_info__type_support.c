// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from uchassis_msgs:msg/BatteryInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "uchassis_msgs/msg/detail/battery_info__rosidl_typesupport_introspection_c.h"
#include "uchassis_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "uchassis_msgs/msg/detail/battery_info__functions.h"
#include "uchassis_msgs/msg/detail/battery_info__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void uchassis_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  uchassis_msgs__msg__BatteryInfo__init(message_memory);
}

void uchassis_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_fini_function(void * message_memory)
{
  uchassis_msgs__msg__BatteryInfo__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember uchassis_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_member_array[6] = {
  {
    "range_km",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__BatteryInfo, range_km),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "power_remain",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__BatteryInfo, power_remain),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "battery_temperature",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__BatteryInfo, battery_temperature),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "battery_current",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__BatteryInfo, battery_current),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "battery_voltage",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__BatteryInfo, battery_voltage),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "charging_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__BatteryInfo, charging_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers uchassis_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_members = {
  "uchassis_msgs__msg",  // message namespace
  "BatteryInfo",  // message name
  6,  // number of fields
  sizeof(uchassis_msgs__msg__BatteryInfo),
  uchassis_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_member_array,  // message members
  uchassis_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  uchassis_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t uchassis_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_type_support_handle = {
  0,
  &uchassis_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_uchassis_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uchassis_msgs, msg, BatteryInfo)() {
  if (!uchassis_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_type_support_handle.typesupport_identifier) {
    uchassis_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &uchassis_msgs__msg__BatteryInfo__rosidl_typesupport_introspection_c__BatteryInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
