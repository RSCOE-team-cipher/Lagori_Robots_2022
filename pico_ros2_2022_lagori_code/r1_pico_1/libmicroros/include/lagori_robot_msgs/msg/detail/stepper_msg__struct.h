// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lagori_robot_msgs:msg/StepperMsg.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__STEPPER_MSG__STRUCT_H_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__STEPPER_MSG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/StepperMsg in the package lagori_robot_msgs.
typedef struct lagori_robot_msgs__msg__StepperMsg
{
  int32_t one_up;
  int32_t one_down;
  int32_t two_up;
  int32_t two_down;
  int32_t three_up;
  int32_t three_down;
} lagori_robot_msgs__msg__StepperMsg;

// Struct for a sequence of lagori_robot_msgs__msg__StepperMsg.
typedef struct lagori_robot_msgs__msg__StepperMsg__Sequence
{
  lagori_robot_msgs__msg__StepperMsg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lagori_robot_msgs__msg__StepperMsg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__STEPPER_MSG__STRUCT_H_
