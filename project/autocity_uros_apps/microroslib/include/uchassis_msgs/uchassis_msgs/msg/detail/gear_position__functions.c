// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from uchassis_msgs:msg/GearPosition.idl
// generated code does not contain a copyright notice
#include "uchassis_msgs/msg/detail/gear_position__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
uchassis_msgs__msg__GearPosition__init(uchassis_msgs__msg__GearPosition * msg)
{
  if (!msg) {
    return false;
  }
  // value
  return true;
}

void
uchassis_msgs__msg__GearPosition__fini(uchassis_msgs__msg__GearPosition * msg)
{
  if (!msg) {
    return;
  }
  // value
}

bool
uchassis_msgs__msg__GearPosition__are_equal(const uchassis_msgs__msg__GearPosition * lhs, const uchassis_msgs__msg__GearPosition * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // value
  if (lhs->value != rhs->value) {
    return false;
  }
  return true;
}

bool
uchassis_msgs__msg__GearPosition__copy(
  const uchassis_msgs__msg__GearPosition * input,
  uchassis_msgs__msg__GearPosition * output)
{
  if (!input || !output) {
    return false;
  }
  // value
  output->value = input->value;
  return true;
}

uchassis_msgs__msg__GearPosition *
uchassis_msgs__msg__GearPosition__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__GearPosition * msg = (uchassis_msgs__msg__GearPosition *)allocator.allocate(sizeof(uchassis_msgs__msg__GearPosition), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(uchassis_msgs__msg__GearPosition));
  bool success = uchassis_msgs__msg__GearPosition__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
uchassis_msgs__msg__GearPosition__destroy(uchassis_msgs__msg__GearPosition * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    uchassis_msgs__msg__GearPosition__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
uchassis_msgs__msg__GearPosition__Sequence__init(uchassis_msgs__msg__GearPosition__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__GearPosition * data = NULL;

  if (size) {
    data = (uchassis_msgs__msg__GearPosition *)allocator.zero_allocate(size, sizeof(uchassis_msgs__msg__GearPosition), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = uchassis_msgs__msg__GearPosition__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        uchassis_msgs__msg__GearPosition__fini(&data[i - 1]);
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
uchassis_msgs__msg__GearPosition__Sequence__fini(uchassis_msgs__msg__GearPosition__Sequence * array)
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
      uchassis_msgs__msg__GearPosition__fini(&array->data[i]);
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

uchassis_msgs__msg__GearPosition__Sequence *
uchassis_msgs__msg__GearPosition__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__GearPosition__Sequence * array = (uchassis_msgs__msg__GearPosition__Sequence *)allocator.allocate(sizeof(uchassis_msgs__msg__GearPosition__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = uchassis_msgs__msg__GearPosition__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
uchassis_msgs__msg__GearPosition__Sequence__destroy(uchassis_msgs__msg__GearPosition__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    uchassis_msgs__msg__GearPosition__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
uchassis_msgs__msg__GearPosition__Sequence__are_equal(const uchassis_msgs__msg__GearPosition__Sequence * lhs, const uchassis_msgs__msg__GearPosition__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!uchassis_msgs__msg__GearPosition__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
uchassis_msgs__msg__GearPosition__Sequence__copy(
  const uchassis_msgs__msg__GearPosition__Sequence * input,
  uchassis_msgs__msg__GearPosition__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(uchassis_msgs__msg__GearPosition);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    uchassis_msgs__msg__GearPosition * data =
      (uchassis_msgs__msg__GearPosition *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!uchassis_msgs__msg__GearPosition__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          uchassis_msgs__msg__GearPosition__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!uchassis_msgs__msg__GearPosition__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
