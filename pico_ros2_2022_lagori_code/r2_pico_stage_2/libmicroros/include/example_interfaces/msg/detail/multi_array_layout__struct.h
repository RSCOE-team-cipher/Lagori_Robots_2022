// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from example_interfaces:msg/MultiArrayLayout.idl
// generated code does not contain a copyright notice

#ifndef EXAMPLE_INTERFACES__MSG__DETAIL__MULTI_ARRAY_LAYOUT__STRUCT_H_
#define EXAMPLE_INTERFACES__MSG__DETAIL__MULTI_ARRAY_LAYOUT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'dim'
#include "example_interfaces/msg/detail/multi_array_dimension__struct.h"

// Struct defined in msg/MultiArrayLayout in the package example_interfaces.
typedef struct example_interfaces__msg__MultiArrayLayout
{
  example_interfaces__msg__MultiArrayDimension__Sequence dim;
  uint32_t data_offset;
} example_interfaces__msg__MultiArrayLayout;

// Struct for a sequence of example_interfaces__msg__MultiArrayLayout.
typedef struct example_interfaces__msg__MultiArrayLayout__Sequence
{
  example_interfaces__msg__MultiArrayLayout * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} example_interfaces__msg__MultiArrayLayout__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // EXAMPLE_INTERFACES__MSG__DETAIL__MULTI_ARRAY_LAYOUT__STRUCT_H_