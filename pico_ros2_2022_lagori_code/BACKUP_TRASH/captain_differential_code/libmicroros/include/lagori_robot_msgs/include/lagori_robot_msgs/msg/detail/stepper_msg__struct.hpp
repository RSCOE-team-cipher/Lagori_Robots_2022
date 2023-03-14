// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from lagori_robot_msgs:msg/StepperMsg.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__STEPPER_MSG__STRUCT_HPP_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__STEPPER_MSG__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__lagori_robot_msgs__msg__StepperMsg __attribute__((deprecated))
#else
# define DEPRECATED__lagori_robot_msgs__msg__StepperMsg __declspec(deprecated)
#endif

namespace lagori_robot_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct StepperMsg_
{
  using Type = StepperMsg_<ContainerAllocator>;

  explicit StepperMsg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->one_up = 0l;
      this->one_down = 0l;
      this->two_up = 0l;
      this->two_down = 0l;
      this->three_up = 0l;
      this->three_down = 0l;
    }
  }

  explicit StepperMsg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->one_up = 0l;
      this->one_down = 0l;
      this->two_up = 0l;
      this->two_down = 0l;
      this->three_up = 0l;
      this->three_down = 0l;
    }
  }

  // field types and members
  using _one_up_type =
    int32_t;
  _one_up_type one_up;
  using _one_down_type =
    int32_t;
  _one_down_type one_down;
  using _two_up_type =
    int32_t;
  _two_up_type two_up;
  using _two_down_type =
    int32_t;
  _two_down_type two_down;
  using _three_up_type =
    int32_t;
  _three_up_type three_up;
  using _three_down_type =
    int32_t;
  _three_down_type three_down;

  // setters for named parameter idiom
  Type & set__one_up(
    const int32_t & _arg)
  {
    this->one_up = _arg;
    return *this;
  }
  Type & set__one_down(
    const int32_t & _arg)
  {
    this->one_down = _arg;
    return *this;
  }
  Type & set__two_up(
    const int32_t & _arg)
  {
    this->two_up = _arg;
    return *this;
  }
  Type & set__two_down(
    const int32_t & _arg)
  {
    this->two_down = _arg;
    return *this;
  }
  Type & set__three_up(
    const int32_t & _arg)
  {
    this->three_up = _arg;
    return *this;
  }
  Type & set__three_down(
    const int32_t & _arg)
  {
    this->three_down = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    lagori_robot_msgs::msg::StepperMsg_<ContainerAllocator> *;
  using ConstRawPtr =
    const lagori_robot_msgs::msg::StepperMsg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<lagori_robot_msgs::msg::StepperMsg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<lagori_robot_msgs::msg::StepperMsg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      lagori_robot_msgs::msg::StepperMsg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<lagori_robot_msgs::msg::StepperMsg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      lagori_robot_msgs::msg::StepperMsg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<lagori_robot_msgs::msg::StepperMsg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<lagori_robot_msgs::msg::StepperMsg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<lagori_robot_msgs::msg::StepperMsg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__lagori_robot_msgs__msg__StepperMsg
    std::shared_ptr<lagori_robot_msgs::msg::StepperMsg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__lagori_robot_msgs__msg__StepperMsg
    std::shared_ptr<lagori_robot_msgs::msg::StepperMsg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const StepperMsg_ & other) const
  {
    if (this->one_up != other.one_up) {
      return false;
    }
    if (this->one_down != other.one_down) {
      return false;
    }
    if (this->two_up != other.two_up) {
      return false;
    }
    if (this->two_down != other.two_down) {
      return false;
    }
    if (this->three_up != other.three_up) {
      return false;
    }
    if (this->three_down != other.three_down) {
      return false;
    }
    return true;
  }
  bool operator!=(const StepperMsg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct StepperMsg_

// alias to use template instance with default allocator
using StepperMsg =
  lagori_robot_msgs::msg::StepperMsg_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace lagori_robot_msgs

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__STEPPER_MSG__STRUCT_HPP_
