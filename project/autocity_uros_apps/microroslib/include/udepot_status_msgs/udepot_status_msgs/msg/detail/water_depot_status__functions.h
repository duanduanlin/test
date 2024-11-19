// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from udepot_status_msgs:msg/WaterDepotStatus.idl
// generated code does not contain a copyright notice

#ifndef UDEPOT_STATUS_MSGS__MSG__DETAIL__WATER_DEPOT_STATUS__FUNCTIONS_H_
#define UDEPOT_STATUS_MSGS__MSG__DETAIL__WATER_DEPOT_STATUS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "udepot_status_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "udepot_status_msgs/msg/detail/water_depot_status__struct.h"

/// Initialize msg/WaterDepotStatus message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * udepot_status_msgs__msg__WaterDepotStatus
 * )) before or use
 * udepot_status_msgs__msg__WaterDepotStatus__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_udepot_status_msgs
bool
udepot_status_msgs__msg__WaterDepotStatus__init(udepot_status_msgs__msg__WaterDepotStatus * msg);

/// Finalize msg/WaterDepotStatus message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_udepot_status_msgs
void
udepot_status_msgs__msg__WaterDepotStatus__fini(udepot_status_msgs__msg__WaterDepotStatus * msg);

/// Create msg/WaterDepotStatus message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * udepot_status_msgs__msg__WaterDepotStatus__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_udepot_status_msgs
udepot_status_msgs__msg__WaterDepotStatus *
udepot_status_msgs__msg__WaterDepotStatus__create();

/// Destroy msg/WaterDepotStatus message.
/**
 * It calls
 * udepot_status_msgs__msg__WaterDepotStatus__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_udepot_status_msgs
void
udepot_status_msgs__msg__WaterDepotStatus__destroy(udepot_status_msgs__msg__WaterDepotStatus * msg);

/// Check for msg/WaterDepotStatus message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_udepot_status_msgs
bool
udepot_status_msgs__msg__WaterDepotStatus__are_equal(const udepot_status_msgs__msg__WaterDepotStatus * lhs, const udepot_status_msgs__msg__WaterDepotStatus * rhs);

/// Copy a msg/WaterDepotStatus message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_udepot_status_msgs
bool
udepot_status_msgs__msg__WaterDepotStatus__copy(
  const udepot_status_msgs__msg__WaterDepotStatus * input,
  udepot_status_msgs__msg__WaterDepotStatus * output);

/// Initialize array of msg/WaterDepotStatus messages.
/**
 * It allocates the memory for the number of elements and calls
 * udepot_status_msgs__msg__WaterDepotStatus__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_udepot_status_msgs
bool
udepot_status_msgs__msg__WaterDepotStatus__Sequence__init(udepot_status_msgs__msg__WaterDepotStatus__Sequence * array, size_t size);

/// Finalize array of msg/WaterDepotStatus messages.
/**
 * It calls
 * udepot_status_msgs__msg__WaterDepotStatus__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_udepot_status_msgs
void
udepot_status_msgs__msg__WaterDepotStatus__Sequence__fini(udepot_status_msgs__msg__WaterDepotStatus__Sequence * array);

/// Create array of msg/WaterDepotStatus messages.
/**
 * It allocates the memory for the array and calls
 * udepot_status_msgs__msg__WaterDepotStatus__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_udepot_status_msgs
udepot_status_msgs__msg__WaterDepotStatus__Sequence *
udepot_status_msgs__msg__WaterDepotStatus__Sequence__create(size_t size);

/// Destroy array of msg/WaterDepotStatus messages.
/**
 * It calls
 * udepot_status_msgs__msg__WaterDepotStatus__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_udepot_status_msgs
void
udepot_status_msgs__msg__WaterDepotStatus__Sequence__destroy(udepot_status_msgs__msg__WaterDepotStatus__Sequence * array);

/// Check for msg/WaterDepotStatus message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_udepot_status_msgs
bool
udepot_status_msgs__msg__WaterDepotStatus__Sequence__are_equal(const udepot_status_msgs__msg__WaterDepotStatus__Sequence * lhs, const udepot_status_msgs__msg__WaterDepotStatus__Sequence * rhs);

/// Copy an array of msg/WaterDepotStatus messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_udepot_status_msgs
bool
udepot_status_msgs__msg__WaterDepotStatus__Sequence__copy(
  const udepot_status_msgs__msg__WaterDepotStatus__Sequence * input,
  udepot_status_msgs__msg__WaterDepotStatus__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // UDEPOT_STATUS_MSGS__MSG__DETAIL__WATER_DEPOT_STATUS__FUNCTIONS_H_
