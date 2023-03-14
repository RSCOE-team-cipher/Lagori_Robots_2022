// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from lagori_robot_msgs:msg/R2LimitSwitch.idl
// generated code does not contain a copyright notice
#include "lagori_robot_msgs/msg/detail/r2_limit_switch__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
lagori_robot_msgs__msg__R2LimitSwitch__init(lagori_robot_msgs__msg__R2LimitSwitch * msg)
{
  if (!msg) {
    return false;
  }
  // stepper1_level1
  // stepper1_level2
  // stepper1_level3
  // stepper1_level4
  // stepper1_level5
  // stepper2_level1
  // stepper2_level2
  // stepper2_level3
  // stepper2_level4
  // stepper2_level5
  // stepper3_level1
  // stepper3_level2
  // stepper3_level3
  // stepper3_level4
  // stepper3_level5
  return true;
}

void
lagori_robot_msgs__msg__R2LimitSwitch__fini(lagori_robot_msgs__msg__R2LimitSwitch * msg)
{
  if (!msg) {
    return;
  }
  // stepper1_level1
  // stepper1_level2
  // stepper1_level3
  // stepper1_level4
  // stepper1_level5
  // stepper2_level1
  // stepper2_level2
  // stepper2_level3
  // stepper2_level4
  // stepper2_level5
  // stepper3_level1
  // stepper3_level2
  // stepper3_level3
  // stepper3_level4
  // stepper3_level5
}

lagori_robot_msgs__msg__R2LimitSwitch *
lagori_robot_msgs__msg__R2LimitSwitch__create()
{
  lagori_robot_msgs__msg__R2LimitSwitch * msg = (lagori_robot_msgs__msg__R2LimitSwitch *)malloc(sizeof(lagori_robot_msgs__msg__R2LimitSwitch));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(lagori_robot_msgs__msg__R2LimitSwitch));
  bool success = lagori_robot_msgs__msg__R2LimitSwitch__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
lagori_robot_msgs__msg__R2LimitSwitch__destroy(lagori_robot_msgs__msg__R2LimitSwitch * msg)
{
  if (msg) {
    lagori_robot_msgs__msg__R2LimitSwitch__fini(msg);
  }
  free(msg);
}


bool
lagori_robot_msgs__msg__R2LimitSwitch__Sequence__init(lagori_robot_msgs__msg__R2LimitSwitch__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  lagori_robot_msgs__msg__R2LimitSwitch * data = NULL;
  if (size) {
    data = (lagori_robot_msgs__msg__R2LimitSwitch *)calloc(size, sizeof(lagori_robot_msgs__msg__R2LimitSwitch));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = lagori_robot_msgs__msg__R2LimitSwitch__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        lagori_robot_msgs__msg__R2LimitSwitch__fini(&data[i - 1]);
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
lagori_robot_msgs__msg__R2LimitSwitch__Sequence__fini(lagori_robot_msgs__msg__R2LimitSwitch__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      lagori_robot_msgs__msg__R2LimitSwitch__fini(&array->data[i]);
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

lagori_robot_msgs__msg__R2LimitSwitch__Sequence *
lagori_robot_msgs__msg__R2LimitSwitch__Sequence__create(size_t size)
{
  lagori_robot_msgs__msg__R2LimitSwitch__Sequence * array = (lagori_robot_msgs__msg__R2LimitSwitch__Sequence *)malloc(sizeof(lagori_robot_msgs__msg__R2LimitSwitch__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = lagori_robot_msgs__msg__R2LimitSwitch__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
lagori_robot_msgs__msg__R2LimitSwitch__Sequence__destroy(lagori_robot_msgs__msg__R2LimitSwitch__Sequence * array)
{
  if (array) {
    lagori_robot_msgs__msg__R2LimitSwitch__Sequence__fini(array);
  }
  free(array);
}
