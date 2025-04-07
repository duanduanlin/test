// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from uchassis_msgs:msg/BatteryInfo.idl
// generated code does not contain a copyright notice
#include "uchassis_msgs/msg/detail/battery_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
uchassis_msgs__msg__BatteryInfo__init(uchassis_msgs__msg__BatteryInfo * msg)
{
  if (!msg) {
    return false;
  }
  // range_km
  // power_remain
  // battery_temperature
  // battery_current
  // battery_voltage
  // charging_status
  return true;
}

void
uchassis_msgs__msg__BatteryInfo__fini(uchassis_msgs__msg__BatteryInfo * msg)
{
  if (!msg) {
    return;
  }
  // range_km
  // power_remain
  // battery_temperature
  // battery_current
  // battery_voltage
  // charging_status
}

bool
uchassis_msgs__msg__BatteryInfo__are_equal(const uchassis_msgs__msg__BatteryInfo * lhs, const uchassis_msgs__msg__BatteryInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // range_km
  if (lhs->range_km != rhs->range_km) {
    return false;
  }
  // power_remain
  if (lhs->power_remain != rhs->power_remain) {
    return false;
  }
  // battery_temperature
  if (lhs->battery_temperature != rhs->battery_temperature) {
    return false;
  }
  // battery_current
  if (lhs->battery_current != rhs->battery_current) {
    return false;
  }
  // battery_voltage
  if (lhs->battery_voltage != rhs->battery_voltage) {
    return false;
  }
  // charging_status
  if (lhs->charging_status != rhs->charging_status) {
    return false;
  }
  return true;
}

bool
uchassis_msgs__msg__BatteryInfo__copy(
  const uchassis_msgs__msg__BatteryInfo * input,
  uchassis_msgs__msg__BatteryInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // range_km
  output->range_km = input->range_km;
  // power_remain
  output->power_remain = input->power_remain;
  // battery_temperature
  output->battery_temperature = input->battery_temperature;
  // battery_current
  output->battery_current = input->battery_current;
  // battery_voltage
  output->battery_voltage = input->battery_voltage;
  // charging_status
  output->charging_status = input->charging_status;
  return true;
}

uchassis_msgs__msg__BatteryInfo *
uchassis_msgs__msg__BatteryInfo__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__BatteryInfo * msg = (uchassis_msgs__msg__BatteryInfo *)allocator.allocate(sizeof(uchassis_msgs__msg__BatteryInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(uchassis_msgs__msg__BatteryInfo));
  bool success = uchassis_msgs__msg__BatteryInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
uchassis_msgs__msg__BatteryInfo__destroy(uchassis_msgs__msg__BatteryInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    uchassis_msgs__msg__BatteryInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
uchassis_msgs__msg__BatteryInfo__Sequence__init(uchassis_msgs__msg__BatteryInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__BatteryInfo * data = NULL;

  if (size) {
    data = (uchassis_msgs__msg__BatteryInfo *)allocator.zero_allocate(size, sizeof(uchassis_msgs__msg__BatteryInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = uchassis_msgs__msg__BatteryInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        uchassis_msgs__msg__BatteryInfo__fini(&data[i - 1]);
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
uchassis_msgs__msg__BatteryInfo__Sequence__fini(uchassis_msgs__msg__BatteryInfo__Sequence * array)
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
      uchassis_msgs__msg__BatteryInfo__fini(&array->data[i]);
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

uchassis_msgs__msg__BatteryInfo__Sequence *
uchassis_msgs__msg__BatteryInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uchassis_msgs__msg__BatteryInfo__Sequence * array = (uchassis_msgs__msg__BatteryInfo__Sequence *)allocator.allocate(sizeof(uchassis_msgs__msg__BatteryInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = uchassis_msgs__msg__BatteryInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
uchassis_msgs__msg__BatteryInfo__Sequence__destroy(uchassis_msgs__msg__BatteryInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    uchassis_msgs__msg__BatteryInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
uchassis_msgs__msg__BatteryInfo__Sequence__are_equal(const uchassis_msgs__msg__BatteryInfo__Sequence * lhs, const uchassis_msgs__msg__BatteryInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!uchassis_msgs__msg__BatteryInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
uchassis_msgs__msg__BatteryInfo__Sequence__copy(
  const uchassis_msgs__msg__BatteryInfo__Sequence * input,
  uchassis_msgs__msg__BatteryInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(uchassis_msgs__msg__BatteryInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    uchassis_msgs__msg__BatteryInfo * data =
      (uchassis_msgs__msg__BatteryInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!uchassis_msgs__msg__BatteryInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          uchassis_msgs__msg__BatteryInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!uchassis_msgs__msg__BatteryInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
