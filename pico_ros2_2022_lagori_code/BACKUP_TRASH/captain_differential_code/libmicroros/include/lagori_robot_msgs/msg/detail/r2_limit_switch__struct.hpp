// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from lagori_robot_msgs:msg/R2LimitSwitch.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH__STRUCT_HPP_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__lagori_robot_msgs__msg__R2LimitSwitch __attribute__((deprecated))
#else
# define DEPRECATED__lagori_robot_msgs__msg__R2LimitSwitch __declspec(deprecated)
#endif

namespace lagori_robot_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct R2LimitSwitch_
{
  using Type = R2LimitSwitch_<ContainerAllocator>;

  explicit R2LimitSwitch_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->stepper1_level1 = 0l;
      this->stepper1_level2 = 0l;
      this->stepper1_level3 = 0l;
      this->stepper1_level4 = 0l;
      this->stepper1_level5 = 0l;
      this->stepper2_level1 = 0l;
      this->stepper2_level2 = 0l;
      this->stepper2_level3 = 0l;
      this->stepper2_level4 = 0l;
      this->stepper2_level5 = 0l;
      this->stepper3_level1 = 0l;
      this->stepper3_level2 = 0l;
      this->stepper3_level3 = 0l;
      this->stepper3_level4 = 0l;
      this->stepper3_level5 = 0l;
    }
  }

  explicit R2LimitSwitch_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->stepper1_level1 = 0l;
      this->stepper1_level2 = 0l;
      this->stepper1_level3 = 0l;
      this->stepper1_level4 = 0l;
      this->stepper1_level5 = 0l;
      this->stepper2_level1 = 0l;
      this->stepper2_level2 = 0l;
      this->stepper2_level3 = 0l;
      this->stepper2_level4 = 0l;
      this->stepper2_level5 = 0l;
      this->stepper3_level1 = 0l;
      this->stepper3_level2 = 0l;
      this->stepper3_level3 = 0l;
      this->stepper3_level4 = 0l;
      this->stepper3_level5 = 0l;
    }
  }

  // field types and members
  using _stepper1_level1_type =
    int32_t;
  _stepper1_level1_type stepper1_level1;
  using _stepper1_level2_type =
    int32_t;
  _stepper1_level2_type stepper1_level2;
  using _stepper1_level3_type =
    int32_t;
  _stepper1_level3_type stepper1_level3;
  using _stepper1_level4_type =
    int32_t;
  _stepper1_level4_type stepper1_level4;
  using _stepper1_level5_type =
    int32_t;
  _stepper1_level5_type stepper1_level5;
  using _stepper2_level1_type =
    int32_t;
  _stepper2_level1_type stepper2_level1;
  using _stepper2_level2_type =
    int32_t;
  _stepper2_level2_type stepper2_level2;
  using _stepper2_level3_type =
    int32_t;
  _stepper2_level3_type stepper2_level3;
  using _stepper2_level4_type =
    int32_t;
  _stepper2_level4_type stepper2_level4;
  using _stepper2_level5_type =
    int32_t;
  _stepper2_level5_type stepper2_level5;
  using _stepper3_level1_type =
    int32_t;
  _stepper3_level1_type stepper3_level1;
  using _stepper3_level2_type =
    int32_t;
  _stepper3_level2_type stepper3_level2;
  using _stepper3_level3_type =
    int32_t;
  _stepper3_level3_type stepper3_level3;
  using _stepper3_level4_type =
    int32_t;
  _stepper3_level4_type stepper3_level4;
  using _stepper3_level5_type =
    int32_t;
  _stepper3_level5_type stepper3_level5;

  // setters for named parameter idiom
  Type & set__stepper1_level1(
    const int32_t & _arg)
  {
    this->stepper1_level1 = _arg;
    return *this;
  }
  Type & set__stepper1_level2(
    const int32_t & _arg)
  {
    this->stepper1_level2 = _arg;
    return *this;
  }
  Type & set__stepper1_level3(
    const int32_t & _arg)
  {
    this->stepper1_level3 = _arg;
    return *this;
  }
  Type & set__stepper1_level4(
    const int32_t & _arg)
  {
    this->stepper1_level4 = _arg;
    return *this;
  }
  Type & set__stepper1_level5(
    const int32_t & _arg)
  {
    this->stepper1_level5 = _arg;
    return *this;
  }
  Type & set__stepper2_level1(
    const int32_t & _arg)
  {
    this->stepper2_level1 = _arg;
    return *this;
  }
  Type & set__stepper2_level2(
    const int32_t & _arg)
  {
    this->stepper2_level2 = _arg;
    return *this;
  }
  Type & set__stepper2_level3(
    const int32_t & _arg)
  {
    this->stepper2_level3 = _arg;
    return *this;
  }
  Type & set__stepper2_level4(
    const int32_t & _arg)
  {
    this->stepper2_level4 = _arg;
    return *this;
  }
  Type & set__stepper2_level5(
    const int32_t & _arg)
  {
    this->stepper2_level5 = _arg;
    return *this;
  }
  Type & set__stepper3_level1(
    const int32_t & _arg)
  {
    this->stepper3_level1 = _arg;
    return *this;
  }
  Type & set__stepper3_level2(
    const int32_t & _arg)
  {
    this->stepper3_level2 = _arg;
    return *this;
  }
  Type & set__stepper3_level3(
    const int32_t & _arg)
  {
    this->stepper3_level3 = _arg;
    return *this;
  }
  Type & set__stepper3_level4(
    const int32_t & _arg)
  {
    this->stepper3_level4 = _arg;
    return *this;
  }
  Type & set__stepper3_level5(
    const int32_t & _arg)
  {
    this->stepper3_level5 = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    lagori_robot_msgs::msg::R2LimitSwitch_<ContainerAllocator> *;
  using ConstRawPtr =
    const lagori_robot_msgs::msg::R2LimitSwitch_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<lagori_robot_msgs::msg::R2LimitSwitch_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<lagori_robot_msgs::msg::R2LimitSwitch_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      lagori_robot_msgs::msg::R2LimitSwitch_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<lagori_robot_msgs::msg::R2LimitSwitch_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      lagori_robot_msgs::msg::R2LimitSwitch_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<lagori_robot_msgs::msg::R2LimitSwitch_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<lagori_robot_msgs::msg::R2LimitSwitch_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<lagori_robot_msgs::msg::R2LimitSwitch_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__lagori_robot_msgs__msg__R2LimitSwitch
    std::shared_ptr<lagori_robot_msgs::msg::R2LimitSwitch_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__lagori_robot_msgs__msg__R2LimitSwitch
    std::shared_ptr<lagori_robot_msgs::msg::R2LimitSwitch_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const R2LimitSwitch_ & other) const
  {
    if (this->stepper1_level1 != other.stepper1_level1) {
      return false;
    }
    if (this->stepper1_level2 != other.stepper1_level2) {
      return false;
    }
    if (this->stepper1_level3 != other.stepper1_level3) {
      return false;
    }
    if (this->stepper1_level4 != other.stepper1_level4) {
      return false;
    }
    if (this->stepper1_level5 != other.stepper1_level5) {
      return false;
    }
    if (this->stepper2_level1 != other.stepper2_level1) {
      return false;
    }
    if (this->stepper2_level2 != other.stepper2_level2) {
      return false;
    }
    if (this->stepper2_level3 != other.stepper2_level3) {
      return false;
    }
    if (this->stepper2_level4 != other.stepper2_level4) {
      return false;
    }
    if (this->stepper2_level5 != other.stepper2_level5) {
      return false;
    }
    if (this->stepper3_level1 != other.stepper3_level1) {
      return false;
    }
    if (this->stepper3_level2 != other.stepper3_level2) {
      return false;
    }
    if (this->stepper3_level3 != other.stepper3_level3) {
      return false;
    }
    if (this->stepper3_level4 != other.stepper3_level4) {
      return false;
    }
    if (this->stepper3_level5 != other.stepper3_level5) {
      return false;
    }
    return true;
  }
  bool operator!=(const R2LimitSwitch_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct R2LimitSwitch_

// alias to use template instance with default allocator
using R2LimitSwitch =
  lagori_robot_msgs::msg::R2LimitSwitch_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace lagori_robot_msgs

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__R2_LIMIT_SWITCH__STRUCT_HPP_
