// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from uchassis_msgs:msg/VehicleInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "uchassis_msgs/msg/detail/vehicle_info__rosidl_typesupport_introspection_c.h"
#include "uchassis_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "uchassis_msgs/msg/detail/vehicle_info__functions.h"
#include "uchassis_msgs/msg/detail/vehicle_info__struct.h"


// Include directives for member types
// Member `driving_mode`
#include "uchassis_msgs/msg/driving_mode.h"
// Member `driving_mode`
#include "uchassis_msgs/msg/detail/driving_mode__rosidl_typesupport_introspection_c.h"
// Member `gear_location`
#include "uchassis_msgs/msg/gear_position.h"
// Member `gear_location`
#include "uchassis_msgs/msg/detail/gear_position__rosidl_typesupport_introspection_c.h"
// Member `parking_state`
#include "uchassis_msgs/msg/parking_state.h"
// Member `parking_state`
#include "uchassis_msgs/msg/detail/parking_state__rosidl_typesupport_introspection_c.h"
// Member `signal`
#include "uchassis_msgs/msg/vehicle_signal.h"
// Member `signal`
#include "uchassis_msgs/msg/detail/vehicle_signal__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  uchassis_msgs__msg__VehicleInfo__init(message_memory);
}

void uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_fini_function(void * message_memory)
{
  uchassis_msgs__msg__VehicleInfo__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_member_array[14] = {
  {
    "driving_mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__VehicleInfo, driving_mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "gear_location",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__VehicleInfo, gear_location),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motor_spd_radps",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__VehicleInfo, motor_spd_radps),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "speed_mps",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__VehicleInfo, speed_mps),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "odometer_m",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__VehicleInfo, odometer_m),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "throttle_percentage",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__VehicleInfo, throttle_percentage),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "brake_percentage",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__VehicleInfo, brake_percentage),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "steering_percentage",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__VehicleInfo, steering_percentage),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "steering_torque_nm",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__VehicleInfo, steering_torque_nm),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "parking_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__VehicleInfo, parking_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "front_crash_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__VehicleInfo, front_crash_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "rear_crash_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__VehicleInfo, rear_crash_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "emgcy_stop_reason",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__VehicleInfo, emgcy_stop_reason),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "signal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uchassis_msgs__msg__VehicleInfo, signal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_members = {
  "uchassis_msgs__msg",  // message namespace
  "VehicleInfo",  // message name
  14,  // number of fields
  sizeof(uchassis_msgs__msg__VehicleInfo),
  uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_member_array,  // message members
  uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_type_support_handle = {
  0,
  &uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_uchassis_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uchassis_msgs, msg, VehicleInfo)() {
  uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uchassis_msgs, msg, DrivingMode)();
  uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uchassis_msgs, msg, GearPosition)();
  uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_member_array[9].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uchassis_msgs, msg, ParkingState)();
  uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_member_array[13].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uchassis_msgs, msg, VehicleSignal)();
  if (!uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_type_support_handle.typesupport_identifier) {
    uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &uchassis_msgs__msg__VehicleInfo__rosidl_typesupport_introspection_c__VehicleInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
