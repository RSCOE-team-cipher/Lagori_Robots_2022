// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lagori_robot_msgs:msg/StepperMsg.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__STEPPER_MSG__BUILDER_HPP_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__STEPPER_MSG__BUILDER_HPP_

#include "lagori_robot_msgs/msg/detail/stepper_msg__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace lagori_robot_msgs
{

namespace msg
{

namespace builder
{

class Init_StepperMsg_three_down
{
public:
  explicit Init_StepperMsg_three_down(::lagori_robot_msgs::msg::StepperMsg & msg)
  : msg_(msg)
  {}
  ::lagori_robot_msgs::msg::StepperMsg three_down(::lagori_robot_msgs::msg::StepperMsg::_three_down_type arg)
  {
    msg_.three_down = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lagori_robot_msgs::msg::StepperMsg msg_;
};

class Init_StepperMsg_three_up
{
public:
  explicit Init_StepperMsg_three_up(::lagori_robot_msgs::msg::StepperMsg & msg)
  : msg_(msg)
  {}
  Init_StepperMsg_three_down three_up(::lagori_robot_msgs::msg::StepperMsg::_three_up_type arg)
  {
    msg_.three_up = std::move(arg);
    return Init_StepperMsg_three_down(msg_);
  }

private:
  ::lagori_robot_msgs::msg::StepperMsg msg_;
};

class Init_StepperMsg_two_down
{
public:
  explicit Init_StepperMsg_two_down(::lagori_robot_msgs::msg::StepperMsg & msg)
  : msg_(msg)
  {}
  Init_StepperMsg_three_up two_down(::lagori_robot_msgs::msg::StepperMsg::_two_down_type arg)
  {
    msg_.two_down = std::move(arg);
    return Init_StepperMsg_three_up(msg_);
  }

private:
  ::lagori_robot_msgs::msg::StepperMsg msg_;
};

class Init_StepperMsg_two_up
{
public:
  explicit Init_StepperMsg_two_up(::lagori_robot_msgs::msg::StepperMsg & msg)
  : msg_(msg)
  {}
  Init_StepperMsg_two_down two_up(::lagori_robot_msgs::msg::StepperMsg::_two_up_type arg)
  {
    msg_.two_up = std::move(arg);
    return Init_StepperMsg_two_down(msg_);
  }

private:
  ::lagori_robot_msgs::msg::StepperMsg msg_;
};

class Init_StepperMsg_one_down
{
public:
  explicit Init_StepperMsg_one_down(::lagori_robot_msgs::msg::StepperMsg & msg)
  : msg_(msg)
  {}
  Init_StepperMsg_two_up one_down(::lagori_robot_msgs::msg::StepperMsg::_one_down_type arg)
  {
    msg_.one_down = std::move(arg);
    return Init_StepperMsg_two_up(msg_);
  }

private:
  ::lagori_robot_msgs::msg::StepperMsg msg_;
};

class Init_StepperMsg_one_up
{
public:
  Init_StepperMsg_one_up()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_StepperMsg_one_down one_up(::lagori_robot_msgs::msg::StepperMsg::_one_up_type arg)
  {
    msg_.one_up = std::move(arg);
    return Init_StepperMsg_one_down(msg_);
  }

private:
  ::lagori_robot_msgs::msg::StepperMsg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::lagori_robot_msgs::msg::StepperMsg>()
{
  return lagori_robot_msgs::msg::builder::Init_StepperMsg_one_up();
}

}  // namespace lagori_robot_msgs

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__STEPPER_MSG__BUILDER_HPP_
