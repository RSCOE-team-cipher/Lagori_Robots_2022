// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lagori_robot_msgs:msg/GripperMsg.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__GRIPPER_MSG__STRUCT_H_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__GRIPPER_MSG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/GripperMsg in the package lagori_robot_msgs.
typedef struct lagori_robot_msgs__msg__GripperMsg
{
  int32_t one_open;
  int32_t one_close;
  int32_t two_open;
  int32_t two_close;
  int32_t three_open;
  int32_t three_close;
} lagori_robot_msgs__msg__GripperMsg;

// Struct for a sequence of lagori_robot_msgs__msg__GripperMsg.
typedef struct lagori_robot_msgs__msg__GripperMsg__Sequence
{
  lagori_robot_msgs__msg__GripperMsg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lagori_robot_msgs__msg__GripperMsg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__GRIPPER_MSG__STRUCT_H_
