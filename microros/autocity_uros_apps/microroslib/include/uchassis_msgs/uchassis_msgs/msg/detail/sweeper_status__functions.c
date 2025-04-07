// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from uchassis_msgs:msg/SweeperStatus.idl
// generated code does not contain a copyright notice
#include "uchassis_msgs/msg/detail/sweeper_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
uchassis_msgs__msg__SweeperStatus__init(uchassis_msgs__msg__SweeperStatus * msg)
{
  if (!msg) {
    return false;
  }
  // sweeping
  // remain_water
  return true;
}

void
uchassis_msgs__msg__SweeperStatus__fini(uchassis_msgs__msg__SweeperStatus * msg)
{
  if (!msg) {
    return;
  }
  // sweeping
  // remain_water
}

bool
uchassis_msgs__msg__SweeperStatus__are_equal(const uchassis_msgs__msg__SweeperStatus * lhs, const uchassis_msgs__msg__SweeperStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // sweeping
  if (lhs->sweeping != rhs->sweeping) {
    return false;
  }
  // remain_water
  if (lhs->remain_water != rhs->remain_water) {
    return false;
  }
  return true;
}

bool
uchassis_msgs__msg__SweeperStatus__copy(
  const uchassis_msgs__msg__SweeperStatus * input,
  uchassis_msgs__msg__SweeperStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // sweeping
  output->sweeping = input->sweeping;
  // remain_water
  output->remain_water = input->remain_water;
  return true;
}

uchassis_msgs__msg__SweeperStatus *
uchassis_msgs__msg__SweeperStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__SweeperStatus * msg = (uchassis_msgs__msg__SweeperStatus *)allocator.allocate(sizeof(uchassis_msgs__msg__SweeperStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(uchassis_msgs__msg__SweeperStatus));
  bool success = uchassis_msgs__msg__SweeperStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
uchassis_msgs__msg__SweeperStatus__destroy(uchassis_msgs__msg__SweeperStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    uchassis_msgs__msg__SweeperStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
uchassis_msgs__msg__SweeperStatus__Sequence__init(uchassis_msgs__msg__SweeperStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__SweeperStatus * data = NULL;

  if (size) {
    data = (uchassis_msgs__msg__SweeperStatus *)allocator.zero_allocate(size, sizeof(uchassis_msgs__msg__SweeperStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = uchassis_msgs__msg__SweeperStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        uchassis_msgs__msg__SweeperStatus__fini(&data[i - 1]);
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
uchassis_msgs__msg__SweeperStatus__Sequence__fini(uchassis_msgs__msg__SweeperStatus__Sequence * array)
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
      uchassis_msgs__msg__SweeperStatus__fini(&array->data[i]);
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

uchassis_msgs__msg__SweeperStatus__Sequence *
uchassis_msgs__msg__SweeperStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__SweeperStatus__Sequence * array = (uchassis_msgs__msg__SweeperStatus__Sequence *)allocator.allocate(sizeof(uchassis_msgs__msg__SweeperStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = uchassis_msgs__msg__SweeperStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
uchassis_msgs__msg__SweeperStatus__Sequence__destroy(uchassis_msgs__msg__SweeperStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    uchassis_msgs__msg__SweeperStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
uchassis_msgs__msg__SweeperStatus__Sequence__are_equal(const uchassis_msgs__msg__SweeperStatus__Sequence * lhs, const uchassis_msgs__msg__SweeperStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!uchassis_msgs__msg__SweeperStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
uchassis_msgs__msg__SweeperStatus__Sequence__copy(
  const uchassis_msgs__msg__SweeperStatus__Sequence * input,
  uchassis_msgs__msg__SweeperStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(uchassis_msgs__msg__SweeperStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    uchassis_msgs__msg__SweeperStatus * data =
      (uchassis_msgs__msg__SweeperStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!uchassis_msgs__msg__SweeperStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          uchassis_msgs__msg__SweeperStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!uchassis_msgs__msg__SweeperStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
