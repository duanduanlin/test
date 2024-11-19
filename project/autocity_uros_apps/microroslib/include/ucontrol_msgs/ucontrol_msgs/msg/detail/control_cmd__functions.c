// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ucontrol_msgs:msg/ControlCMD.idl
// generated code does not contain a copyright notice
#include "ucontrol_msgs/msg/detail/control_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `chassis_cmd`
#include "ucontrol_msgs/msg/detail/chassis_cmd__functions.h"
// Member `sweeper_cmd`
#include "ucontrol_msgs/msg/detail/sweeper_cmd__functions.h"
// Member `light_cmd`
#include "ucontrol_msgs/msg/detail/light_cmd__functions.h"
// Member `audio_cmd`
#include "ucontrol_msgs/msg/detail/audio_cmd__functions.h"

bool
ucontrol_msgs__msg__ControlCMD__init(ucontrol_msgs__msg__ControlCMD * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    ucontrol_msgs__msg__ControlCMD__fini(msg);
    return false;
  }
  // chassis_cmd
  if (!ucontrol_msgs__msg__ChassisCMD__init(&msg->chassis_cmd)) {
    ucontrol_msgs__msg__ControlCMD__fini(msg);
    return false;
  }
  // sweeper_cmd
  if (!ucontrol_msgs__msg__SweeperCMD__init(&msg->sweeper_cmd)) {
    ucontrol_msgs__msg__ControlCMD__fini(msg);
    return false;
  }
  // light_cmd
  if (!ucontrol_msgs__msg__LightCMD__init(&msg->light_cmd)) {
    ucontrol_msgs__msg__ControlCMD__fini(msg);
    return false;
  }
  // audio_cmd
  if (!ucontrol_msgs__msg__AudioCMD__init(&msg->audio_cmd)) {
    ucontrol_msgs__msg__ControlCMD__fini(msg);
    return false;
  }
  return true;
}

void
ucontrol_msgs__msg__ControlCMD__fini(ucontrol_msgs__msg__ControlCMD * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // chassis_cmd
  ucontrol_msgs__msg__ChassisCMD__fini(&msg->chassis_cmd);
  // sweeper_cmd
  ucontrol_msgs__msg__SweeperCMD__fini(&msg->sweeper_cmd);
  // light_cmd
  ucontrol_msgs__msg__LightCMD__fini(&msg->light_cmd);
  // audio_cmd
  ucontrol_msgs__msg__AudioCMD__fini(&msg->audio_cmd);
}

bool
ucontrol_msgs__msg__ControlCMD__are_equal(const ucontrol_msgs__msg__ControlCMD * lhs, const ucontrol_msgs__msg__ControlCMD * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // chassis_cmd
  if (!ucontrol_msgs__msg__ChassisCMD__are_equal(
      &(lhs->chassis_cmd), &(rhs->chassis_cmd)))
  {
    return false;
  }
  // sweeper_cmd
  if (!ucontrol_msgs__msg__SweeperCMD__are_equal(
      &(lhs->sweeper_cmd), &(rhs->sweeper_cmd)))
  {
    return false;
  }
  // light_cmd
  if (!ucontrol_msgs__msg__LightCMD__are_equal(
      &(lhs->light_cmd), &(rhs->light_cmd)))
  {
    return false;
  }
  // audio_cmd
  if (!ucontrol_msgs__msg__AudioCMD__are_equal(
      &(lhs->audio_cmd), &(rhs->audio_cmd)))
  {
    return false;
  }
  return true;
}

bool
ucontrol_msgs__msg__ControlCMD__copy(
  const ucontrol_msgs__msg__ControlCMD * input,
  ucontrol_msgs__msg__ControlCMD * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // chassis_cmd
  if (!ucontrol_msgs__msg__ChassisCMD__copy(
      &(input->chassis_cmd), &(output->chassis_cmd)))
  {
    return false;
  }
  // sweeper_cmd
  if (!ucontrol_msgs__msg__SweeperCMD__copy(
      &(input->sweeper_cmd), &(output->sweeper_cmd)))
  {
    return false;
  }
  // light_cmd
  if (!ucontrol_msgs__msg__LightCMD__copy(
      &(input->light_cmd), &(output->light_cmd)))
  {
    return false;
  }
  // audio_cmd
  if (!ucontrol_msgs__msg__AudioCMD__copy(
      &(input->audio_cmd), &(output->audio_cmd)))
  {
    return false;
  }
  return true;
}

ucontrol_msgs__msg__ControlCMD *
ucontrol_msgs__msg__ControlCMD__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__ControlCMD * msg = (ucontrol_msgs__msg__ControlCMD *)allocator.allocate(sizeof(ucontrol_msgs__msg__ControlCMD), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ucontrol_msgs__msg__ControlCMD));
  bool success = ucontrol_msgs__msg__ControlCMD__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
ucontrol_msgs__msg__ControlCMD__destroy(ucontrol_msgs__msg__ControlCMD * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    ucontrol_msgs__msg__ControlCMD__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
ucontrol_msgs__msg__ControlCMD__Sequence__init(ucontrol_msgs__msg__ControlCMD__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__ControlCMD * data = NULL;

  if (size) {
    data = (ucontrol_msgs__msg__ControlCMD *)allocator.zero_allocate(size, sizeof(ucontrol_msgs__msg__ControlCMD), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ucontrol_msgs__msg__ControlCMD__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ucontrol_msgs__msg__ControlCMD__fini(&data[i - 1]);
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
ucontrol_msgs__msg__ControlCMD__Sequence__fini(ucontrol_msgs__msg__ControlCMD__Sequence * array)
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
      ucontrol_msgs__msg__ControlCMD__fini(&array->data[i]);
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

ucontrol_msgs__msg__ControlCMD__Sequence *
ucontrol_msgs__msg__ControlCMD__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__ControlCMD__Sequence * array = (ucontrol_msgs__msg__ControlCMD__Sequence *)allocator.allocate(sizeof(ucontrol_msgs__msg__ControlCMD__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = ucontrol_msgs__msg__ControlCMD__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
ucontrol_msgs__msg__ControlCMD__Sequence__destroy(ucontrol_msgs__msg__ControlCMD__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    ucontrol_msgs__msg__ControlCMD__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
ucontrol_msgs__msg__ControlCMD__Sequence__are_equal(const ucontrol_msgs__msg__ControlCMD__Sequence * lhs, const ucontrol_msgs__msg__ControlCMD__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ucontrol_msgs__msg__ControlCMD__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ucontrol_msgs__msg__ControlCMD__Sequence__copy(
  const ucontrol_msgs__msg__ControlCMD__Sequence * input,
  ucontrol_msgs__msg__ControlCMD__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ucontrol_msgs__msg__ControlCMD);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    ucontrol_msgs__msg__ControlCMD * data =
      (ucontrol_msgs__msg__ControlCMD *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ucontrol_msgs__msg__ControlCMD__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          ucontrol_msgs__msg__ControlCMD__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!ucontrol_msgs__msg__ControlCMD__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
