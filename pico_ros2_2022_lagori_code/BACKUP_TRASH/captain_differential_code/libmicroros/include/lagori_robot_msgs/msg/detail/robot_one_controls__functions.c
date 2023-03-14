// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from lagori_robot_msgs:msg/RobotOneControls.idl
// generated code does not contain a copyright notice
#include "lagori_robot_msgs/msg/detail/robot_one_controls__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
lagori_robot_msgs__msg__RobotOneControls__init(lagori_robot_msgs__msg__RobotOneControls * msg)
{
  if (!msg) {
    return false;
  }
  // rotor
  // feeder_up
  // feeder_down
  // angle_up
  // angle_down
  // servo
  // shoot
  return true;
}

void
lagori_robot_msgs__msg__RobotOneControls__fini(lagori_robot_msgs__msg__RobotOneControls * msg)
{
  if (!msg) {
    return;
  }
  // rotor
  // feeder_up
  // feeder_down
  // angle_up
  // angle_down
  // servo
  // shoot
}

lagori_robot_msgs__msg__RobotOneControls *
lagori_robot_msgs__msg__RobotOneControls__create()
{
  lagori_robot_msgs__msg__RobotOneControls * msg = (lagori_robot_msgs__msg__RobotOneControls *)malloc(sizeof(lagori_robot_msgs__msg__RobotOneControls));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(lagori_robot_msgs__msg__RobotOneControls));
  bool success = lagori_robot_msgs__msg__RobotOneControls__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
lagori_robot_msgs__msg__RobotOneControls__destroy(lagori_robot_msgs__msg__RobotOneControls * msg)
{
  if (msg) {
    lagori_robot_msgs__msg__RobotOneControls__fini(msg);
  }
  free(msg);
}


bool
lagori_robot_msgs__msg__RobotOneControls__Sequence__init(lagori_robot_msgs__msg__RobotOneControls__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  lagori_robot_msgs__msg__RobotOneControls * data = NULL;
  if (size) {
    data = (lagori_robot_msgs__msg__RobotOneControls *)calloc(size, sizeof(lagori_robot_msgs__msg__RobotOneControls));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = lagori_robot_msgs__msg__RobotOneControls__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        lagori_robot_msgs__msg__RobotOneControls__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
lagori_robot_msgs__msg__RobotOneControls__Sequence__fini(lagori_robot_msgs__msg__RobotOneControls__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      lagori_robot_msgs__msg__RobotOneControls__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

lagori_robot_msgs__msg__RobotOneControls__Sequence *
lagori_robot_msgs__msg__RobotOneControls__Sequence__create(size_t size)
{
  lagori_robot_msgs__msg__RobotOneControls__Sequence * array = (lagori_robot_msgs__msg__RobotOneControls__Sequence *)malloc(sizeof(lagori_robot_msgs__msg__RobotOneControls__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = lagori_robot_msgs__msg__RobotOneControls__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
lagori_robot_msgs__msg__RobotOneControls__Sequence__destroy(lagori_robot_msgs__msg__RobotOneControls__Sequence * array)
{
  if (array) {
    lagori_robot_msgs__msg__RobotOneControls__Sequence__fini(array);
  }
  free(array);
}
