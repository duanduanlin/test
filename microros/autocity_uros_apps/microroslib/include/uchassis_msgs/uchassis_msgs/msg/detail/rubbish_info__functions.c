// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from uchassis_msgs:msg/RubbishInfo.idl
// generated code does not contain a copyright notice
#include "uchassis_msgs/msg/detail/rubbish_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `task_request_status`
#include "uchassis_msgs/msg/detail/task_request_status__functions.h"

bool
uchassis_msgs__msg__RubbishInfo__init(uchassis_msgs__msg__RubbishInfo * msg)
{
  if (!msg) {
    return false;
  }
  // quantity
  // box_remain
  // lift_status
  // lift_position
  // dump_status
  // dump_position
  // door_status
  // door_position
  // dustbin_box_clean_status
  // reset_status
  // task_request_status
  if (!uchassis_msgs__msg__TaskRequestStatus__init(&msg->task_request_status)) {
    uchassis_msgs__msg__RubbishInfo__fini(msg);
    return false;
  }
  return true;
}

void
uchassis_msgs__msg__RubbishInfo__fini(uchassis_msgs__msg__RubbishInfo * msg)
{
  if (!msg) {
    return;
  }
  // quantity
  // box_remain
  // lift_status
  // lift_position
  // dump_status
  // dump_position
  // door_status
  // door_position
  // dustbin_box_clean_status
  // reset_status
  // task_request_status
  uchassis_msgs__msg__TaskRequestStatus__fini(&msg->task_request_status);
}

bool
uchassis_msgs__msg__RubbishInfo__are_equal(const uchassis_msgs__msg__RubbishInfo * lhs, const uchassis_msgs__msg__RubbishInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // quantity
  if (lhs->quantity != rhs->quantity) {
    return false;
  }
  // box_remain
  if (lhs->box_remain != rhs->box_remain) {
    return false;
  }
  // lift_status
  if (lhs->lift_status != rhs->lift_status) {
    return false;
  }
  // lift_position
  if (lhs->lift_position != rhs->lift_position) {
    return false;
  }
  // dump_status
  if (lhs->dump_status != rhs->dump_status) {
    return false;
  }
  // dump_position
  if (lhs->dump_position != rhs->dump_position) {
    return false;
  }
  // door_status
  if (lhs->door_status != rhs->door_status) {
    return false;
  }
  // door_position
  if (lhs->door_position != rhs->door_position) {
    return false;
  }
  // dustbin_box_clean_status
  if (lhs->dustbin_box_clean_status != rhs->dustbin_box_clean_status) {
    return false;
  }
  // reset_status
  if (lhs->reset_status != rhs->reset_status) {
    return false;
  }
  // task_request_status
  if (!uchassis_msgs__msg__TaskRequestStatus__are_equal(
      &(lhs->task_request_status), &(rhs->task_request_status)))
  {
    return false;
  }
  return true;
}

bool
uchassis_msgs__msg__RubbishInfo__copy(
  const uchassis_msgs__msg__RubbishInfo * input,
  uchassis_msgs__msg__RubbishInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // quantity
  output->quantity = input->quantity;
  // box_remain
  output->box_remain = input->box_remain;
  // lift_status
  output->lift_status = input->lift_status;
  // lift_position
  output->lift_position = input->lift_position;
  // dump_status
  output->dump_status = input->dump_status;
  // dump_position
  output->dump_position = input->dump_position;
  // door_status
  output->door_status = input->door_status;
  // door_position
  output->door_position = input->door_position;
  // dustbin_box_clean_status
  output->dustbin_box_clean_status = input->dustbin_box_clean_status;
  // reset_status
  output->reset_status = input->reset_status;
  // task_request_status
  if (!uchassis_msgs__msg__TaskRequestStatus__copy(
      &(input->task_request_status), &(output->task_request_status)))
  {
    return false;
  }
  return true;
}

uchassis_msgs__msg__RubbishInfo *
uchassis_msgs__msg__RubbishInfo__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__RubbishInfo * msg = (uchassis_msgs__msg__RubbishInfo *)allocator.allocate(sizeof(uchassis_msgs__msg__RubbishInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(uchassis_msgs__msg__RubbishInfo));
  bool success = uchassis_msgs__msg__RubbishInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
uchassis_msgs__msg__RubbishInfo__destroy(uchassis_msgs__msg__RubbishInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    uchassis_msgs__msg__RubbishInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
uchassis_msgs__msg__RubbishInfo__Sequence__init(uchassis_msgs__msg__RubbishInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__RubbishInfo * data = NULL;

  if (size) {
    data = (uchassis_msgs__msg__RubbishInfo *)allocator.zero_allocate(size, sizeof(uchassis_msgs__msg__RubbishInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = uchassis_msgs__msg__RubbishInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        uchassis_msgs__msg__RubbishInfo__fini(&data[i - 1]);
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
uchassis_msgs__msg__RubbishInfo__Sequence__fini(uchassis_msgs__msg__RubbishInfo__Sequence * array)
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
      uchassis_msgs__msg__RubbishInfo__fini(&array->data[i]);
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

uchassis_msgs__msg__RubbishInfo__Sequence *
uchassis_msgs__msg__RubbishInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__RubbishInfo__Sequence * array = (uchassis_msgs__msg__RubbishInfo__Sequence *)allocator.allocate(sizeof(uchassis_msgs__msg__RubbishInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = uchassis_msgs__msg__RubbishInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
uchassis_msgs__msg__RubbishInfo__Sequence__destroy(uchassis_msgs__msg__RubbishInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    uchassis_msgs__msg__RubbishInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
uchassis_msgs__msg__RubbishInfo__Sequence__are_equal(const uchassis_msgs__msg__RubbishInfo__Sequence * lhs, const uchassis_msgs__msg__RubbishInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!uchassis_msgs__msg__RubbishInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
uchassis_msgs__msg__RubbishInfo__Sequence__copy(
  const uchassis_msgs__msg__RubbishInfo__Sequence * input,
  uchassis_msgs__msg__RubbishInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(uchassis_msgs__msg__RubbishInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    uchassis_msgs__msg__RubbishInfo * data =
      (uchassis_msgs__msg__RubbishInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!uchassis_msgs__msg__RubbishInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          uchassis_msgs__msg__RubbishInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!uchassis_msgs__msg__RubbishInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
