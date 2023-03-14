// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from lagori_robot_msgs:msg/R2LimitSwitchStepper2.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER2__TRAITS_HPP_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER2__TRAITS_HPP_

#include "lagori_robot_msgs/msg/detail/r2_limit_switch_stepper2__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<lagori_robot_msgs::msg::R2LimitSwitchStepper2>()
{
  return "lagori_robot_msgs::msg::R2LimitSwitchStepper2";
}

template<>
inline const char * name<lagori_robot_msgs::msg::R2LimitSwitchStepper2>()
{
  return "lagori_robot_msgs/msg/R2LimitSwitchStepper2";
}

template<>
struct has_fixed_size<lagori_robot_msgs::msg::R2LimitSwitchStepper2>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<lagori_robot_msgs::msg::R2LimitSwitchStepper2>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<lagori_robot_msgs::msg::R2LimitSwitchStepper2>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER2__TRAITS_HPP_