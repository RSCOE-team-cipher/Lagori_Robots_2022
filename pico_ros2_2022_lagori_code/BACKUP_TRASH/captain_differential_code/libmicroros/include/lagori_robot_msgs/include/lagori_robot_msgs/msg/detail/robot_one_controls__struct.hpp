// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from lagori_robot_msgs:msg/RobotOneControls.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__ROBOT_ONE_CONTROLS__STRUCT_HPP_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__ROBOT_ONE_CONTROLS__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__lagori_robot_msgs__msg__RobotOneControls __attribute__((deprecated))
#else
# define DEPRECATED__lagori_robot_msgs__msg__RobotOneControls __declspec(deprecated)
#endif

namespace lagori_robot_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RobotOneControls_
{
  using Type = RobotOneControls_<ContainerAllocator>;

  explicit RobotOneControls_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->rotor = 0l;
      this->feeder_up = 0l;
      this->feeder_down = 0l;
      this->angle_up = 0l;
      this->angle_down = 0l;
      this->servo = 0l;
      this->shoot = 0l;
    }
  }

  explicit RobotOneControls_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->rotor = 0l;
      this->feeder_up = 0l;
      this->feeder_down = 0l;
      this->angle_up = 0l;
      this->angle_down = 0l;
      this->servo = 0l;
      this->shoot = 0l;
    }
  }

  // field types and members
  using _rotor_type =
    int32_t;
  _rotor_type rotor;
  using _feeder_up_type =
    int32_t;
  _feeder_up_type feeder_up;
  using _feeder_down_type =
    int32_t;
  _feeder_down_type feeder_down;
  using _angle_up_type =
    int32_t;
  _angle_up_type angle_up;
  using _angle_down_type =
    int32_t;
  _angle_down_type angle_down;
  using _servo_type =
    int32_t;
  _servo_type servo;
  using _shoot_type =
    int32_t;
  _shoot_type shoot;

  // setters for named parameter idiom
  Type & set__rotor(
    const int32_t & _arg)
  {
    this->rotor = _arg;
    return *this;
  }
  Type & set__feeder_up(
    const int32_t & _arg)
  {
    this->feeder_up = _arg;
    return *this;
  }
  Type & set__feeder_down(
    const int32_t & _arg)
  {
    this->feeder_down = _arg;
    return *this;
  }
  Type & set__angle_up(
    const int32_t & _arg)
  {
    this->angle_up = _arg;
    return *this;
  }
  Type & set__angle_down(
    const int32_t & _arg)
  {
    this->angle_down = _arg;
    return *this;
  }
  Type & set__servo(
    const int32_t & _arg)
  {
    this->servo = _arg;
    return *this;
  }
  Type & set__shoot(
    const int32_t & _arg)
  {
    this->shoot = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    lagori_robot_msgs::msg::RobotOneControls_<ContainerAllocator> *;
  using ConstRawPtr =
    const lagori_robot_msgs::msg::RobotOneControls_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<lagori_robot_msgs::msg::RobotOneControls_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<lagori_robot_msgs::msg::RobotOneControls_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      lagori_robot_msgs::msg::RobotOneControls_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<lagori_robot_msgs::msg::RobotOneControls_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      lagori_robot_msgs::msg::RobotOneControls_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<lagori_robot_msgs::msg::RobotOneControls_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<lagori_robot_msgs::msg::RobotOneControls_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<lagori_robot_msgs::msg::RobotOneControls_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__lagori_robot_msgs__msg__RobotOneControls
    std::shared_ptr<lagori_robot_msgs::msg::RobotOneControls_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__lagori_robot_msgs__msg__RobotOneControls
    std::shared_ptr<lagori_robot_msgs::msg::RobotOneControls_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotOneControls_ & other) const
  {
    if (this->rotor != other.rotor) {
      return false;
    }
    if (this->feeder_up != other.feeder_up) {
      return false;
    }
    if (this->feeder_down != other.feeder_down) {
      return false;
    }
    if (this->angle_up != other.angle_up) {
      return false;
    }
    if (this->angle_down != other.angle_down) {
      return false;
    }
    if (this->servo != other.servo) {
      return false;
    }
    if (this->shoot != other.shoot) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotOneControls_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotOneControls_

// alias to use template instance with default allocator
using RobotOneControls =
  lagori_robot_msgs::msg::RobotOneControls_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace lagori_robot_msgs

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__ROBOT_ONE_CONTROLS__STRUCT_HPP_
