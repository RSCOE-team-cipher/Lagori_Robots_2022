// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lagori_robot_msgs:msg/R2LimitSwitchStepper2.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER2__BUILDER_HPP_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER2__BUILDER_HPP_

#include "lagori_robot_msgs/msg/detail/r2_limit_switch_stepper2__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace lagori_robot_msgs
{

namespace msg
{

namespace builder
{

class Init_R2LimitSwitchStepper2_stepper2_level
{
public:
  Init_R2LimitSwitchStepper2_stepper2_level()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::lagori_robot_msgs::msg::R2LimitSwitchStepper2 stepper2_level(::lagori_robot_msgs::msg::R2LimitSwitchStepper2::_stepper2_level_type arg)
  {
    msg_.stepper2_level = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lagori_robot_msgs::msg::R2LimitSwitchStepper2 msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::lagori_robot_msgs::msg::R2LimitSwitchStepper2>()
{
  return lagori_robot_msgs::msg::builder::Init_R2LimitSwitchStepper2_stepper2_level();
}

}  // namespace lagori_robot_msgs

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER2__BUILDER_HPP_
