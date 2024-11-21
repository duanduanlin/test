// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from ucontrol_msgs:msg/ChassisCMD.idl
// generated code does not contain a copyright notice

#ifndef UCONTROL_MSGS__MSG__DETAIL__CHASSIS_CMD__FUNCTIONS_H_
#define UCONTROL_MSGS__MSG__DETAIL__CHASSIS_CMD__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "ucontrol_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "ucontrol_msgs/msg/detail/chassis_cmd__struct.h"

/// Initialize msg/ChassisCMD message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ucontrol_msgs__msg__ChassisCMD
 * )) before or use
 * ucontrol_msgs__msg__ChassisCMD__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ucontrol_msgs
bool
ucontrol_msgs__msg__ChassisCMD__init(ucontrol_msgs__msg__ChassisCMD * msg);

/// Finalize msg/ChassisCMD message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ucontrol_msgs
void
ucontrol_msgs__msg__ChassisCMD__fini(ucontrol_msgs__msg__ChassisCMD * msg);

/// Create msg/ChassisCMD message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ucontrol_msgs__msg__ChassisCMD__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ucontrol_msgs
ucontrol_msgs__msg__ChassisCMD *
ucontrol_msgs__msg__ChassisCMD__create();

/// Destroy msg/ChassisCMD message.
/**
 * It calls
 * ucontrol_msgs__msg__ChassisCMD__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ucontrol_msgs
void
ucontrol_msgs__msg__ChassisCMD__destroy(ucontrol_msgs__msg__ChassisCMD * msg);

/// Check for msg/ChassisCMD message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ucontrol_msgs
bool
ucontrol_msgs__msg__ChassisCMD__are_equal(const ucontrol_msgs__msg__ChassisCMD * lhs, const ucontrol_msgs__msg__ChassisCMD * rhs);

/// Copy a msg/ChassisCMD message.
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
ROSIDL_GENERATOR_C_PUBLIC_ucontrol_msgs
bool
ucontrol_msgs__msg__ChassisCMD__copy(
  const ucontrol_msgs__msg__ChassisCMD * input,
  ucontrol_msgs__msg__ChassisCMD * output);

/// Initialize array of msg/ChassisCMD messages.
/**
 * It allocates the memory for the number of elements and calls
 * ucontrol_msgs__msg__ChassisCMD__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ucontrol_msgs
bool
ucontrol_msgs__msg__ChassisCMD__Sequence__init(ucontrol_msgs__msg__ChassisCMD__Sequence * array, size_t size);

/// Finalize array of msg/ChassisCMD messages.
/**
 * It calls
 * ucontrol_msgs__msg__ChassisCMD__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ucontrol_msgs
void
ucontrol_msgs__msg__ChassisCMD__Sequence__fini(ucontrol_msgs__msg__ChassisCMD__Sequence * array);

/// Create array of msg/ChassisCMD messages.
/**
 * It allocates the memory for the array and calls
 * ucontrol_msgs__msg__ChassisCMD__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ucontrol_msgs
ucontrol_msgs__msg__ChassisCMD__Sequence *
ucontrol_msgs__msg__ChassisCMD__Sequence__create(size_t size);

/// Destroy array of msg/ChassisCMD messages.
/**
 * It calls
 * ucontrol_msgs__msg__ChassisCMD__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ucontrol_msgs
void
ucontrol_msgs__msg__ChassisCMD__Sequence__destroy(ucontrol_msgs__msg__ChassisCMD__Sequence * array);

/// Check for msg/ChassisCMD message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ucontrol_msgs
bool
ucontrol_msgs__msg__ChassisCMD__Sequence__are_equal(const ucontrol_msgs__msg__ChassisCMD__Sequence * lhs, const ucontrol_msgs__msg__ChassisCMD__Sequence * rhs);

/// Copy an array of msg/ChassisCMD messages.
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
ROSIDL_GENERATOR_C_PUBLIC_ucontrol_msgs
bool
ucontrol_msgs__msg__ChassisCMD__Sequence__copy(
  const ucontrol_msgs__msg__ChassisCMD__Sequence * input,
  ucontrol_msgs__msg__ChassisCMD__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // UCONTROL_MSGS__MSG__DETAIL__CHASSIS_CMD__FUNCTIONS_H_