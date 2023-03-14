// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from lagori_robot_msgs:msg/R2LimitSwitchStepper3.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "lagori_robot_msgs/msg/detail/r2_limit_switch_stepper3__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace lagori_robot_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void R2LimitSwitchStepper3_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) lagori_robot_msgs::msg::R2LimitSwitchStepper3(_init);
}

void R2LimitSwitchStepper3_fini_function(void * message_memory)
{
  auto typed_message = static_cast<lagori_robot_msgs::msg::R2LimitSwitchStepper3 *>(message_memory);
  typed_message->~R2LimitSwitchStepper3();
}

size_t size_function__R2LimitSwitchStepper3__stepper3_level(const void * untyped_member)
{
  (void)untyped_member;
  return 5;
}

const void * get_const_function__R2LimitSwitchStepper3__stepper3_level(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int32_t, 5> *>(untyped_member);
  return &member[index];
}

void * get_function__R2LimitSwitchStepper3__stepper3_level(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int32_t, 5> *>(untyped_member);
  return &member[index];
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember R2LimitSwitchStepper3_message_member_array[1] = {
  {
    "stepper3_level",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    5,  // array size
    false,  // is upper bound
    offsetof(lagori_robot_msgs::msg::R2LimitSwitchStepper3, stepper3_level),  // bytes offset in struct
    nullptr,  // default value
    size_function__R2LimitSwitchStepper3__stepper3_level,  // size() function pointer
    get_const_function__R2LimitSwitchStepper3__stepper3_level,  // get_const(index) function pointer
    get_function__R2LimitSwitchStepper3__stepper3_level,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers R2LimitSwitchStepper3_message_members = {
  "lagori_robot_msgs::msg",  // message namespace
  "R2LimitSwitchStepper3",  // message name
  1,  // number of fields
  sizeof(lagori_robot_msgs::msg::R2LimitSwitchStepper3),
  R2LimitSwitchStepper3_message_member_array,  // message members
  R2LimitSwitchStepper3_init_function,  // function to initialize message memory (memory has to be allocated)
  R2LimitSwitchStepper3_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t R2LimitSwitchStepper3_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &R2LimitSwitchStepper3_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace lagori_robot_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<lagori_robot_msgs::msg::R2LimitSwitchStepper3>()
{
  return &::lagori_robot_msgs::msg::rosidl_typesupport_introspection_cpp::R2LimitSwitchStepper3_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, lagori_robot_msgs, msg, R2LimitSwitchStepper3)() {
  return &::lagori_robot_msgs::msg::rosidl_typesupport_introspection_cpp::R2LimitSwitchStepper3_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
