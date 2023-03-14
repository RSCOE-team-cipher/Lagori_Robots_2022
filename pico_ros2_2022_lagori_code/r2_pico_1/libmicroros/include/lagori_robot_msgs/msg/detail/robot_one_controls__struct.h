// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lagori_robot_msgs:msg/RobotOneControls.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__ROBOT_ONE_CONTROLS__STRUCT_H_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__ROBOT_ONE_CONTROLS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/RobotOneControls in the package lagori_robot_msgs.
typedef struct lagori_robot_msgs__msg__RobotOneControls
{
  int32_t rotor;
  int32_t feeder_up;
  int32_t feeder_down;
  int32_t angle_up;
  int32_t angle_down;
  int32_t servo;
  int32_t shoot;
} lagori_robot_msgs__msg__RobotOneControls;

// Struct for a sequence of lagori_robot_msgs__msg__RobotOneControls.
typedef struct lagori_robot_msgs__msg__RobotOneControls__Sequence
{
  lagori_robot_msgs__msg__RobotOneControls * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lagori_robot_msgs__msg__RobotOneControls__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__ROBOT_ONE_CONTROLS__STRUCT_H_
