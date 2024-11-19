// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ucontrol_msgs:msg/LightCMD.idl
// generated code does not contain a copyright notice
#include "ucontrol_msgs/msg/detail/light_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
ucontrol_msgs__msg__LightCMD__init(ucontrol_msgs__msg__LightCMD * msg)
{
  if (!msg) {
    return false;
  }
  // head_lamp_cmd
  // fog_lamp_cmd
  // caution_lamp_cmd
  // turn_light_cmd
  // back_light_cmd
  return true;
}

void
ucontrol_msgs__msg__LightCMD__fini(ucontrol_msgs__msg__LightCMD * msg)
{
  if (!msg) {
    return;
  }
  // head_lamp_cmd
  // fog_lamp_cmd
  // caution_lamp_cmd
  // turn_light_cmd
  // back_light_cmd
}

bool
ucontrol_msgs__msg__LightCMD__are_equal(const ucontrol_msgs__msg__LightCMD * lhs, const ucontrol_msgs__msg__LightCMD * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // head_lamp_cmd
  if (lhs->head_lamp_cmd != rhs->head_lamp_cmd) {
    return false;
  }
  // fog_lamp_cmd
  if (lhs->fog_lamp_cmd != rhs->fog_lamp_cmd) {
    return false;
  }
  // caution_lamp_cmd
  if (lhs->caution_lamp_cmd != rhs->caution_lamp_cmd) {
    return false;
  }
  // turn_light_cmd
  if (lhs->turn_light_cmd != rhs->turn_light_cmd) {
    return false;
  }
  // back_light_cmd
  if (lhs->back_light_cmd != rhs->back_light_cmd) {
    return false;
  }
  return true;
}

bool
ucontrol_msgs__msg__LightCMD__copy(
  const ucontrol_msgs__msg__LightCMD * input,
  ucontrol_msgs__msg__LightCMD * output)
{
  if (!input || !output) {
    return false;
  }
  // head_lamp_cmd
  output->head_lamp_cmd = input->head_lamp_cmd;
  // fog_lamp_cmd
  output->fog_lamp_cmd = input->fog_lamp_cmd;
  // caution_lamp_cmd
  output->caution_lamp_cmd = input->caution_lamp_cmd;
  // turn_light_cmd
  output->turn_light_cmd = input->turn_light_cmd;
  // back_light_cmd
  output->back_light_cmd = input->back_light_cmd;
  return true;
}

ucontrol_msgs__msg__LightCMD *
ucontrol_msgs__msg__LightCMD__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__LightCMD * msg = (ucontrol_msgs__msg__LightCMD *)allocator.allocate(sizeof(ucontrol_msgs__msg__LightCMD), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ucontrol_msgs__msg__LightCMD));
  bool success = ucontrol_msgs__msg__LightCMD__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
ucontrol_msgs__msg__LightCMD__destroy(ucontrol_msgs__msg__LightCMD * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    ucontrol_msgs__msg__LightCMD__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
ucontrol_msgs__msg__LightCMD__Sequence__init(ucontrol_msgs__msg__LightCMD__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__LightCMD * data = NULL;

  if (size) {
    data = (ucontrol_msgs__msg__LightCMD *)allocator.zero_allocate(size, sizeof(ucontrol_msgs__msg__LightCMD), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ucontrol_msgs__msg__LightCMD__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ucontrol_msgs__msg__LightCMD__fini(&data[i - 1]);
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
ucontrol_msgs__msg__LightCMD__Sequence__fini(ucontrol_msgs__msg__LightCMD__Sequence * array)
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
      ucontrol_msgs__msg__LightCMD__fini(&array->data[i]);
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

ucontrol_msgs__msg__LightCMD__Sequence *
ucontrol_msgs__msg__LightCMD__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__LightCMD__Sequence * array = (ucontrol_msgs__msg__LightCMD__Sequence *)allocator.allocate(sizeof(ucontrol_msgs__msg__LightCMD__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = ucontrol_msgs__msg__LightCMD__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
ucontrol_msgs__msg__LightCMD__Sequence__destroy(ucontrol_msgs__msg__LightCMD__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    ucontrol_msgs__msg__LightCMD__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
ucontrol_msgs__msg__LightCMD__Sequence__are_equal(const ucontrol_msgs__msg__LightCMD__Sequence * lhs, const ucontrol_msgs__msg__LightCMD__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ucontrol_msgs__msg__LightCMD__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ucontrol_msgs__msg__LightCMD__Sequence__copy(
  const ucontrol_msgs__msg__LightCMD__Sequence * input,
  ucontrol_msgs__msg__LightCMD__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ucontrol_msgs__msg__LightCMD);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    ucontrol_msgs__msg__LightCMD * data =
      (ucontrol_msgs__msg__LightCMD *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ucontrol_msgs__msg__LightCMD__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          ucontrol_msgs__msg__LightCMD__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!ucontrol_msgs__msg__LightCMD__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
