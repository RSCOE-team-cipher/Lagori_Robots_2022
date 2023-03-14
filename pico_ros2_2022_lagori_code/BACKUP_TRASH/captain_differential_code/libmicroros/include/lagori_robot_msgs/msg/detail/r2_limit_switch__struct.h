// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lagori_robot_msgs:msg/R2LimitSwitch.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH__STRUCT_H_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/R2LimitSwitch in the package lagori_robot_msgs.
typedef struct lagori_robot_msgs__msg__R2LimitSwitch
{
  int32_t stepper1_level1;
  int32_t stepper1_level2;
  int32_t stepper1_level3;
  int32_t stepper1_level4;
  int32_t stepper1_level5;
  int32_t stepper2_level1;
  int32_t stepper2_level2;
  int32_t stepper2_level3;
  int32_t stepper2_level4;
  int32_t stepper2_level5;
  int32_t stepper3_level1;
  int32_t stepper3_level2;
  int32_t stepper3_level3;
  int32_t stepper3_level4;
  int32_t stepper3_level5;
} lagori_robot_msgs__msg__R2LimitSwitch;

// Struct for a sequence of lagori_robot_msgs__msg__R2LimitSwitch.
typedef struct lagori_robot_msgs__msg__R2LimitSwitch__Sequence
{
  lagori_robot_msgs__msg__R2LimitSwitch * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lagori_robot_msgs__msg__R2LimitSwitch__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH__STRUCT_H_
