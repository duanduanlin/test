// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from uchassis_msgs:msg/TaskRequestStatus.idl
// generated code does not contain a copyright notice

#ifndef UCHASSIS_MSGS__MSG__DETAIL__TASK_REQUEST_STATUS__FUNCTIONS_H_
#define UCHASSIS_MSGS__MSG__DETAIL__TASK_REQUEST_STATUS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "uchassis_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "uchassis_msgs/msg/detail/task_request_status__struct.h"

/// Initialize msg/TaskRequestStatus message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * uchassis_msgs__msg__TaskRequestStatus
 * )) before or use
 * uchassis_msgs__msg__TaskRequestStatus__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_uchassis_msgs
bool
uchassis_msgs__msg__TaskRequestStatus__init(uchassis_msgs__msg__TaskRequestStatus * msg);

/// Finalize msg/TaskRequestStatus message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uchassis_msgs
void
uchassis_msgs__msg__TaskRequestStatus__fini(uchassis_msgs__msg__TaskRequestStatus * msg);

/// Create msg/TaskRequestStatus message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * uchassis_msgs__msg__TaskRequestStatus__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_uchassis_msgs
uchassis_msgs__msg__TaskRequestStatus *
uchassis_msgs__msg__TaskRequestStatus__create();

/// Destroy msg/TaskRequestStatus message.
/**
 * It calls
 * uchassis_msgs__msg__TaskRequestStatus__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uchassis_msgs
void
uchassis_msgs__msg__TaskRequestStatus__destroy(uchassis_msgs__msg__TaskRequestStatus * msg);

/// Check for msg/TaskRequestStatus message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_uchassis_msgs
bool
uchassis_msgs__msg__TaskRequestStatus__are_equal(const uchassis_msgs__msg__TaskRequestStatus * lhs, const uchassis_msgs__msg__TaskRequestStatus * rhs);

/// Copy a msg/TaskRequestStatus message.
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
ROSIDL_GENERATOR_C_PUBLIC_uchassis_msgs
bool
uchassis_msgs__msg__TaskRequestStatus__copy(
  const uchassis_msgs__msg__TaskRequestStatus * input,
  uchassis_msgs__msg__TaskRequestStatus * output);

/// Initialize array of msg/TaskRequestStatus messages.
/**
 * It allocates the memory for the number of elements and calls
 * uchassis_msgs__msg__TaskRequestStatus__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_uchassis_msgs
bool
uchassis_msgs__msg__TaskRequestStatus__Sequence__init(uchassis_msgs__msg__TaskRequestStatus__Sequence * array, size_t size);

/// Finalize array of msg/TaskRequestStatus messages.
/**
 * It calls
 * uchassis_msgs__msg__TaskRequestStatus__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uchassis_msgs
void
uchassis_msgs__msg__TaskRequestStatus__Sequence__fini(uchassis_msgs__msg__TaskRequestStatus__Sequence * array);

/// Create array of msg/TaskRequestStatus messages.
/**
 * It allocates the memory for the array and calls
 * uchassis_msgs__msg__TaskRequestStatus__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_uchassis_msgs
uchassis_msgs__msg__TaskRequestStatus__Sequence *
uchassis_msgs__msg__TaskRequestStatus__Sequence__create(size_t size);

/// Destroy array of msg/TaskRequestStatus messages.
/**
 * It calls
 * uchassis_msgs__msg__TaskRequestStatus__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uchassis_msgs
void
uchassis_msgs__msg__TaskRequestStatus__Sequence__destroy(uchassis_msgs__msg__TaskRequestStatus__Sequence * array);

/// Check for msg/TaskRequestStatus message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_uchassis_msgs
bool
uchassis_msgs__msg__TaskRequestStatus__Sequence__are_equal(const uchassis_msgs__msg__TaskRequestStatus__Sequence * lhs, const uchassis_msgs__msg__TaskRequestStatus__Sequence * rhs);

/// Copy an array of msg/TaskRequestStatus messages.
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
ROSIDL_GENERATOR_C_PUBLIC_uchassis_msgs
bool
uchassis_msgs__msg__TaskRequestStatus__Sequence__copy(
  const uchassis_msgs__msg__TaskRequestStatus__Sequence * input,
  uchassis_msgs__msg__TaskRequestStatus__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // UCHASSIS_MSGS__MSG__DETAIL__TASK_REQUEST_STATUS__FUNCTIONS_H_
