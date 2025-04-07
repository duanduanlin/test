// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from udepot_status_msgs:msg/TrashDepotStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "udepot_status_msgs/msg/detail/trash_depot_status__rosidl_typesupport_introspection_c.h"
#include "udepot_status_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "udepot_status_msgs/msg/detail/trash_depot_status__functions.h"
#include "udepot_status_msgs/msg/detail/trash_depot_status__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void udepot_status_msgs__msg__TrashDepotStatus__rosidl_typesupport_introspection_c__TrashDepotStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  udepot_status_msgs__msg__TrashDepotStatus__init(message_memory);
}

void udepot_status_msgs__msg__TrashDepotStatus__rosidl_typesupport_introspection_c__TrashDepotStatus_fini_function(void * message_memory)
{
  udepot_status_msgs__msg__TrashDepotStatus__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember udepot_status_msgs__msg__TrashDepotStatus__rosidl_typesupport_introspection_c__TrashDepotStatus_message_member_array[8] = {
  {
    "network_light_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(udepot_status_msgs__msg__TrashDepotStatus, network_light_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "fault_light_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(udepot_status_msgs__msg__TrashDepotStatus, fault_light_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "audio_play_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(udepot_status_msgs__msg__TrashDepotStatus, audio_play_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "trash_open_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(udepot_status_msgs__msg__TrashDepotStatus, trash_open_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "estop_button_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(udepot_status_msgs__msg__TrashDepotStatus, estop_button_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "trash_open_button_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(udepot_status_msgs__msg__TrashDepotStatus, trash_open_button_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "trash_full_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(udepot_status_msgs__msg__TrashDepotStatus, trash_full_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "trash_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(udepot_status_msgs__msg__TrashDepotStatus, trash_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers udepot_status_msgs__msg__TrashDepotStatus__rosidl_typesupport_introspection_c__TrashDepotStatus_message_members = {
  "udepot_status_msgs__msg",  // message namespace
  "TrashDepotStatus",  // message name
  8,  // number of fields
  sizeof(udepot_status_msgs__msg__TrashDepotStatus),
  udepot_status_msgs__msg__TrashDepotStatus__rosidl_typesupport_introspection_c__TrashDepotStatus_message_member_array,  // message members
  udepot_status_msgs__msg__TrashDepotStatus__rosidl_typesupport_introspection_c__TrashDepotStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  udepot_status_msgs__msg__TrashDepotStatus__rosidl_typesupport_introspection_c__TrashDepotStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t udepot_status_msgs__msg__TrashDepotStatus__rosidl_typesupport_introspection_c__TrashDepotStatus_message_type_support_handle = {
  0,
  &udepot_status_msgs__msg__TrashDepotStatus__rosidl_typesupport_introspection_c__TrashDepotStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_udepot_status_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, udepot_status_msgs, msg, TrashDepotStatus)() {
  if (!udepot_status_msgs__msg__TrashDepotStatus__rosidl_typesupport_introspection_c__TrashDepotStatus_message_type_support_handle.typesupport_identifier) {
    udepot_status_msgs__msg__TrashDepotStatus__rosidl_typesupport_introspection_c__TrashDepotStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &udepot_status_msgs__msg__TrashDepotStatus__rosidl_typesupport_introspection_c__TrashDepotStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
