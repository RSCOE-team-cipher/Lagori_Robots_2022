// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from lagori_robot_msgs:msg/R2LimitSwitchStepper2.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER2__STRUCT_HPP_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER2__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__lagori_robot_msgs__msg__R2LimitSwitchStepper2 __attribute__((deprecated))
#else
# define DEPRECATED__lagori_robot_msgs__msg__R2LimitSwitchStepper2 __declspec(deprecated)
#endif

namespace lagori_robot_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct R2LimitSwitchStepper2_
{
  using Type = R2LimitSwitchStepper2_<ContainerAllocator>;

  explicit R2LimitSwitchStepper2_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<int32_t, 5>::iterator, int32_t>(this->stepper2_level.begin(), this->stepper2_level.end(), 0l);
    }
  }

  explicit R2LimitSwitchStepper2_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stepper2_level(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<int32_t, 5>::iterator, int32_t>(this->stepper2_level.begin(), this->stepper2_level.end(), 0l);
    }
  }

  // field types and members
  using _stepper2_level_type =
    std::array<int32_t, 5>;
  _stepper2_level_type stepper2_level;

  // setters for named parameter idiom
  Type & set__stepper2_level(
    const std::array<int32_t, 5> & _arg)
  {
    this->stepper2_level = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    lagori_robot_msgs::msg::R2LimitSwitchStepper2_<ContainerAllocator> *;
  using ConstRawPtr =
    const lagori_robot_msgs::msg::R2LimitSwitchStepper2_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper2_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper2_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      lagori_robot_msgs::msg::R2LimitSwitchStepper2_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper2_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      lagori_robot_msgs::msg::R2LimitSwitchStepper2_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper2_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper2_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper2_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__lagori_robot_msgs__msg__R2LimitSwitchStepper2
    std::shared_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper2_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__lagori_robot_msgs__msg__R2LimitSwitchStepper2
    std::shared_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper2_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const R2LimitSwitchStepper2_ & other) const
  {
    if (this->stepper2_level != other.stepper2_level) {
      return false;
    }
    return true;
  }
  bool operator!=(const R2LimitSwitchStepper2_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct R2LimitSwitchStepper2_

// alias to use template instance with default allocator
using R2LimitSwitchStepper2 =
  lagori_robot_msgs::msg::R2LimitSwitchStepper2_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace lagori_robot_msgs

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER2__STRUCT_HPP_
