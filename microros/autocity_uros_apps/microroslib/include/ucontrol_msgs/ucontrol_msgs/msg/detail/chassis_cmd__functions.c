// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ucontrol_msgs:msg/ChassisCMD.idl
// generated code does not contain a copyright notice
#include "ucontrol_msgs/msg/detail/chassis_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
ucontrol_msgs__msg__ChassisCMD__init(ucontrol_msgs__msg__ChassisCMD * msg)
{
  if (!msg) {
    return false;
  }
  // drivingmode
  // controlmode
  // drivemode
  // gear_cmd
  // front_angle_rad
  // rear_angle_rad
  // front_angular_speed
  // rear_angular_speed
  // linear_v_mps
  // a_mpss
  // gas_pedal_cmd
  // brake_pedal_cmd
  // clear_crash_cmd
  return true;
}

void
ucontrol_msgs__msg__ChassisCMD__fini(ucontrol_msgs__msg__ChassisCMD * msg)
{
  if (!msg) {
    return;
  }
  // drivingmode
  // controlmode
  // drivemode
  // gear_cmd
  // front_angle_rad
  // rear_angle_rad
  // front_angular_speed
  // rear_angular_speed
  // linear_v_mps
  // a_mpss
  // gas_pedal_cmd
  // brake_pedal_cmd
  // clear_crash_cmd
}

bool
ucontrol_msgs__msg__ChassisCMD__are_equal(const ucontrol_msgs__msg__ChassisCMD * lhs, const ucontrol_msgs__msg__ChassisCMD * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // drivingmode
  if (lhs->drivingmode != rhs->drivingmode) {
    return false;
  }
  // controlmode
  if (lhs->controlmode != rhs->controlmode) {
    return false;
  }
  // drivemode
  if (lhs->drivemode != rhs->drivemode) {
    return false;
  }
  // gear_cmd
  if (lhs->gear_cmd != rhs->gear_cmd) {
    return false;
  }
  // front_angle_rad
  if (lhs->front_angle_rad != rhs->front_angle_rad) {
    return false;
  }
  // rear_angle_rad
  if (lhs->rear_angle_rad != rhs->rear_angle_rad) {
    return false;
  }
  // front_angular_speed
  if (lhs->front_angular_speed != rhs->front_angular_speed) {
    return false;
  }
  // rear_angular_speed
  if (lhs->rear_angular_speed != rhs->rear_angular_speed) {
    return false;
  }
  // linear_v_mps
  if (lhs->linear_v_mps != rhs->linear_v_mps) {
    return false;
  }
  // a_mpss
  if (lhs->a_mpss != rhs->a_mpss) {
    return false;
  }
  // gas_pedal_cmd
  if (lhs->gas_pedal_cmd != rhs->gas_pedal_cmd) {
    return false;
  }
  // brake_pedal_cmd
  if (lhs->brake_pedal_cmd != rhs->brake_pedal_cmd) {
    return false;
  }
  // clear_crash_cmd
  if (lhs->clear_crash_cmd != rhs->clear_crash_cmd) {
    return false;
  }
  return true;
}

bool
ucontrol_msgs__msg__ChassisCMD__copy(
  const ucontrol_msgs__msg__ChassisCMD * input,
  ucontrol_msgs__msg__ChassisCMD * output)
{
  if (!input || !output) {
    return false;
  }
  // drivingmode
  output->drivingmode = input->drivingmode;
  // controlmode
  output->controlmode = input->controlmode;
  // drivemode
  output->drivemode = input->drivemode;
  // gear_cmd
  output->gear_cmd = input->gear_cmd;
  // front_angle_rad
  output->front_angle_rad = input->front_angle_rad;
  // rear_angle_rad
  output->rear_angle_rad = input->rear_angle_rad;
  // front_angular_speed
  output->front_angular_speed = input->front_angular_speed;
  // rear_angular_speed
  output->rear_angular_speed = input->rear_angular_speed;
  // linear_v_mps
  output->linear_v_mps = input->linear_v_mps;
  // a_mpss
  output->a_mpss = input->a_mpss;
  // gas_pedal_cmd
  output->gas_pedal_cmd = input->gas_pedal_cmd;
  // brake_pedal_cmd
  output->brake_pedal_cmd = input->brake_pedal_cmd;
  // clear_crash_cmd
  output->clear_crash_cmd = input->clear_crash_cmd;
  return true;
}

ucontrol_msgs__msg__ChassisCMD *
ucontrol_msgs__msg__ChassisCMD__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__ChassisCMD * msg = (ucontrol_msgs__msg__ChassisCMD *)allocator.allocate(sizeof(ucontrol_msgs__msg__ChassisCMD), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ucontrol_msgs__msg__ChassisCMD));
  bool success = ucontrol_msgs__msg__ChassisCMD__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
ucontrol_msgs__msg__ChassisCMD__destroy(ucontrol_msgs__msg__ChassisCMD * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    ucontrol_msgs__msg__ChassisCMD__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
ucontrol_msgs__msg__ChassisCMD__Sequence__init(ucontrol_msgs__msg__ChassisCMD__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__ChassisCMD * data = NULL;

  if (size) {
    data = (ucontrol_msgs__msg__ChassisCMD *)allocator.zero_allocate(size, sizeof(ucontrol_msgs__msg__ChassisCMD), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ucontrol_msgs__msg__ChassisCMD__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ucontrol_msgs__msg__ChassisCMD__fini(&data[i - 1]);
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
ucontrol_msgs__msg__ChassisCMD__Sequence__fini(ucontrol_msgs__msg__ChassisCMD__Sequence * array)
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
      ucontrol_msgs__msg__ChassisCMD__fini(&array->data[i]);
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

ucontrol_msgs__msg__ChassisCMD__Sequence *
ucontrol_msgs__msg__ChassisCMD__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__ChassisCMD__Sequence * array = (ucontrol_msgs__msg__ChassisCMD__Sequence *)allocator.allocate(sizeof(ucontrol_msgs__msg__ChassisCMD__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = ucontrol_msgs__msg__ChassisCMD__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
ucontrol_msgs__msg__ChassisCMD__Sequence__destroy(ucontrol_msgs__msg__ChassisCMD__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    ucontrol_msgs__msg__ChassisCMD__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
ucontrol_msgs__msg__ChassisCMD__Sequence__are_equal(const ucontrol_msgs__msg__ChassisCMD__Sequence * lhs, const ucontrol_msgs__msg__ChassisCMD__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ucontrol_msgs__msg__ChassisCMD__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ucontrol_msgs__msg__ChassisCMD__Sequence__copy(
  const ucontrol_msgs__msg__ChassisCMD__Sequence * input,
  ucontrol_msgs__msg__ChassisCMD__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ucontrol_msgs__msg__ChassisCMD);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    ucontrol_msgs__msg__ChassisCMD * data =
      (ucontrol_msgs__msg__ChassisCMD *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ucontrol_msgs__msg__ChassisCMD__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          ucontrol_msgs__msg__ChassisCMD__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!ucontrol_msgs__msg__ChassisCMD__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
