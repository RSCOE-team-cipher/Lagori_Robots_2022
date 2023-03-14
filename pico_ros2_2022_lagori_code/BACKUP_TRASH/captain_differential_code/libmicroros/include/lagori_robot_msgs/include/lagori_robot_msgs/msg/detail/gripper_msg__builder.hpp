// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lagori_robot_msgs:msg/GripperMsg.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__GRIPPER_MSG__BUILDER_HPP_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__GRIPPER_MSG__BUILDER_HPP_

#include "lagori_robot_msgs/msg/detail/gripper_msg__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace lagori_robot_msgs
{

namespace msg
{

namespace builder
{

class Init_GripperMsg_three_close
{
public:
  explicit Init_GripperMsg_three_close(::lagori_robot_msgs::msg::GripperMsg & msg)
  : msg_(msg)
  {}
  ::lagori_robot_msgs::msg::GripperMsg three_close(::lagori_robot_msgs::msg::GripperMsg::_three_close_type arg)
  {
    msg_.three_close = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lagori_robot_msgs::msg::GripperMsg msg_;
};

class Init_GripperMsg_three_open
{
public:
  explicit Init_GripperMsg_three_open(::lagori_robot_msgs::msg::GripperMsg & msg)
  : msg_(msg)
  {}
  Init_GripperMsg_three_close three_open(::lagori_robot_msgs::msg::GripperMsg::_three_open_type arg)
  {
    msg_.three_open = std::move(arg);
    return Init_GripperMsg_three_close(msg_);
  }

private:
  ::lagori_robot_msgs::msg::GripperMsg msg_;
};

class Init_GripperMsg_two_close
{
public:
  explicit Init_GripperMsg_two_close(::lagori_robot_msgs::msg::GripperMsg & msg)
  : msg_(msg)
  {}
  Init_GripperMsg_three_open two_close(::lagori_robot_msgs::msg::GripperMsg::_two_close_type arg)
  {
    msg_.two_close = std::move(arg);
    return Init_GripperMsg_three_open(msg_);
  }

private:
  ::lagori_robot_msgs::msg::GripperMsg msg_;
};

class Init_GripperMsg_two_open
{
public:
  explicit Init_GripperMsg_two_open(::lagori_robot_msgs::msg::GripperMsg & msg)
  : msg_(msg)
  {}
  Init_GripperMsg_two_close two_open(::lagori_robot_msgs::msg::GripperMsg::_two_open_type arg)
  {
    msg_.two_open = std::move(arg);
    return Init_GripperMsg_two_close(msg_);
  }

private:
  ::lagori_robot_msgs::msg::GripperMsg msg_;
};

class Init_GripperMsg_one_close
{
public:
  explicit Init_GripperMsg_one_close(::lagori_robot_msgs::msg::GripperMsg & msg)
  : msg_(msg)
  {}
  Init_GripperMsg_two_open one_close(::lagori_robot_msgs::msg::GripperMsg::_one_close_type arg)
  {
    msg_.one_close = std::move(arg);
    return Init_GripperMsg_two_open(msg_);
  }

private:
  ::lagori_robot_msgs::msg::GripperMsg msg_;
};

class Init_GripperMsg_one_open
{
public:
  Init_GripperMsg_one_open()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GripperMsg_one_close one_open(::lagori_robot_msgs::msg::GripperMsg::_one_open_type arg)
  {
    msg_.one_open = std::move(arg);
    return Init_GripperMsg_one_close(msg_);
  }

private:
  ::lagori_robot_msgs::msg::GripperMsg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::lagori_robot_msgs::msg::GripperMsg>()
{
  return lagori_robot_msgs::msg::builder::Init_GripperMsg_one_open();
}

}  // namespace lagori_robot_msgs

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__GRIPPER_MSG__BUILDER_HPP_
