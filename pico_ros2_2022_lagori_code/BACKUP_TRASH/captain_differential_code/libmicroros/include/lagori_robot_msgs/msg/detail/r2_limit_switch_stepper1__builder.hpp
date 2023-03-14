// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lagori_robot_msgs:msg/R2LimitSwitchStepper1.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER1__BUILDER_HPP_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER1__BUILDER_HPP_

#include "lagori_robot_msgs/msg/detail/r2_limit_switch_stepper1__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace lagori_robot_msgs
{

namespace msg
{

namespace builder
{

class Init_R2LimitSwitchStepper1_stepper1_level
{
public:
  Init_R2LimitSwitchStepper1_stepper1_level()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::lagori_robot_msgs::msg::R2LimitSwitchStepper1 stepper1_level(::lagori_robot_msgs::msg::R2LimitSwitchStepper1::_stepper1_level_type arg)
  {
    msg_.stepper1_level = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lagori_robot_msgs::msg::R2LimitSwitchStepper1 msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::lagori_robot_msgs::msg::R2LimitSwitchStepper1>()
{
  return lagori_robot_msgs::msg::builder::Init_R2LimitSwitchStepper1_stepper1_level();
}

}  // namespace lagori_robot_msgs

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER1__BUILDER_HPP_
