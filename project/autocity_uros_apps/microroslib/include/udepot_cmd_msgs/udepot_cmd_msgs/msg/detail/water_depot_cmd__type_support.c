// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from udepot_cmd_msgs:msg/WaterDepotCmd.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "udepot_cmd_msgs/msg/detail/water_depot_cmd__rosidl_typesupport_introspection_c.h"
#include "udepot_cmd_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "udepot_cmd_msgs/msg/detail/water_depot_cmd__functions.h"
#include "udepot_cmd_msgs/msg/detail/water_depot_cmd__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void udepot_cmd_msgs__msg__WaterDepotCmd__rosidl_typesupport_introspection_c__WaterDepotCmd_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  udepot_cmd_msgs__msg__WaterDepotCmd__init(message_memory);
}

void udepot_cmd_msgs__msg__WaterDepotCmd__rosidl_typesupport_introspection_c__WaterDepotCmd_fini_function(void * message_memory)
{
  udepot_cmd_msgs__msg__WaterDepotCmd__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember udepot_cmd_msgs__msg__WaterDepotCmd__rosidl_typesupport_introspection_c__WaterDepotCmd_message_member_array[5] = {
  {
    "network_light_cmd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(udepot_cmd_msgs__msg__WaterDepotCmd, network_light_cmd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "work_light_cmd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(udepot_cmd_msgs__msg__WaterDepotCmd, work_light_cmd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "fault_light_cmd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(udepot_cmd_msgs__msg__WaterDepotCmd, fault_light_cmd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "flow_reset_cmd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(udepot_cmd_msgs__msg__WaterDepotCmd, flow_reset_cmd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "water_valve_cmd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(udepot_cmd_msgs__msg__WaterDepotCmd, water_valve_cmd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers udepot_cmd_msgs__msg__WaterDepotCmd__rosidl_typesupport_introspection_c__WaterDepotCmd_message_members = {
  "udepot_cmd_msgs__msg",  // message namespace
  "WaterDepotCmd",  // message name
  5,  // number of fields
  sizeof(udepot_cmd_msgs__msg__WaterDepotCmd),
  udepot_cmd_msgs__msg__WaterDepotCmd__rosidl_typesupport_introspection_c__WaterDepotCmd_message_member_array,  // message members
  udepot_cmd_msgs__msg__WaterDepotCmd__rosidl_typesupport_introspection_c__WaterDepotCmd_init_function,  // function to initialize message memory (memory has to be allocated)
  udepot_cmd_msgs__msg__WaterDepotCmd__rosidl_typesupport_introspection_c__WaterDepotCmd_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t udepot_cmd_msgs__msg__WaterDepotCmd__rosidl_typesupport_introspection_c__WaterDepotCmd_message_type_support_handle = {
  0,
  &udepot_cmd_msgs__msg__WaterDepotCmd__rosidl_typesupport_introspection_c__WaterDepotCmd_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_udepot_cmd_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, udepot_cmd_msgs, msg, WaterDepotCmd)() {
  if (!udepot_cmd_msgs__msg__WaterDepotCmd__rosidl_typesupport_introspection_c__WaterDepotCmd_message_type_support_handle.typesupport_identifier) {
    udepot_cmd_msgs__msg__WaterDepotCmd__rosidl_typesupport_introspection_c__WaterDepotCmd_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &udepot_cmd_msgs__msg__WaterDepotCmd__rosidl_typesupport_introspection_c__WaterDepotCmd_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
