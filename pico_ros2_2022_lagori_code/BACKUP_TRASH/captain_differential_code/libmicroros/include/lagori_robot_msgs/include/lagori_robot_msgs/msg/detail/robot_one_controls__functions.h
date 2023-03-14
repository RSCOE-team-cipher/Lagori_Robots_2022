// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from lagori_robot_msgs:msg/RobotOneControls.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__ROBOT_ONE_CONTROLS__FUNCTIONS_H_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__ROBOT_ONE_CONTROLS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "lagori_robot_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "lagori_robot_msgs/msg/detail/robot_one_controls__struct.h"

/// Initialize msg/RobotOneControls message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * lagori_robot_msgs__msg__RobotOneControls
 * )) before or use
 * lagori_robot_msgs__msg__RobotOneControls__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_lagori_robot_msgs
bool
lagori_robot_msgs__msg__RobotOneControls__init(lagori_robot_msgs__msg__RobotOneControls * msg);

/// Finalize msg/RobotOneControls message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lagori_robot_msgs
void
lagori_robot_msgs__msg__RobotOneControls__fini(lagori_robot_msgs__msg__RobotOneControls * msg);

/// Create msg/RobotOneControls message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * lagori_robot_msgs__msg__RobotOneControls__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_lagori_robot_msgs
lagori_robot_msgs__msg__RobotOneControls *
lagori_robot_msgs__msg__RobotOneControls__create();

/// Destroy msg/RobotOneControls message.
/**
 * It calls
 * lagori_robot_msgs__msg__RobotOneControls__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lagori_robot_msgs
void
lagori_robot_msgs__msg__RobotOneControls__destroy(lagori_robot_msgs__msg__RobotOneControls * msg);


/// Initialize array of msg/RobotOneControls messages.
/**
 * It allocates the memory for the number of elements and calls
 * lagori_robot_msgs__msg__RobotOneControls__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_lagori_robot_msgs
bool
lagori_robot_msgs__msg__RobotOneControls__Sequence__init(lagori_robot_msgs__msg__RobotOneControls__Sequence * array, size_t size);

/// Finalize array of msg/RobotOneControls messages.
/**
 * It calls
 * lagori_robot_msgs__msg__RobotOneControls__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lagori_robot_msgs
void
lagori_robot_msgs__msg__RobotOneControls__Sequence__fini(lagori_robot_msgs__msg__RobotOneControls__Sequence * array);

/// Create array of msg/RobotOneControls messages.
/**
 * It allocates the memory for the array and calls
 * lagori_robot_msgs__msg__RobotOneControls__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_lagori_robot_msgs
lagori_robot_msgs__msg__RobotOneControls__Sequence *
lagori_robot_msgs__msg__RobotOneControls__Sequence__create(size_t size);

/// Destroy array of msg/RobotOneControls messages.
/**
 * It calls
 * lagori_robot_msgs__msg__RobotOneControls__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_lagori_robot_msgs
void
lagori_robot_msgs__msg__RobotOneControls__Sequence__destroy(lagori_robot_msgs__msg__RobotOneControls__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__ROBOT_ONE_CONTROLS__FUNCTIONS_H_
