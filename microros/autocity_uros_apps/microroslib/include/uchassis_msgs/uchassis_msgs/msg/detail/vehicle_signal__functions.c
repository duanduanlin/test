// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from uchassis_msgs:msg/VehicleSignal.idl
// generated code does not contain a copyright notice
#include "uchassis_msgs/msg/detail/vehicle_signal__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `turn_signal`
#include "uchassis_msgs/msg/detail/turn_signal__functions.h"

bool
uchassis_msgs__msg__VehicleSignal__init(uchassis_msgs__msg__VehicleSignal * msg)
{
  if (!msg) {
    return false;
  }
  // turn_signal
  if (!uchassis_msgs__msg__TurnSignal__init(&msg->turn_signal)) {
    uchassis_msgs__msg__VehicleSignal__fini(msg);
    return false;
  }
  // high_beam
  // low_beam
  // fog_light
  // emergency_light
  // horn
  return true;
}

void
uchassis_msgs__msg__VehicleSignal__fini(uchassis_msgs__msg__VehicleSignal * msg)
{
  if (!msg) {
    return;
  }
  // turn_signal
  uchassis_msgs__msg__TurnSignal__fini(&msg->turn_signal);
  // high_beam
  // low_beam
  // fog_light
  // emergency_light
  // horn
}

bool
uchassis_msgs__msg__VehicleSignal__are_equal(const uchassis_msgs__msg__VehicleSignal * lhs, const uchassis_msgs__msg__VehicleSignal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // turn_signal
  if (!uchassis_msgs__msg__TurnSignal__are_equal(
      &(lhs->turn_signal), &(rhs->turn_signal)))
  {
    return false;
  }
  // high_beam
  if (lhs->high_beam != rhs->high_beam) {
    return false;
  }
  // low_beam
  if (lhs->low_beam != rhs->low_beam) {
    return false;
  }
  // fog_light
  if (lhs->fog_light != rhs->fog_light) {
    return false;
  }
  // emergency_light
  if (lhs->emergency_light != rhs->emergency_light) {
    return false;
  }
  // horn
  if (lhs->horn != rhs->horn) {
    return false;
  }
  return true;
}

bool
uchassis_msgs__msg__VehicleSignal__copy(
  const uchassis_msgs__msg__VehicleSignal * input,
  uchassis_msgs__msg__VehicleSignal * output)
{
  if (!input || !output) {
    return false;
  }
  // turn_signal
  if (!uchassis_msgs__msg__TurnSignal__copy(
      &(input->turn_signal), &(output->turn_signal)))
  {
    return false;
  }
  // high_beam
  output->high_beam = input->high_beam;
  // low_beam
  output->low_beam = input->low_beam;
  // fog_light
  output->fog_light = input->fog_light;
  // emergency_light
  output->emergency_light = input->emergency_light;
  // horn
  output->horn = input->horn;
  return true;
}

uchassis_msgs__msg__VehicleSignal *
uchassis_msgs__msg__VehicleSignal__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__VehicleSignal * msg = (uchassis_msgs__msg__VehicleSignal *)allocator.allocate(sizeof(uchassis_msgs__msg__VehicleSignal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(uchassis_msgs__msg__VehicleSignal));
  bool success = uchassis_msgs__msg__VehicleSignal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
uchassis_msgs__msg__VehicleSignal__destroy(uchassis_msgs__msg__VehicleSignal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    uchassis_msgs__msg__VehicleSignal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
uchassis_msgs__msg__VehicleSignal__Sequence__init(uchassis_msgs__msg__VehicleSignal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__VehicleSignal * data = NULL;

  if (size) {
    data = (uchassis_msgs__msg__VehicleSignal *)allocator.zero_allocate(size, sizeof(uchassis_msgs__msg__VehicleSignal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = uchassis_msgs__msg__VehicleSignal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        uchassis_msgs__msg__VehicleSignal__fini(&data[i - 1]);
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
uchassis_msgs__msg__VehicleSignal__Sequence__fini(uchassis_msgs__msg__VehicleSignal__Sequence * array)
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
      uchassis_msgs__msg__VehicleSignal__fini(&array->data[i]);
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

uchassis_msgs__msg__VehicleSignal__Sequence *
uchassis_msgs__msg__VehicleSignal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__VehicleSignal__Sequence * array = (uchassis_msgs__msg__VehicleSignal__Sequence *)allocator.allocate(sizeof(uchassis_msgs__msg__VehicleSignal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = uchassis_msgs__msg__VehicleSignal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
uchassis_msgs__msg__VehicleSignal__Sequence__destroy(uchassis_msgs__msg__VehicleSignal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    uchassis_msgs__msg__VehicleSignal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
uchassis_msgs__msg__VehicleSignal__Sequence__are_equal(const uchassis_msgs__msg__VehicleSignal__Sequence * lhs, const uchassis_msgs__msg__VehicleSignal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!uchassis_msgs__msg__VehicleSignal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
uchassis_msgs__msg__VehicleSignal__Sequence__copy(
  const uchassis_msgs__msg__VehicleSignal__Sequence * input,
  uchassis_msgs__msg__VehicleSignal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(uchassis_msgs__msg__VehicleSignal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    uchassis_msgs__msg__VehicleSignal * data =
      (uchassis_msgs__msg__VehicleSignal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!uchassis_msgs__msg__VehicleSignal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          uchassis_msgs__msg__VehicleSignal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!uchassis_msgs__msg__VehicleSignal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
