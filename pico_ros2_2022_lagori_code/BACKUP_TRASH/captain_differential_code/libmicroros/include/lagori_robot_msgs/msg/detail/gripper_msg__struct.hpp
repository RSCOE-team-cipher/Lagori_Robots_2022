// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from lagori_robot_msgs:msg/GripperMsg.idl
// generated code does not contain a copyright notice

#ifndef LAGORI_ROBOT_MSGS__MSG__DETAIL__GRIPPER_MSG__STRUCT_HPP_
#define LAGORI_ROBOT_MSGS__MSG__DETAIL__GRIPPER_MSG__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__lagori_robot_msgs__msg__GripperMsg __attribute__((deprecated))
#else
# define DEPRECATED__lagori_robot_msgs__msg__GripperMsg __declspec(deprecated)
#endif

namespace lagori_robot_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GripperMsg_
{
  using Type = GripperMsg_<ContainerAllocator>;

  explicit GripperMsg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->one_open = 0l;
      this->one_close = 0l;
      this->two_open = 0l;
      this->two_close = 0l;
      this->three_open = 0l;
      this->three_close = 0l;
    }
  }

  explicit GripperMsg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->one_open = 0l;
      this->one_close = 0l;
      this->two_open = 0l;
      this->two_close = 0l;
      this->three_open = 0l;
      this->three_close = 0l;
    }
  }

  // field types and members
  using _one_open_type =
    int32_t;
  _one_open_type one_open;
  using _one_close_type =
    int32_t;
  _one_close_type one_close;
  using _two_open_type =
    int32_t;
  _two_open_type two_open;
  using _two_close_type =
    int32_t;
  _two_close_type two_close;
  using _three_open_type =
    int32_t;
  _three_open_type three_open;
  using _three_close_type =
    int32_t;
  _three_close_type three_close;

  // setters for named parameter idiom
  Type & set__one_open(
    const int32_t & _arg)
  {
    this->one_open = _arg;
    return *this;
  }
  Type & set__one_close(
    const int32_t & _arg)
  {
    this->one_close = _arg;
    return *this;
  }
  Type & set__two_open(
    const int32_t & _arg)
  {
    this->two_open = _arg;
    return *this;
  }
  Type & set__two_close(
    const int32_t & _arg)
  {
    this->two_close = _arg;
    return *this;
  }
  Type & set__three_open(
    const int32_t & _arg)
  {
    this->three_open = _arg;
    return *this;
  }
  Type & set__three_close(
    const int32_t & _arg)
  {
    this->three_close = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    lagori_robot_msgs::msg::GripperMsg_<ContainerAllocator> *;
  using ConstRawPtr =
    const lagori_robot_msgs::msg::GripperMsg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<lagori_robot_msgs::msg::GripperMsg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<lagori_robot_msgs::msg::GripperMsg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      lagori_robot_msgs::msg::GripperMsg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<lagori_robot_msgs::msg::GripperMsg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      lagori_robot_msgs::msg::GripperMsg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<lagori_robot_msgs::msg::GripperMsg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<lagori_robot_msgs::msg::GripperMsg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<lagori_robot_msgs::msg::GripperMsg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__lagori_robot_msgs__msg__GripperMsg
    std::shared_ptr<lagori_robot_msgs::msg::GripperMsg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__lagori_robot_msgs__msg__GripperMsg
    std::shared_ptr<lagori_robot_msgs::msg::GripperMsg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GripperMsg_ & other) const
  {
    if (this->one_open != other.one_open) {
      return false;
    }
    if (this->one_close != other.one_close) {
      return false;
    }
    if (this->two_open != other.two_open) {
      return false;
    }
    if (this->two_close != other.two_close) {
      return false;
    }
    if (this->three_open != other.three_open) {
      return false;
    }
    if (this->three_close != other.three_close) {
      return false;
    }
    return true;
  }
  bool operator!=(const GripperMsg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GripperMsg_

// alias to use template instance with default allocator
using GripperMsg =
  lagori_robot_msgs::msg::GripperMsg_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace lagori_robot_msgs

#endif  // LAGORI_ROBOT_MSGS__MSG__DETAIL__GRIPPER_MSG__STRUCT_HPP_
