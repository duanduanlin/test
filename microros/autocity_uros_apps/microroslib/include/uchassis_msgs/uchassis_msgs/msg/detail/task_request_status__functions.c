// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from uchassis_msgs:msg/TaskRequestStatus.idl
// generated code does not contain a copyright notice
#include "uchassis_msgs/msg/detail/task_request_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
uchassis_msgs__msg__TaskRequestStatus__init(uchassis_msgs__msg__TaskRequestStatus * msg)
{
  if (!msg) {
    return false;
  }
  // sweeping_task_status
  // dustbin_lifting_task_status
  // dustbin_dumping_cleaning_task_status
  // dustbin_reset_task_status
  // wireless_charge_task_status
  // left_front_brush_tgt_abd_dist_mm
  // right_front_brush_tgt_abd_dist_mm
  return true;
}

void
uchassis_msgs__msg__TaskRequestStatus__fini(uchassis_msgs__msg__TaskRequestStatus * msg)
{
  if (!msg) {
    return;
  }
  // sweeping_task_status
  // dustbin_lifting_task_status
  // dustbin_dumping_cleaning_task_status
  // dustbin_reset_task_status
  // wireless_charge_task_status
  // left_front_brush_tgt_abd_dist_mm
  // right_front_brush_tgt_abd_dist_mm
}

bool
uchassis_msgs__msg__TaskRequestStatus__are_equal(const uchassis_msgs__msg__TaskRequestStatus * lhs, const uchassis_msgs__msg__TaskRequestStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // sweeping_task_status
  if (lhs->sweeping_task_status != rhs->sweeping_task_status) {
    return false;
  }
  // dustbin_lifting_task_status
  if (lhs->dustbin_lifting_task_status != rhs->dustbin_lifting_task_status) {
    return false;
  }
  // dustbin_dumping_cleaning_task_status
  if (lhs->dustbin_dumping_cleaning_task_status != rhs->dustbin_dumping_cleaning_task_status) {
    return false;
  }
  // dustbin_reset_task_status
  if (lhs->dustbin_reset_task_status != rhs->dustbin_reset_task_status) {
    return false;
  }
  // wireless_charge_task_status
  if (lhs->wireless_charge_task_status != rhs->wireless_charge_task_status) {
    return false;
  }
  // left_front_brush_tgt_abd_dist_mm
  if (lhs->left_front_brush_tgt_abd_dist_mm != rhs->left_front_brush_tgt_abd_dist_mm) {
    return false;
  }
  // right_front_brush_tgt_abd_dist_mm
  if (lhs->right_front_brush_tgt_abd_dist_mm != rhs->right_front_brush_tgt_abd_dist_mm) {
    return false;
  }
  return true;
}

bool
uchassis_msgs__msg__TaskRequestStatus__copy(
  const uchassis_msgs__msg__TaskRequestStatus * input,
  uchassis_msgs__msg__TaskRequestStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // sweeping_task_status
  output->sweeping_task_status = input->sweeping_task_status;
  // dustbin_lifting_task_status
  output->dustbin_lifting_task_status = input->dustbin_lifting_task_status;
  // dustbin_dumping_cleaning_task_status
  output->dustbin_dumping_cleaning_task_status = input->dustbin_dumping_cleaning_task_status;
  // dustbin_reset_task_status
  output->dustbin_reset_task_status = input->dustbin_reset_task_status;
  // wireless_charge_task_status
  output->wireless_charge_task_status = input->wireless_charge_task_status;
  // left_front_brush_tgt_abd_dist_mm
  output->left_front_brush_tgt_abd_dist_mm = input->left_front_brush_tgt_abd_dist_mm;
  // right_front_brush_tgt_abd_dist_mm
  output->right_front_brush_tgt_abd_dist_mm = input->right_front_brush_tgt_abd_dist_mm;
  return true;
}

uchassis_msgs__msg__TaskRequestStatus *
uchassis_msgs__msg__TaskRequestStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__TaskRequestStatus * msg = (uchassis_msgs__msg__TaskRequestStatus *)allocator.allocate(sizeof(uchassis_msgs__msg__TaskRequestStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(uchassis_msgs__msg__TaskRequestStatus));
  bool success = uchassis_msgs__msg__TaskRequestStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
uchassis_msgs__msg__TaskRequestStatus__destroy(uchassis_msgs__msg__TaskRequestStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    uchassis_msgs__msg__TaskRequestStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
uchassis_msgs__msg__TaskRequestStatus__Sequence__init(uchassis_msgs__msg__TaskRequestStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__TaskRequestStatus * data = NULL;

  if (size) {
    data = (uchassis_msgs__msg__TaskRequestStatus *)allocator.zero_allocate(size, sizeof(uchassis_msgs__msg__TaskRequestStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = uchassis_msgs__msg__TaskRequestStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        uchassis_msgs__msg__TaskRequestStatus__fini(&data[i - 1]);
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
uchassis_msgs__msg__TaskRequestStatus__Sequence__fini(uchassis_msgs__msg__TaskRequestStatus__Sequence * array)
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
      uchassis_msgs__msg__TaskRequestStatus__fini(&array->data[i]);
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

uchassis_msgs__msg__TaskRequestStatus__Sequence *
uchassis_msgs__msg__TaskRequestStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__TaskRequestStatus__Sequence * array = (uchassis_msgs__msg__TaskRequestStatus__Sequence *)allocator.allocate(sizeof(uchassis_msgs__msg__TaskRequestStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = uchassis_msgs__msg__TaskRequestStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
uchassis_msgs__msg__TaskRequestStatus__Sequence__destroy(uchassis_msgs__msg__TaskRequestStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    uchassis_msgs__msg__TaskRequestStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
uchassis_msgs__msg__TaskRequestStatus__Sequence__are_equal(const uchassis_msgs__msg__TaskRequestStatus__Sequence * lhs, const uchassis_msgs__msg__TaskRequestStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!uchassis_msgs__msg__TaskRequestStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
uchassis_msgs__msg__TaskRequestStatus__Sequence__copy(
  const uchassis_msgs__msg__TaskRequestStatus__Sequence * input,
  uchassis_msgs__msg__TaskRequestStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(uchassis_msgs__msg__TaskRequestStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    uchassis_msgs__msg__TaskRequestStatus * data =
      (uchassis_msgs__msg__TaskRequestStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!uchassis_msgs__msg__TaskRequestStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          uchassis_msgs__msg__TaskRequestStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!uchassis_msgs__msg__TaskRequestStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
