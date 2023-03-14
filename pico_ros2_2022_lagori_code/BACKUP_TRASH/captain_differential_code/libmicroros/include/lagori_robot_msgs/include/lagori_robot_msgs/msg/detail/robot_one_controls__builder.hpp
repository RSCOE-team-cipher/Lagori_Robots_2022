// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lagori_robot_msgs:msg/RobotOneControls.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__ROBOT_ONE_CONTROLS__BUILDER_HPP_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__ROBOT_ONE_CONTROLS__BUILDER_HPP_

#include "lagori_robot_msgs/msg/detail/robot_one_controls__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace lagori_robot_msgs
{

namespace msg
{

namespace builder
{

class Init_RobotOneControls_shoot
{
public:
  explicit Init_RobotOneControls_shoot(::lagori_robot_msgs::msg::RobotOneControls & msg)
  : msg_(msg)
  {}
  ::lagori_robot_msgs::msg::RobotOneControls shoot(::lagori_robot_msgs::msg::RobotOneControls::_shoot_type arg)
  {
    msg_.shoot = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lagori_robot_msgs::msg::RobotOneControls msg_;
};

class Init_RobotOneControls_servo
{
public:
  explicit Init_RobotOneControls_servo(::lagori_robot_msgs::msg::RobotOneControls & msg)
  : msg_(msg)
  {}
  Init_RobotOneControls_shoot servo(::lagori_robot_msgs::msg::RobotOneControls::_servo_type arg)
  {
    msg_.servo = std::move(arg);
    return Init_RobotOneControls_shoot(msg_);
  }

private:
  ::lagori_robot_msgs::msg::RobotOneControls msg_;
};

class Init_RobotOneControls_angle_down
{
public:
  explicit Init_RobotOneControls_angle_down(::lagori_robot_msgs::msg::RobotOneControls & msg)
  : msg_(msg)
  {}
  Init_RobotOneControls_servo angle_down(::lagori_robot_msgs::msg::RobotOneControls::_angle_down_type arg)
  {
    msg_.angle_down = std::move(arg);
    return Init_RobotOneControls_servo(msg_);
  }

private:
  ::lagori_robot_msgs::msg::RobotOneControls msg_;
};

class Init_RobotOneControls_angle_up
{
public:
  explicit Init_RobotOneControls_angle_up(::lagori_robot_msgs::msg::RobotOneControls & msg)
  : msg_(msg)
  {}
  Init_RobotOneControls_angle_down angle_up(::lagori_robot_msgs::msg::RobotOneControls::_angle_up_type arg)
  {
    msg_.angle_up = std::move(arg);
    return Init_RobotOneControls_angle_down(msg_);
  }

private:
  ::lagori_robot_msgs::msg::RobotOneControls msg_;
};

class Init_RobotOneControls_feeder_down
{
public:
  explicit Init_RobotOneControls_feeder_down(::lagori_robot_msgs::msg::RobotOneControls & msg)
  : msg_(msg)
  {}
  Init_RobotOneControls_angle_up feeder_down(::lagori_robot_msgs::msg::RobotOneControls::_feeder_down_type arg)
  {
    msg_.feeder_down = std::move(arg);
    return Init_RobotOneControls_angle_up(msg_);
  }

private:
  ::lagori_robot_msgs::msg::RobotOneControls msg_;
};

class Init_RobotOneControls_feeder_up
{
public:
  explicit Init_RobotOneControls_feeder_up(::lagori_robot_msgs::msg::RobotOneControls & msg)
  : msg_(msg)
  {}
  Init_RobotOneControls_feeder_down feeder_up(::lagori_robot_msgs::msg::RobotOneControls::_feeder_up_type arg)
  {
    msg_.feeder_up = std::move(arg);
    return Init_RobotOneControls_feeder_down(msg_);
  }

private:
  ::lagori_robot_msgs::msg::RobotOneControls msg_;
};

class Init_RobotOneControls_rotor
{
public:
  Init_RobotOneControls_rotor()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotOneControls_feeder_up rotor(::lagori_robot_msgs::msg::RobotOneControls::_rotor_type arg)
  {
    msg_.rotor = std::move(arg);
    return Init_RobotOneControls_feeder_up(msg_);
  }

private:
  ::lagori_robot_msgs::msg::RobotOneControls msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::lagori_robot_msgs::msg::RobotOneControls>()
{
  return lagori_robot_msgs::msg::builder::Init_RobotOneControls_rotor();
}

}  // namespace lagori_robot_msgs

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__ROBOT_ONE_CONTROLS__BUILDER_HPP_
