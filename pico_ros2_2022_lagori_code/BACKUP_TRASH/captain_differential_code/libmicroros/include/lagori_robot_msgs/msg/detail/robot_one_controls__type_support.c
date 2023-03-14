// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from lagori_robot_msgs:msg/RobotOneControls.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "lagori_robot_msgs/msg/detail/robot_one_controls__rosidl_typesupport_introspection_c.h"
#include "lagori_robot_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "lagori_robot_msgs/msg/detail/robot_one_controls__functions.h"
#include "lagori_robot_msgs/msg/detail/robot_one_controls__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void RobotOneControls__rosidl_typesupport_introspection_c__RobotOneControls_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  lagori_robot_msgs__msg__RobotOneControls__init(message_memory);
}

void RobotOneControls__rosidl_typesupport_introspection_c__RobotOneControls_fini_function(void * message_memory)
{
  lagori_robot_msgs__msg__RobotOneControls__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember RobotOneControls__rosidl_typesupport_introspection_c__RobotOneControls_message_member_array[7] = {
  {
    "rotor",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lagori_robot_msgs__msg__RobotOneControls, rotor),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "feeder_up",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lagori_robot_msgs__msg__RobotOneControls, feeder_up),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "feeder_down",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lagori_robot_msgs__msg__RobotOneControls, feeder_down),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "angle_up",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lagori_robot_msgs__msg__RobotOneControls, angle_up),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "angle_down",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lagori_robot_msgs__msg__RobotOneControls, angle_down),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "servo",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lagori_robot_msgs__msg__RobotOneControls, servo),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "shoot",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lagori_robot_msgs__msg__RobotOneControls, shoot),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers RobotOneControls__rosidl_typesupport_introspection_c__RobotOneControls_message_members = {
  "lagori_robot_msgs__msg",  // message namespace
  "RobotOneControls",  // message name
  7,  // number of fields
  sizeof(lagori_robot_msgs__msg__RobotOneControls),
  RobotOneControls__rosidl_typesupport_introspection_c__RobotOneControls_message_member_array,  // message members
  RobotOneControls__rosidl_typesupport_introspection_c__RobotOneControls_init_function,  // function to initialize message memory (memory has to be allocated)
  RobotOneControls__rosidl_typesupport_introspection_c__RobotOneControls_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t RobotOneControls__rosidl_typesupport_introspection_c__RobotOneControls_message_type_support_handle = {
  0,
  &RobotOneControls__rosidl_typesupport_introspection_c__RobotOneControls_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_lagori_robot_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lagori_robot_msgs, msg, RobotOneControls)() {
  if (!RobotOneControls__rosidl_typesupport_introspection_c__RobotOneControls_message_type_support_handle.typesupport_identifier) {
    RobotOneControls__rosidl_typesupport_introspection_c__RobotOneControls_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &RobotOneControls__rosidl_typesupport_introspection_c__RobotOneControls_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
