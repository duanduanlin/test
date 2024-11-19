// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from uchassis_msgs:msg/Chassis.idl
// generated code does not contain a copyright notice
#include "uchassis_msgs/msg/detail/chassis__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `ros_header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `rubbish_info`
#include "uchassis_msgs/msg/detail/rubbish_info__functions.h"
// Member `battery_info`
#include "uchassis_msgs/msg/detail/battery_info__functions.h"
// Member `vehicle_id`
#include "uchassis_msgs/msg/detail/vehicle_id__functions.h"
// Member `vehicle_info`
#include "uchassis_msgs/msg/detail/vehicle_info__functions.h"
// Member `sweeper_status`
#include "uchassis_msgs/msg/detail/sweeper_status__functions.h"
// Member `error_code`
#include "uchassis_msgs/msg/detail/error_code__functions.h"

bool
uchassis_msgs__msg__Chassis__init(uchassis_msgs__msg__Chassis * msg)
{
  if (!msg) {
    return false;
  }
  // ros_header
  if (!std_msgs__msg__Header__init(&msg->ros_header)) {
    uchassis_msgs__msg__Chassis__fini(msg);
    return false;
  }
  // rubbish_info
  if (!uchassis_msgs__msg__RubbishInfo__init(&msg->rubbish_info)) {
    uchassis_msgs__msg__Chassis__fini(msg);
    return false;
  }
  // battery_info
  if (!uchassis_msgs__msg__BatteryInfo__init(&msg->battery_info)) {
    uchassis_msgs__msg__Chassis__fini(msg);
    return false;
  }
  // vehicle_id
  if (!uchassis_msgs__msg__VehicleID__init(&msg->vehicle_id)) {
    uchassis_msgs__msg__Chassis__fini(msg);
    return false;
  }
  // vehicle_info
  if (!uchassis_msgs__msg__VehicleInfo__init(&msg->vehicle_info)) {
    uchassis_msgs__msg__Chassis__fini(msg);
    return false;
  }
  // sweeper_status
  if (!uchassis_msgs__msg__SweeperStatus__init(&msg->sweeper_status)) {
    uchassis_msgs__msg__Chassis__fini(msg);
    return false;
  }
  // error_code
  if (!uchassis_msgs__msg__ErrorCode__init(&msg->error_code)) {
    uchassis_msgs__msg__Chassis__fini(msg);
    return false;
  }
  return true;
}

void
uchassis_msgs__msg__Chassis__fini(uchassis_msgs__msg__Chassis * msg)
{
  if (!msg) {
    return;
  }
  // ros_header
  std_msgs__msg__Header__fini(&msg->ros_header);
  // rubbish_info
  uchassis_msgs__msg__RubbishInfo__fini(&msg->rubbish_info);
  // battery_info
  uchassis_msgs__msg__BatteryInfo__fini(&msg->battery_info);
  // vehicle_id
  uchassis_msgs__msg__VehicleID__fini(&msg->vehicle_id);
  // vehicle_info
  uchassis_msgs__msg__VehicleInfo__fini(&msg->vehicle_info);
  // sweeper_status
  uchassis_msgs__msg__SweeperStatus__fini(&msg->sweeper_status);
  // error_code
  uchassis_msgs__msg__ErrorCode__fini(&msg->error_code);
}

bool
uchassis_msgs__msg__Chassis__are_equal(const uchassis_msgs__msg__Chassis * lhs, const uchassis_msgs__msg__Chassis * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // ros_header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->ros_header), &(rhs->ros_header)))
  {
    return false;
  }
  // rubbish_info
  if (!uchassis_msgs__msg__RubbishInfo__are_equal(
      &(lhs->rubbish_info), &(rhs->rubbish_info)))
  {
    return false;
  }
  // battery_info
  if (!uchassis_msgs__msg__BatteryInfo__are_equal(
      &(lhs->battery_info), &(rhs->battery_info)))
  {
    return false;
  }
  // vehicle_id
  if (!uchassis_msgs__msg__VehicleID__are_equal(
      &(lhs->vehicle_id), &(rhs->vehicle_id)))
  {
    return false;
  }
  // vehicle_info
  if (!uchassis_msgs__msg__VehicleInfo__are_equal(
      &(lhs->vehicle_info), &(rhs->vehicle_info)))
  {
    return false;
  }
  // sweeper_status
  if (!uchassis_msgs__msg__SweeperStatus__are_equal(
      &(lhs->sweeper_status), &(rhs->sweeper_status)))
  {
    return false;
  }
  // error_code
  if (!uchassis_msgs__msg__ErrorCode__are_equal(
      &(lhs->error_code), &(rhs->error_code)))
  {
    return false;
  }
  return true;
}

bool
uchassis_msgs__msg__Chassis__copy(
  const uchassis_msgs__msg__Chassis * input,
  uchassis_msgs__msg__Chassis * output)
{
  if (!input || !output) {
    return false;
  }
  // ros_header
  if (!std_msgs__msg__Header__copy(
      &(input->ros_header), &(output->ros_header)))
  {
    return false;
  }
  // rubbish_info
  if (!uchassis_msgs__msg__RubbishInfo__copy(
      &(input->rubbish_info), &(output->rubbish_info)))
  {
    return false;
  }
  // battery_info
  if (!uchassis_msgs__msg__BatteryInfo__copy(
      &(input->battery_info), &(output->battery_info)))
  {
    return false;
  }
  // vehicle_id
  if (!uchassis_msgs__msg__VehicleID__copy(
      &(input->vehicle_id), &(output->vehicle_id)))
  {
    return false;
  }
  // vehicle_info
  if (!uchassis_msgs__msg__VehicleInfo__copy(
      &(input->vehicle_info), &(output->vehicle_info)))
  {
    return false;
  }
  // sweeper_status
  if (!uchassis_msgs__msg__SweeperStatus__copy(
      &(input->sweeper_status), &(output->sweeper_status)))
  {
    return false;
  }
  // error_code
  if (!uchassis_msgs__msg__ErrorCode__copy(
      &(input->error_code), &(output->error_code)))
  {
    return false;
  }
  return true;
}

uchassis_msgs__msg__Chassis *
uchassis_msgs__msg__Chassis__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__Chassis * msg = (uchassis_msgs__msg__Chassis *)allocator.allocate(sizeof(uchassis_msgs__msg__Chassis), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(uchassis_msgs__msg__Chassis));
  bool success = uchassis_msgs__msg__Chassis__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
uchassis_msgs__msg__Chassis__destroy(uchassis_msgs__msg__Chassis * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    uchassis_msgs__msg__Chassis__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
uchassis_msgs__msg__Chassis__Sequence__init(uchassis_msgs__msg__Chassis__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__Chassis * data = NULL;

  if (size) {
    data = (uchassis_msgs__msg__Chassis *)allocator.zero_allocate(size, sizeof(uchassis_msgs__msg__Chassis), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = uchassis_msgs__msg__Chassis__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        uchassis_msgs__msg__Chassis__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
uchassis_msgs__msg__Chassis__Sequence__fini(uchassis_msgs__msg__Chassis__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      uchassis_msgs__msg__Chassis__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

uchassis_msgs__msg__Chassis__Sequence *
uchassis_msgs__msg__Chassis__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__Chassis__Sequence * array = (uchassis_msgs__msg__Chassis__Sequence *)allocator.allocate(sizeof(uchassis_msgs__msg__Chassis__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = uchassis_msgs__msg__Chassis__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
uchassis_msgs__msg__Chassis__Sequence__destroy(uchassis_msgs__msg__Chassis__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    uchassis_msgs__msg__Chassis__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
uchassis_msgs__msg__Chassis__Sequence__are_equal(const uchassis_msgs__msg__Chassis__Sequence * lhs, const uchassis_msgs__msg__Chassis__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!uchassis_msgs__msg__Chassis__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
uchassis_msgs__msg__Chassis__Sequence__copy(
  const uchassis_msgs__msg__Chassis__Sequence * input,
  uchassis_msgs__msg__Chassis__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(uchassis_msgs__msg__Chassis);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    uchassis_msgs__msg__Chassis * data =
      (uchassis_msgs__msg__Chassis *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!uchassis_msgs__msg__Chassis__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          uchassis_msgs__msg__Chassis__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!uchassis_msgs__msg__Chassis__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
