// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from uchassis_msgs:msg/VehicleInfo.idl
// generated code does not contain a copyright notice
#include "uchassis_msgs/msg/detail/vehicle_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `driving_mode`
#include "uchassis_msgs/msg/detail/driving_mode__functions.h"
// Member `gear_location`
#include "uchassis_msgs/msg/detail/gear_position__functions.h"
// Member `parking_state`
#include "uchassis_msgs/msg/detail/parking_state__functions.h"
// Member `signal`
#include "uchassis_msgs/msg/detail/vehicle_signal__functions.h"

bool
uchassis_msgs__msg__VehicleInfo__init(uchassis_msgs__msg__VehicleInfo * msg)
{
  if (!msg) {
    return false;
  }
  // driving_mode
  if (!uchassis_msgs__msg__DrivingMode__init(&msg->driving_mode)) {
    uchassis_msgs__msg__VehicleInfo__fini(msg);
    return false;
  }
  // gear_location
  if (!uchassis_msgs__msg__GearPosition__init(&msg->gear_location)) {
    uchassis_msgs__msg__VehicleInfo__fini(msg);
    return false;
  }
  // motor_spd_radps
  // speed_mps
  // odometer_m
  // throttle_percentage
  // brake_percentage
  // steering_percentage
  // steering_torque_nm
  // parking_state
  if (!uchassis_msgs__msg__ParkingState__init(&msg->parking_state)) {
    uchassis_msgs__msg__VehicleInfo__fini(msg);
    return false;
  }
  // front_crash_status
  // rear_crash_status
  // emgcy_stop_reason
  // signal
  if (!uchassis_msgs__msg__VehicleSignal__init(&msg->signal)) {
    uchassis_msgs__msg__VehicleInfo__fini(msg);
    return false;
  }
  return true;
}

void
uchassis_msgs__msg__VehicleInfo__fini(uchassis_msgs__msg__VehicleInfo * msg)
{
  if (!msg) {
    return;
  }
  // driving_mode
  uchassis_msgs__msg__DrivingMode__fini(&msg->driving_mode);
  // gear_location
  uchassis_msgs__msg__GearPosition__fini(&msg->gear_location);
  // motor_spd_radps
  // speed_mps
  // odometer_m
  // throttle_percentage
  // brake_percentage
  // steering_percentage
  // steering_torque_nm
  // parking_state
  uchassis_msgs__msg__ParkingState__fini(&msg->parking_state);
  // front_crash_status
  // rear_crash_status
  // emgcy_stop_reason
  // signal
  uchassis_msgs__msg__VehicleSignal__fini(&msg->signal);
}

bool
uchassis_msgs__msg__VehicleInfo__are_equal(const uchassis_msgs__msg__VehicleInfo * lhs, const uchassis_msgs__msg__VehicleInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // driving_mode
  if (!uchassis_msgs__msg__DrivingMode__are_equal(
      &(lhs->driving_mode), &(rhs->driving_mode)))
  {
    return false;
  }
  // gear_location
  if (!uchassis_msgs__msg__GearPosition__are_equal(
      &(lhs->gear_location), &(rhs->gear_location)))
  {
    return false;
  }
  // motor_spd_radps
  if (lhs->motor_spd_radps != rhs->motor_spd_radps) {
    return false;
  }
  // speed_mps
  if (lhs->speed_mps != rhs->speed_mps) {
    return false;
  }
  // odometer_m
  if (lhs->odometer_m != rhs->odometer_m) {
    return false;
  }
  // throttle_percentage
  if (lhs->throttle_percentage != rhs->throttle_percentage) {
    return false;
  }
  // brake_percentage
  if (lhs->brake_percentage != rhs->brake_percentage) {
    return false;
  }
  // steering_percentage
  if (lhs->steering_percentage != rhs->steering_percentage) {
    return false;
  }
  // steering_torque_nm
  if (lhs->steering_torque_nm != rhs->steering_torque_nm) {
    return false;
  }
  // parking_state
  if (!uchassis_msgs__msg__ParkingState__are_equal(
      &(lhs->parking_state), &(rhs->parking_state)))
  {
    return false;
  }
  // front_crash_status
  if (lhs->front_crash_status != rhs->front_crash_status) {
    return false;
  }
  // rear_crash_status
  if (lhs->rear_crash_status != rhs->rear_crash_status) {
    return false;
  }
  // emgcy_stop_reason
  if (lhs->emgcy_stop_reason != rhs->emgcy_stop_reason) {
    return false;
  }
  // signal
  if (!uchassis_msgs__msg__VehicleSignal__are_equal(
      &(lhs->signal), &(rhs->signal)))
  {
    return false;
  }
  return true;
}

bool
uchassis_msgs__msg__VehicleInfo__copy(
  const uchassis_msgs__msg__VehicleInfo * input,
  uchassis_msgs__msg__VehicleInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // driving_mode
  if (!uchassis_msgs__msg__DrivingMode__copy(
      &(input->driving_mode), &(output->driving_mode)))
  {
    return false;
  }
  // gear_location
  if (!uchassis_msgs__msg__GearPosition__copy(
      &(input->gear_location), &(output->gear_location)))
  {
    return false;
  }
  // motor_spd_radps
  output->motor_spd_radps = input->motor_spd_radps;
  // speed_mps
  output->speed_mps = input->speed_mps;
  // odometer_m
  output->odometer_m = input->odometer_m;
  // throttle_percentage
  output->throttle_percentage = input->throttle_percentage;
  // brake_percentage
  output->brake_percentage = input->brake_percentage;
  // steering_percentage
  output->steering_percentage = input->steering_percentage;
  // steering_torque_nm
  output->steering_torque_nm = input->steering_torque_nm;
  // parking_state
  if (!uchassis_msgs__msg__ParkingState__copy(
      &(input->parking_state), &(output->parking_state)))
  {
    return false;
  }
  // front_crash_status
  output->front_crash_status = input->front_crash_status;
  // rear_crash_status
  output->rear_crash_status = input->rear_crash_status;
  // emgcy_stop_reason
  output->emgcy_stop_reason = input->emgcy_stop_reason;
  // signal
  if (!uchassis_msgs__msg__VehicleSignal__copy(
      &(input->signal), &(output->signal)))
  {
    return false;
  }
  return true;
}

uchassis_msgs__msg__VehicleInfo *
uchassis_msgs__msg__VehicleInfo__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__VehicleInfo * msg = (uchassis_msgs__msg__VehicleInfo *)allocator.allocate(sizeof(uchassis_msgs__msg__VehicleInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(uchassis_msgs__msg__VehicleInfo));
  bool success = uchassis_msgs__msg__VehicleInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
uchassis_msgs__msg__VehicleInfo__destroy(uchassis_msgs__msg__VehicleInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    uchassis_msgs__msg__VehicleInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
uchassis_msgs__msg__VehicleInfo__Sequence__init(uchassis_msgs__msg__VehicleInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__VehicleInfo * data = NULL;

  if (size) {
    data = (uchassis_msgs__msg__VehicleInfo *)allocator.zero_allocate(size, sizeof(uchassis_msgs__msg__VehicleInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = uchassis_msgs__msg__VehicleInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        uchassis_msgs__msg__VehicleInfo__fini(&data[i - 1]);
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
uchassis_msgs__msg__VehicleInfo__Sequence__fini(uchassis_msgs__msg__VehicleInfo__Sequence * array)
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
      uchassis_msgs__msg__VehicleInfo__fini(&array->data[i]);
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

uchassis_msgs__msg__VehicleInfo__Sequence *
uchassis_msgs__msg__VehicleInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__VehicleInfo__Sequence * array = (uchassis_msgs__msg__VehicleInfo__Sequence *)allocator.allocate(sizeof(uchassis_msgs__msg__VehicleInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = uchassis_msgs__msg__VehicleInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
uchassis_msgs__msg__VehicleInfo__Sequence__destroy(uchassis_msgs__msg__VehicleInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    uchassis_msgs__msg__VehicleInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
uchassis_msgs__msg__VehicleInfo__Sequence__are_equal(const uchassis_msgs__msg__VehicleInfo__Sequence * lhs, const uchassis_msgs__msg__VehicleInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!uchassis_msgs__msg__VehicleInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
uchassis_msgs__msg__VehicleInfo__Sequence__copy(
  const uchassis_msgs__msg__VehicleInfo__Sequence * input,
  uchassis_msgs__msg__VehicleInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(uchassis_msgs__msg__VehicleInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    uchassis_msgs__msg__VehicleInfo * data =
      (uchassis_msgs__msg__VehicleInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!uchassis_msgs__msg__VehicleInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          uchassis_msgs__msg__VehicleInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!uchassis_msgs__msg__VehicleInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
