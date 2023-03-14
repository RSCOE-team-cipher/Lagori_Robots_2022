// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from lagori_robot_msgs:msg/StepperMsg.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__STEPPER_MSG__TRAITS_HPP_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__STEPPER_MSG__TRAITS_HPP_

#include "lagori_robot_msgs/msg/detail/stepper_msg__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<lagori_robot_msgs::msg::StepperMsg>()
{
  return "lagori_robot_msgs::msg::StepperMsg";
}

template<>
inline const char * name<lagori_robot_msgs::msg::StepperMsg>()
{
  return "lagori_robot_msgs/msg/StepperMsg";
}

template<>
struct has_fixed_size<lagori_robot_msgs::msg::StepperMsg>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<lagori_robot_msgs::msg::StepperMsg>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<lagori_robot_msgs::msg::StepperMsg>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__STEPPER_MSG__TRAITS_HPP_
