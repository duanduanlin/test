// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from uchassis_msgs:msg/Chassis.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "uchassis_msgs/msg/detail/chassis__rosidl_typesupport_introspection_c.h"
#include "uchassis_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "uchassis_msgs/msg/detail/chassis__functions.h"
#include "uchassis_msgs/msg/detail/chassis__struct.h"


// Include directives for member types
// Member `ros_header`
#include "std_msgs/msg/header.h"
// Member `ros_header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `rubbish_info`
#include "uchassis_msgs/msg/rubbish_info.h"
// Member `rubbish_info`
#include "uchassis_msgs/msg/detail/rubbish_info__rosidl_typesupport_introspection_c.h"
// Member `battery_info`
#include "uchassis_msgs/msg/battery_info.h"
// Member `battery_info`
#include "uchassis_msgs/msg/detail/battery_info__rosidl_typesupport_introspection_c.h"
// Member `vehicle_id`
#include "uchassis_msgs/msg/vehicle_id.h"
// Member `vehicle_id`
#include "uchassis_msgs/msg/detail/vehicle_id__rosidl_typesupport_introspection_c.h"
// Member `vehicle_info`
#include "uchassis_msgs/msg/vehicle_info.h"
// Member `vehicle_info`
#include "uchassis_msgs/msg/detail/vehicle_info__rosidl_typesupport_introspection_c.h"
// Member `sweeper_status`
#include "uchassis_msgs/msg/sweeper_status.h"
// Member `sweeper_status`
#include "uchassis_msgs/msg/detail/sweeper_status__rosidl_typesupport_introspection_c.h"
// Member `error_code`
#include "uchassis_msgs/msg/error_code.h"
// Member `error_code`
#include "uchassis_msgs/msg/detail/error_code__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  uchassis_msgs__msg__Chassis__init(message_memory);
}

void uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_fini_function(void * message_memory)
{
  uchassis_msgs__msg__Chassis__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_member_array[7] = {
  {
    "ros_header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__Chassis, ros_header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "rubbish_info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__Chassis, rubbish_info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "battery_info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__Chassis, battery_info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "vehicle_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__Chassis, vehicle_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "vehicle_info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__Chassis, vehicle_info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sweeper_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__Chassis, sweeper_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_code",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__Chassis, error_code),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_members = {
  "uchassis_msgs__msg",  // message namespace
  "Chassis",  // message name
  7,  // number of fields
  sizeof(uchassis_msgs__msg__Chassis),
  uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_member_array,  // message members
  uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_init_function,  // function to initialize message memory (memory has to be allocated)
  uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_type_support_handle = {
  0,
  &uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_uchassis_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uchassis_msgs, msg, Chassis)() {
  uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uchassis_msgs, msg, RubbishInfo)();
  uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uchassis_msgs, msg, BatteryInfo)();
  uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uchassis_msgs, msg, VehicleID)();
  uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uchassis_msgs, msg, VehicleInfo)();
  uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_member_array[5].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uchassis_msgs, msg, SweeperStatus)();
  uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_member_array[6].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uchassis_msgs, msg, ErrorCode)();
  if (!uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_type_support_handle.typesupport_identifier) {
    uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &uchassis_msgs__msg__Chassis__rosidl_typesupport_introspection_c__Chassis_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
