// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from lagori_robot_msgs:msg/R2LimitSwitchStepper1.idl
// generated code does not contain a copyright notice
#include "lagori_robot_msgs/msg/detail/r2_limit_switch_stepper1__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
lagori_robot_msgs__msg__R2LimitSwitchStepper1__init(lagori_robot_msgs__msg__R2LimitSwitchStepper1 * msg)
{
  if (!msg) {
    return false;
  }
  // stepper1_level
  return true;
}

void
lagori_robot_msgs__msg__R2LimitSwitchStepper1__fini(lagori_robot_msgs__msg__R2LimitSwitchStepper1 * msg)
{
  if (!msg) {
    return;
  }
  // stepper1_level
}

lagori_robot_msgs__msg__R2LimitSwitchStepper1 *
lagori_robot_msgs__msg__R2LimitSwitchStepper1__create()
{
  lagori_robot_msgs__msg__R2LimitSwitchStepper1 * msg = (lagori_robot_msgs__msg__R2LimitSwitchStepper1 *)malloc(sizeof(lagori_robot_msgs__msg__R2LimitSwitchStepper1));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(lagori_robot_msgs__msg__R2LimitSwitchStepper1));
  bool success = lagori_robot_msgs__msg__R2LimitSwitchStepper1__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
lagori_robot_msgs__msg__R2LimitSwitchStepper1__destroy(lagori_robot_msgs__msg__R2LimitSwitchStepper1 * msg)
{
  if (msg) {
    lagori_robot_msgs__msg__R2LimitSwitchStepper1__fini(msg);
  }
  free(msg);
}


bool
lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence__init(lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  lagori_robot_msgs__msg__R2LimitSwitchStepper1 * data = NULL;
  if (size) {
    data = (lagori_robot_msgs__msg__R2LimitSwitchStepper1 *)calloc(size, sizeof(lagori_robot_msgs__msg__R2LimitSwitchStepper1));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = lagori_robot_msgs__msg__R2LimitSwitchStepper1__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        lagori_robot_msgs__msg__R2LimitSwitchStepper1__fini(&data[i - 1]);
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
lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence__fini(lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      lagori_robot_msgs__msg__R2LimitSwitchStepper1__fini(&array->data[i]);
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

lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence *
lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence__create(size_t size)
{
  lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence * array = (lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence *)malloc(sizeof(lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence__destroy(lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence * array)
{
  if (array) {
    lagori_robot_msgs__msg__R2LimitSwitchStepper1__Sequence__fini(array);
  }
  free(array);
}
