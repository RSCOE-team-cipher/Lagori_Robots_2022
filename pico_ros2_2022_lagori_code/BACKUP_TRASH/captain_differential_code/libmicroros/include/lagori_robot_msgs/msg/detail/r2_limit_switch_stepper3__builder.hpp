// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lagori_robot_msgs:msg/R2LimitSwitchStepper3.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER3__BUILDER_HPP_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER3__BUILDER_HPP_

#include "lagori_robot_msgs/msg/detail/r2_limit_switch_stepper3__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace lagori_robot_msgs
{

namespace msg
{

namespace builder
{

class Init_R2LimitSwitchStepper3_stepper3_level
{
public:
  Init_R2LimitSwitchStepper3_stepper3_level()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::lagori_robot_msgs::msg::R2LimitSwitchStepper3 stepper3_level(::lagori_robot_msgs::msg::R2LimitSwitchStepper3::_stepper3_level_type arg)
  {
    msg_.stepper3_level = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lagori_robot_msgs::msg::R2LimitSwitchStepper3 msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::lagori_robot_msgs::msg::R2LimitSwitchStepper3>()
{
  return lagori_robot_msgs::msg::builder::Init_R2LimitSwitchStepper3_stepper3_level();
}

}  // namespace lagori_robot_msgs

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER3__BUILDER_HPP_
