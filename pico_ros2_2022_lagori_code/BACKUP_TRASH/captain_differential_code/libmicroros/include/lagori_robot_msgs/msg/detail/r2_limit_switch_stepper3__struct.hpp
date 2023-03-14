// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from lagori_robot_msgs:msg/R2LimitSwitchStepper3.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER3__STRUCT_HPP_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER3__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__lagori_robot_msgs__msg__R2LimitSwitchStepper3 __attribute__((deprecated))
#else
# define DEPRECATED__lagori_robot_msgs__msg__R2LimitSwitchStepper3 __declspec(deprecated)
#endif

namespace lagori_robot_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct R2LimitSwitchStepper3_
{
  using Type = R2LimitSwitchStepper3_<ContainerAllocator>;

  explicit R2LimitSwitchStepper3_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<int32_t, 5>::iterator, int32_t>(this->stepper3_level.begin(), this->stepper3_level.end(), 0l);
    }
  }

  explicit R2LimitSwitchStepper3_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stepper3_level(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<int32_t, 5>::iterator, int32_t>(this->stepper3_level.begin(), this->stepper3_level.end(), 0l);
    }
  }

  // field types and members
  using _stepper3_level_type =
    std::array<int32_t, 5>;
  _stepper3_level_type stepper3_level;

  // setters for named parameter idiom
  Type & set__stepper3_level(
    const std::array<int32_t, 5> & _arg)
  {
    this->stepper3_level = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    lagori_robot_msgs::msg::R2LimitSwitchStepper3_<ContainerAllocator> *;
  using ConstRawPtr =
    const lagori_robot_msgs::msg::R2LimitSwitchStepper3_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper3_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper3_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      lagori_robot_msgs::msg::R2LimitSwitchStepper3_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper3_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      lagori_robot_msgs::msg::R2LimitSwitchStepper3_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper3_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper3_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper3_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__lagori_robot_msgs__msg__R2LimitSwitchStepper3
    std::shared_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper3_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__lagori_robot_msgs__msg__R2LimitSwitchStepper3
    std::shared_ptr<lagori_robot_msgs::msg::R2LimitSwitchStepper3_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const R2LimitSwitchStepper3_ & other) const
  {
    if (this->stepper3_level != other.stepper3_level) {
      return false;
    }
    return true;
  }
  bool operator!=(const R2LimitSwitchStepper3_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct R2LimitSwitchStepper3_

// alias to use template instance with default allocator
using R2LimitSwitchStepper3 =
  lagori_robot_msgs::msg::R2LimitSwitchStepper3_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace lagori_robot_msgs

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH_STEPPER3__STRUCT_HPP_
