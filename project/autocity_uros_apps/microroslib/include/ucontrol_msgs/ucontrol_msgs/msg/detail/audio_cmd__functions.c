// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ucontrol_msgs:msg/AudioCMD.idl
// generated code does not contain a copyright notice
#include "ucontrol_msgs/msg/detail/audio_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
ucontrol_msgs__msg__AudioCMD__init(ucontrol_msgs__msg__AudioCMD * msg)
{
  if (!msg) {
    return false;
  }
  // audio_cmd
  // audio_num
  // audio_volume
  // audio_mode
  // play_cycle_cnt
  // play_cycle_duration
  // play_cycle_interval
  // horn_cmd
  return true;
}

void
ucontrol_msgs__msg__AudioCMD__fini(ucontrol_msgs__msg__AudioCMD * msg)
{
  if (!msg) {
    return;
  }
  // audio_cmd
  // audio_num
  // audio_volume
  // audio_mode
  // play_cycle_cnt
  // play_cycle_duration
  // play_cycle_interval
  // horn_cmd
}

bool
ucontrol_msgs__msg__AudioCMD__are_equal(const ucontrol_msgs__msg__AudioCMD * lhs, const ucontrol_msgs__msg__AudioCMD * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // audio_cmd
  if (lhs->audio_cmd != rhs->audio_cmd) {
    return false;
  }
  // audio_num
  if (lhs->audio_num != rhs->audio_num) {
    return false;
  }
  // audio_volume
  if (lhs->audio_volume != rhs->audio_volume) {
    return false;
  }
  // audio_mode
  if (lhs->audio_mode != rhs->audio_mode) {
    return false;
  }
  // play_cycle_cnt
  if (lhs->play_cycle_cnt != rhs->play_cycle_cnt) {
    return false;
  }
  // play_cycle_duration
  if (lhs->play_cycle_duration != rhs->play_cycle_duration) {
    return false;
  }
  // play_cycle_interval
  if (lhs->play_cycle_interval != rhs->play_cycle_interval) {
    return false;
  }
  // horn_cmd
  if (lhs->horn_cmd != rhs->horn_cmd) {
    return false;
  }
  return true;
}

bool
ucontrol_msgs__msg__AudioCMD__copy(
  const ucontrol_msgs__msg__AudioCMD * input,
  ucontrol_msgs__msg__AudioCMD * output)
{
  if (!input || !output) {
    return false;
  }
  // audio_cmd
  output->audio_cmd = input->audio_cmd;
  // audio_num
  output->audio_num = input->audio_num;
  // audio_volume
  output->audio_volume = input->audio_volume;
  // audio_mode
  output->audio_mode = input->audio_mode;
  // play_cycle_cnt
  output->play_cycle_cnt = input->play_cycle_cnt;
  // play_cycle_duration
  output->play_cycle_duration = input->play_cycle_duration;
  // play_cycle_interval
  output->play_cycle_interval = input->play_cycle_interval;
  // horn_cmd
  output->horn_cmd = input->horn_cmd;
  return true;
}

ucontrol_msgs__msg__AudioCMD *
ucontrol_msgs__msg__AudioCMD__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__AudioCMD * msg = (ucontrol_msgs__msg__AudioCMD *)allocator.allocate(sizeof(ucontrol_msgs__msg__AudioCMD), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ucontrol_msgs__msg__AudioCMD));
  bool success = ucontrol_msgs__msg__AudioCMD__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
ucontrol_msgs__msg__AudioCMD__destroy(ucontrol_msgs__msg__AudioCMD * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    ucontrol_msgs__msg__AudioCMD__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
ucontrol_msgs__msg__AudioCMD__Sequence__init(ucontrol_msgs__msg__AudioCMD__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__AudioCMD * data = NULL;

  if (size) {
    data = (ucontrol_msgs__msg__AudioCMD *)allocator.zero_allocate(size, sizeof(ucontrol_msgs__msg__AudioCMD), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ucontrol_msgs__msg__AudioCMD__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ucontrol_msgs__msg__AudioCMD__fini(&data[i - 1]);
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
ucontrol_msgs__msg__AudioCMD__Sequence__fini(ucontrol_msgs__msg__AudioCMD__Sequence * array)
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
      ucontrol_msgs__msg__AudioCMD__fini(&array->data[i]);
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

ucontrol_msgs__msg__AudioCMD__Sequence *
ucontrol_msgs__msg__AudioCMD__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__AudioCMD__Sequence * array = (ucontrol_msgs__msg__AudioCMD__Sequence *)allocator.allocate(sizeof(ucontrol_msgs__msg__AudioCMD__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = ucontrol_msgs__msg__AudioCMD__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
ucontrol_msgs__msg__AudioCMD__Sequence__destroy(ucontrol_msgs__msg__AudioCMD__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    ucontrol_msgs__msg__AudioCMD__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
ucontrol_msgs__msg__AudioCMD__Sequence__are_equal(const ucontrol_msgs__msg__AudioCMD__Sequence * lhs, const ucontrol_msgs__msg__AudioCMD__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ucontrol_msgs__msg__AudioCMD__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ucontrol_msgs__msg__AudioCMD__Sequence__copy(
  const ucontrol_msgs__msg__AudioCMD__Sequence * input,
  ucontrol_msgs__msg__AudioCMD__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ucontrol_msgs__msg__AudioCMD);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    ucontrol_msgs__msg__AudioCMD * data =
      (ucontrol_msgs__msg__AudioCMD *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ucontrol_msgs__msg__AudioCMD__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          ucontrol_msgs__msg__AudioCMD__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!ucontrol_msgs__msg__AudioCMD__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
