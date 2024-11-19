// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ucontrol_msgs:msg/SweeperCMD.idl
// generated code does not contain a copyright notice
#include "ucontrol_msgs/msg/detail/sweeper_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
ucontrol_msgs__msg__SweeperCMD__init(ucontrol_msgs__msg__SweeperCMD * msg)
{
  if (!msg) {
    return false;
  }
  // sweeping
  // blow_motor_cmd
  // sweep_brush_cmd
  // water_pump_cmd
  // blow_water_pump_cmd
  // suction_water_pump_cmd
  // jaw_plate_cmd
  // left_front_brush_tgt_abd_dist_mm
  // right_front_brush_tgt_abd_dist_mm
  // task_request
  return true;
}

void
ucontrol_msgs__msg__SweeperCMD__fini(ucontrol_msgs__msg__SweeperCMD * msg)
{
  if (!msg) {
    return;
  }
  // sweeping
  // blow_motor_cmd
  // sweep_brush_cmd
  // water_pump_cmd
  // blow_water_pump_cmd
  // suction_water_pump_cmd
  // jaw_plate_cmd
  // left_front_brush_tgt_abd_dist_mm
  // right_front_brush_tgt_abd_dist_mm
  // task_request
}

bool
ucontrol_msgs__msg__SweeperCMD__are_equal(const ucontrol_msgs__msg__SweeperCMD * lhs, const ucontrol_msgs__msg__SweeperCMD * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // sweeping
  if (lhs->sweeping != rhs->sweeping) {
    return false;
  }
  // blow_motor_cmd
  if (lhs->blow_motor_cmd != rhs->blow_motor_cmd) {
    return false;
  }
  // sweep_brush_cmd
  if (lhs->sweep_brush_cmd != rhs->sweep_brush_cmd) {
    return false;
  }
  // water_pump_cmd
  if (lhs->water_pump_cmd != rhs->water_pump_cmd) {
    return false;
  }
  // blow_water_pump_cmd
  if (lhs->blow_water_pump_cmd != rhs->blow_water_pump_cmd) {
    return false;
  }
  // suction_water_pump_cmd
  if (lhs->suction_water_pump_cmd != rhs->suction_water_pump_cmd) {
    return false;
  }
  // jaw_plate_cmd
  if (lhs->jaw_plate_cmd != rhs->jaw_plate_cmd) {
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
  // task_request
  if (lhs->task_request != rhs->task_request) {
    return false;
  }
  return true;
}

bool
ucontrol_msgs__msg__SweeperCMD__copy(
  const ucontrol_msgs__msg__SweeperCMD * input,
  ucontrol_msgs__msg__SweeperCMD * output)
{
  if (!input || !output) {
    return false;
  }
  // sweeping
  output->sweeping = input->sweeping;
  // blow_motor_cmd
  output->blow_motor_cmd = input->blow_motor_cmd;
  // sweep_brush_cmd
  output->sweep_brush_cmd = input->sweep_brush_cmd;
  // water_pump_cmd
  output->water_pump_cmd = input->water_pump_cmd;
  // blow_water_pump_cmd
  output->blow_water_pump_cmd = input->blow_water_pump_cmd;
  // suction_water_pump_cmd
  output->suction_water_pump_cmd = input->suction_water_pump_cmd;
  // jaw_plate_cmd
  output->jaw_plate_cmd = input->jaw_plate_cmd;
  // left_front_brush_tgt_abd_dist_mm
  output->left_front_brush_tgt_abd_dist_mm = input->left_front_brush_tgt_abd_dist_mm;
  // right_front_brush_tgt_abd_dist_mm
  output->right_front_brush_tgt_abd_dist_mm = input->right_front_brush_tgt_abd_dist_mm;
  // task_request
  output->task_request = input->task_request;
  return true;
}

ucontrol_msgs__msg__SweeperCMD *
ucontrol_msgs__msg__SweeperCMD__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__SweeperCMD * msg = (ucontrol_msgs__msg__SweeperCMD *)allocator.allocate(sizeof(ucontrol_msgs__msg__SweeperCMD), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ucontrol_msgs__msg__SweeperCMD));
  bool success = ucontrol_msgs__msg__SweeperCMD__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
ucontrol_msgs__msg__SweeperCMD__destroy(ucontrol_msgs__msg__SweeperCMD * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    ucontrol_msgs__msg__SweeperCMD__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
ucontrol_msgs__msg__SweeperCMD__Sequence__init(ucontrol_msgs__msg__SweeperCMD__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__SweeperCMD * data = NULL;

  if (size) {
    data = (ucontrol_msgs__msg__SweeperCMD *)allocator.zero_allocate(size, sizeof(ucontrol_msgs__msg__SweeperCMD), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ucontrol_msgs__msg__SweeperCMD__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ucontrol_msgs__msg__SweeperCMD__fini(&data[i - 1]);
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
ucontrol_msgs__msg__SweeperCMD__Sequence__fini(ucontrol_msgs__msg__SweeperCMD__Sequence * array)
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
      ucontrol_msgs__msg__SweeperCMD__fini(&array->data[i]);
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

ucontrol_msgs__msg__SweeperCMD__Sequence *
ucontrol_msgs__msg__SweeperCMD__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ucontrol_msgs__msg__SweeperCMD__Sequence * array = (ucontrol_msgs__msg__SweeperCMD__Sequence *)allocator.allocate(sizeof(ucontrol_msgs__msg__SweeperCMD__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = ucontrol_msgs__msg__SweeperCMD__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
ucontrol_msgs__msg__SweeperCMD__Sequence__destroy(ucontrol_msgs__msg__SweeperCMD__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    ucontrol_msgs__msg__SweeperCMD__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
ucontrol_msgs__msg__SweeperCMD__Sequence__are_equal(const ucontrol_msgs__msg__SweeperCMD__Sequence * lhs, const ucontrol_msgs__msg__SweeperCMD__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ucontrol_msgs__msg__SweeperCMD__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ucontrol_msgs__msg__SweeperCMD__Sequence__copy(
  const ucontrol_msgs__msg__SweeperCMD__Sequence * input,
  ucontrol_msgs__msg__SweeperCMD__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ucontrol_msgs__msg__SweeperCMD);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    ucontrol_msgs__msg__SweeperCMD * data =
      (ucontrol_msgs__msg__SweeperCMD *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ucontrol_msgs__msg__SweeperCMD__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          ucontrol_msgs__msg__SweeperCMD__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!ucontrol_msgs__msg__SweeperCMD__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
