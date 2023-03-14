// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lagori_robot_msgs:msg/R2LimitSwitchStepper1.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER1__STRUCT_H_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER1__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/R2LimitSwitchStepper1 in the package lagori_robot_msgs.
typedef struct lagori_robot_msgs__msg__R2LimitSwitchStepper1
{
  int32_t stepper1_level[5];
} lagori_robot_msgs__msg__R2LimitSwitchStepper1;

// Struct for a sequence of lagori_robot_msgs__msg__R2LimitSwitchStepper1.
typedef struct lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence
{
  lagori_robot_msgs__msg__R2LimitSwitchStepper1 * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER1__STRUCT_H_
