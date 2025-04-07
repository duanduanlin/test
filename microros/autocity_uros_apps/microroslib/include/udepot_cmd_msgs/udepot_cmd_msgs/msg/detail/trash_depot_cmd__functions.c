// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from udepot_cmd_msgs:msg/TrashDepotCmd.idl
// generated code does not contain a copyright notice
#include "udepot_cmd_msgs/msg/detail/trash_depot_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
udepot_cmd_msgs__msg__TrashDepotCmd__init(udepot_cmd_msgs__msg__TrashDepotCmd * msg)
{
  if (!msg) {
    return false;
  }
  // network_light_cmd
  // fault_light_cmd
  // audio_play_cmd
  // trash_open_cmd
  return true;
}

void
udepot_cmd_msgs__msg__TrashDepotCmd__fini(udepot_cmd_msgs__msg__TrashDepotCmd * msg)
{
  if (!msg) {
    return;
  }
  // network_light_cmd
  // fault_light_cmd
  // audio_play_cmd
  // trash_open_cmd
}

bool
udepot_cmd_msgs__msg__TrashDepotCmd__are_equal(const udepot_cmd_msgs__msg__TrashDepotCmd * lhs, const udepot_cmd_msgs__msg__TrashDepotCmd * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // network_light_cmd
  if (lhs->network_light_cmd != rhs->network_light_cmd) {
    return false;
  }
  // fault_light_cmd
  if (lhs->fault_light_cmd != rhs->fault_light_cmd) {
    return false;
  }
  // audio_play_cmd
  if (lhs->audio_play_cmd != rhs->audio_play_cmd) {
    return false;
  }
  // trash_open_cmd
  if (lhs->trash_open_cmd != rhs->trash_open_cmd) {
    return false;
  }
  return true;
}

bool
udepot_cmd_msgs__msg__TrashDepotCmd__copy(
  const udepot_cmd_msgs__msg__TrashDepotCmd * input,
  udepot_cmd_msgs__msg__TrashDepotCmd * output)
{
  if (!input || !output) {
    return false;
  }
  // network_light_cmd
  output->network_light_cmd = input->network_light_cmd;
  // fault_light_cmd
  output->fault_light_cmd = input->fault_light_cmd;
  // audio_play_cmd
  output->audio_play_cmd = input->audio_play_cmd;
  // trash_open_cmd
  output->trash_open_cmd = input->trash_open_cmd;
  return true;
}

udepot_cmd_msgs__msg__TrashDepotCmd *
udepot_cmd_msgs__msg__TrashDepotCmd__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  udepot_cmd_msgs__msg__TrashDepotCmd * msg = (udepot_cmd_msgs__msg__TrashDepotCmd *)allocator.allocate(sizeof(udepot_cmd_msgs__msg__TrashDepotCmd), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(udepot_cmd_msgs__msg__TrashDepotCmd));
  bool success = udepot_cmd_msgs__msg__TrashDepotCmd__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
udepot_cmd_msgs__msg__TrashDepotCmd__destroy(udepot_cmd_msgs__msg__TrashDepotCmd * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    udepot_cmd_msgs__msg__TrashDepotCmd__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
udepot_cmd_msgs__msg__TrashDepotCmd__Sequence__init(udepot_cmd_msgs__msg__TrashDepotCmd__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  udepot_cmd_msgs__msg__TrashDepotCmd * data = NULL;

  if (size) {
    data = (udepot_cmd_msgs__msg__TrashDepotCmd *)allocator.zero_allocate(size, sizeof(udepot_cmd_msgs__msg__TrashDepotCmd), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = udepot_cmd_msgs__msg__TrashDepotCmd__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        udepot_cmd_msgs__msg__TrashDepotCmd__fini(&data[i - 1]);
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
udepot_cmd_msgs__msg__TrashDepotCmd__Sequence__fini(udepot_cmd_msgs__msg__TrashDepotCmd__Sequence * array)
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
      udepot_cmd_msgs__msg__TrashDepotCmd__fini(&array->data[i]);
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

udepot_cmd_msgs__msg__TrashDepotCmd__Sequence *
udepot_cmd_msgs__msg__TrashDepotCmd__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  udepot_cmd_msgs__msg__TrashDepotCmd__Sequence * array = (udepot_cmd_msgs__msg__TrashDepotCmd__Sequence *)allocator.allocate(sizeof(udepot_cmd_msgs__msg__TrashDepotCmd__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = udepot_cmd_msgs__msg__TrashDepotCmd__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
udepot_cmd_msgs__msg__TrashDepotCmd__Sequence__destroy(udepot_cmd_msgs__msg__TrashDepotCmd__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    udepot_cmd_msgs__msg__TrashDepotCmd__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
udepot_cmd_msgs__msg__TrashDepotCmd__Sequence__are_equal(const udepot_cmd_msgs__msg__TrashDepotCmd__Sequence * lhs, const udepot_cmd_msgs__msg__TrashDepotCmd__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!udepot_cmd_msgs__msg__TrashDepotCmd__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
udepot_cmd_msgs__msg__TrashDepotCmd__Sequence__copy(
  const udepot_cmd_msgs__msg__TrashDepotCmd__Sequence * input,
  udepot_cmd_msgs__msg__TrashDepotCmd__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(udepot_cmd_msgs__msg__TrashDepotCmd);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    udepot_cmd_msgs__msg__TrashDepotCmd * data =
      (udepot_cmd_msgs__msg__TrashDepotCmd *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!udepot_cmd_msgs__msg__TrashDepotCmd__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          udepot_cmd_msgs__msg__TrashDepotCmd__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!udepot_cmd_msgs__msg__TrashDepotCmd__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
