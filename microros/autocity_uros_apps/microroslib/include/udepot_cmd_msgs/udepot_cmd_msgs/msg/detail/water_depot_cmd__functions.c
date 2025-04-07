// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from udepot_cmd_msgs:msg/WaterDepotCmd.idl
// generated code does not contain a copyright notice
#include "udepot_cmd_msgs/msg/detail/water_depot_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
udepot_cmd_msgs__msg__WaterDepotCmd__init(udepot_cmd_msgs__msg__WaterDepotCmd * msg)
{
  if (!msg) {
    return false;
  }
  // network_light_cmd
  // work_light_cmd
  // fault_light_cmd
  // flow_reset_cmd
  // water_valve_cmd
  return true;
}

void
udepot_cmd_msgs__msg__WaterDepotCmd__fini(udepot_cmd_msgs__msg__WaterDepotCmd * msg)
{
  if (!msg) {
    return;
  }
  // network_light_cmd
  // work_light_cmd
  // fault_light_cmd
  // flow_reset_cmd
  // water_valve_cmd
}

bool
udepot_cmd_msgs__msg__WaterDepotCmd__are_equal(const udepot_cmd_msgs__msg__WaterDepotCmd * lhs, const udepot_cmd_msgs__msg__WaterDepotCmd * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // network_light_cmd
  if (lhs->network_light_cmd != rhs->network_light_cmd) {
    return false;
  }
  // work_light_cmd
  if (lhs->work_light_cmd != rhs->work_light_cmd) {
    return false;
  }
  // fault_light_cmd
  if (lhs->fault_light_cmd != rhs->fault_light_cmd) {
    return false;
  }
  // flow_reset_cmd
  if (lhs->flow_reset_cmd != rhs->flow_reset_cmd) {
    return false;
  }
  // water_valve_cmd
  if (lhs->water_valve_cmd != rhs->water_valve_cmd) {
    return false;
  }
  return true;
}

bool
udepot_cmd_msgs__msg__WaterDepotCmd__copy(
  const udepot_cmd_msgs__msg__WaterDepotCmd * input,
  udepot_cmd_msgs__msg__WaterDepotCmd * output)
{
  if (!input || !output) {
    return false;
  }
  // network_light_cmd
  output->network_light_cmd = input->network_light_cmd;
  // work_light_cmd
  output->work_light_cmd = input->work_light_cmd;
  // fault_light_cmd
  output->fault_light_cmd = input->fault_light_cmd;
  // flow_reset_cmd
  output->flow_reset_cmd = input->flow_reset_cmd;
  // water_valve_cmd
  output->water_valve_cmd = input->water_valve_cmd;
  return true;
}

udepot_cmd_msgs__msg__WaterDepotCmd *
udepot_cmd_msgs__msg__WaterDepotCmd__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  udepot_cmd_msgs__msg__WaterDepotCmd * msg = (udepot_cmd_msgs__msg__WaterDepotCmd *)allocator.allocate(sizeof(udepot_cmd_msgs__msg__WaterDepotCmd), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(udepot_cmd_msgs__msg__WaterDepotCmd));
  bool success = udepot_cmd_msgs__msg__WaterDepotCmd__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
udepot_cmd_msgs__msg__WaterDepotCmd__destroy(udepot_cmd_msgs__msg__WaterDepotCmd * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    udepot_cmd_msgs__msg__WaterDepotCmd__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
udepot_cmd_msgs__msg__WaterDepotCmd__Sequence__init(udepot_cmd_msgs__msg__WaterDepotCmd__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  udepot_cmd_msgs__msg__WaterDepotCmd * data = NULL;

  if (size) {
    data = (udepot_cmd_msgs__msg__WaterDepotCmd *)allocator.zero_allocate(size, sizeof(udepot_cmd_msgs__msg__WaterDepotCmd), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = udepot_cmd_msgs__msg__WaterDepotCmd__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        udepot_cmd_msgs__msg__WaterDepotCmd__fini(&data[i - 1]);
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
udepot_cmd_msgs__msg__WaterDepotCmd__Sequence__fini(udepot_cmd_msgs__msg__WaterDepotCmd__Sequence * array)
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
      udepot_cmd_msgs__msg__WaterDepotCmd__fini(&array->data[i]);
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

udepot_cmd_msgs__msg__WaterDepotCmd__Sequence *
udepot_cmd_msgs__msg__WaterDepotCmd__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  udepot_cmd_msgs__msg__WaterDepotCmd__Sequence * array = (udepot_cmd_msgs__msg__WaterDepotCmd__Sequence *)allocator.allocate(sizeof(udepot_cmd_msgs__msg__WaterDepotCmd__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = udepot_cmd_msgs__msg__WaterDepotCmd__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
udepot_cmd_msgs__msg__WaterDepotCmd__Sequence__destroy(udepot_cmd_msgs__msg__WaterDepotCmd__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    udepot_cmd_msgs__msg__WaterDepotCmd__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
udepot_cmd_msgs__msg__WaterDepotCmd__Sequence__are_equal(const udepot_cmd_msgs__msg__WaterDepotCmd__Sequence * lhs, const udepot_cmd_msgs__msg__WaterDepotCmd__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!udepot_cmd_msgs__msg__WaterDepotCmd__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
udepot_cmd_msgs__msg__WaterDepotCmd__Sequence__copy(
  const udepot_cmd_msgs__msg__WaterDepotCmd__Sequence * input,
  udepot_cmd_msgs__msg__WaterDepotCmd__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(udepot_cmd_msgs__msg__WaterDepotCmd);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    udepot_cmd_msgs__msg__WaterDepotCmd * data =
      (udepot_cmd_msgs__msg__WaterDepotCmd *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!udepot_cmd_msgs__msg__WaterDepotCmd__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          udepot_cmd_msgs__msg__WaterDepotCmd__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!udepot_cmd_msgs__msg__WaterDepotCmd__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
