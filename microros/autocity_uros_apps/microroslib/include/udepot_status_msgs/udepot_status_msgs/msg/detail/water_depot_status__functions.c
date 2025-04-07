// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from udepot_status_msgs:msg/WaterDepotStatus.idl
// generated code does not contain a copyright notice
#include "udepot_status_msgs/msg/detail/water_depot_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
udepot_status_msgs__msg__WaterDepotStatus__init(udepot_status_msgs__msg__WaterDepotStatus * msg)
{
  if (!msg) {
    return false;
  }
  // network_light_status
  // work_light_status
  // fault_light_status
  // instantaneous_flow
  // total_flow
  // water_valve_status
  // estop_button_status
  // water_button_status
  return true;
}

void
udepot_status_msgs__msg__WaterDepotStatus__fini(udepot_status_msgs__msg__WaterDepotStatus * msg)
{
  if (!msg) {
    return;
  }
  // network_light_status
  // work_light_status
  // fault_light_status
  // instantaneous_flow
  // total_flow
  // water_valve_status
  // estop_button_status
  // water_button_status
}

bool
udepot_status_msgs__msg__WaterDepotStatus__are_equal(const udepot_status_msgs__msg__WaterDepotStatus * lhs, const udepot_status_msgs__msg__WaterDepotStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // network_light_status
  if (lhs->network_light_status != rhs->network_light_status) {
    return false;
  }
  // work_light_status
  if (lhs->work_light_status != rhs->work_light_status) {
    return false;
  }
  // fault_light_status
  if (lhs->fault_light_status != rhs->fault_light_status) {
    return false;
  }
  // instantaneous_flow
  if (lhs->instantaneous_flow != rhs->instantaneous_flow) {
    return false;
  }
  // total_flow
  if (lhs->total_flow != rhs->total_flow) {
    return false;
  }
  // water_valve_status
  if (lhs->water_valve_status != rhs->water_valve_status) {
    return false;
  }
  // estop_button_status
  if (lhs->estop_button_status != rhs->estop_button_status) {
    return false;
  }
  // water_button_status
  if (lhs->water_button_status != rhs->water_button_status) {
    return false;
  }
  return true;
}

bool
udepot_status_msgs__msg__WaterDepotStatus__copy(
  const udepot_status_msgs__msg__WaterDepotStatus * input,
  udepot_status_msgs__msg__WaterDepotStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // network_light_status
  output->network_light_status = input->network_light_status;
  // work_light_status
  output->work_light_status = input->work_light_status;
  // fault_light_status
  output->fault_light_status = input->fault_light_status;
  // instantaneous_flow
  output->instantaneous_flow = input->instantaneous_flow;
  // total_flow
  output->total_flow = input->total_flow;
  // water_valve_status
  output->water_valve_status = input->water_valve_status;
  // estop_button_status
  output->estop_button_status = input->estop_button_status;
  // water_button_status
  output->water_button_status = input->water_button_status;
  return true;
}

udepot_status_msgs__msg__WaterDepotStatus *
udepot_status_msgs__msg__WaterDepotStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  udepot_status_msgs__msg__WaterDepotStatus * msg = (udepot_status_msgs__msg__WaterDepotStatus *)allocator.allocate(sizeof(udepot_status_msgs__msg__WaterDepotStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(udepot_status_msgs__msg__WaterDepotStatus));
  bool success = udepot_status_msgs__msg__WaterDepotStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
udepot_status_msgs__msg__WaterDepotStatus__destroy(udepot_status_msgs__msg__WaterDepotStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    udepot_status_msgs__msg__WaterDepotStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
udepot_status_msgs__msg__WaterDepotStatus__Sequence__init(udepot_status_msgs__msg__WaterDepotStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  udepot_status_msgs__msg__WaterDepotStatus * data = NULL;

  if (size) {
    data = (udepot_status_msgs__msg__WaterDepotStatus *)allocator.zero_allocate(size, sizeof(udepot_status_msgs__msg__WaterDepotStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = udepot_status_msgs__msg__WaterDepotStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        udepot_status_msgs__msg__WaterDepotStatus__fini(&data[i - 1]);
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
udepot_status_msgs__msg__WaterDepotStatus__Sequence__fini(udepot_status_msgs__msg__WaterDepotStatus__Sequence * array)
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
      udepot_status_msgs__msg__WaterDepotStatus__fini(&array->data[i]);
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

udepot_status_msgs__msg__WaterDepotStatus__Sequence *
udepot_status_msgs__msg__WaterDepotStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  udepot_status_msgs__msg__WaterDepotStatus__Sequence * array = (udepot_status_msgs__msg__WaterDepotStatus__Sequence *)allocator.allocate(sizeof(udepot_status_msgs__msg__WaterDepotStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = udepot_status_msgs__msg__WaterDepotStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
udepot_status_msgs__msg__WaterDepotStatus__Sequence__destroy(udepot_status_msgs__msg__WaterDepotStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    udepot_status_msgs__msg__WaterDepotStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
udepot_status_msgs__msg__WaterDepotStatus__Sequence__are_equal(const udepot_status_msgs__msg__WaterDepotStatus__Sequence * lhs, const udepot_status_msgs__msg__WaterDepotStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!udepot_status_msgs__msg__WaterDepotStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
udepot_status_msgs__msg__WaterDepotStatus__Sequence__copy(
  const udepot_status_msgs__msg__WaterDepotStatus__Sequence * input,
  udepot_status_msgs__msg__WaterDepotStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(udepot_status_msgs__msg__WaterDepotStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    udepot_status_msgs__msg__WaterDepotStatus * data =
      (udepot_status_msgs__msg__WaterDepotStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!udepot_status_msgs__msg__WaterDepotStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          udepot_status_msgs__msg__WaterDepotStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!udepot_status_msgs__msg__WaterDepotStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
