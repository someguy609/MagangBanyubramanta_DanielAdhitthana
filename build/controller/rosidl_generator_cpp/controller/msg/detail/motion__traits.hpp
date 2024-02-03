// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from controller:msg/Motion.idl
// generated code does not contain a copyright notice

#ifndef CONTROLLER__MSG__DETAIL__MOTION__TRAITS_HPP_
#define CONTROLLER__MSG__DETAIL__MOTION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "controller/msg/detail/motion__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace controller
{

namespace msg
{

inline void to_flow_style_yaml(
  const Motion & msg,
  std::ostream & out)
{
  out << "{";
  // member: x_cmd
  {
    out << "x_cmd: ";
    rosidl_generator_traits::value_to_yaml(msg.x_cmd, out);
    out << ", ";
  }

  // member: y_cmd
  {
    out << "y_cmd: ";
    rosidl_generator_traits::value_to_yaml(msg.y_cmd, out);
    out << ", ";
  }

  // member: yaw
  {
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << ", ";
  }

  // member: depth
  {
    out << "depth: ";
    rosidl_generator_traits::value_to_yaml(msg.depth, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Motion & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x_cmd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x_cmd: ";
    rosidl_generator_traits::value_to_yaml(msg.x_cmd, out);
    out << "\n";
  }

  // member: y_cmd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y_cmd: ";
    rosidl_generator_traits::value_to_yaml(msg.y_cmd, out);
    out << "\n";
  }

  // member: yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << "\n";
  }

  // member: depth
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "depth: ";
    rosidl_generator_traits::value_to_yaml(msg.depth, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Motion & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace controller

namespace rosidl_generator_traits
{

[[deprecated("use controller::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const controller::msg::Motion & msg,
  std::ostream & out, size_t indentation = 0)
{
  controller::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use controller::msg::to_yaml() instead")]]
inline std::string to_yaml(const controller::msg::Motion & msg)
{
  return controller::msg::to_yaml(msg);
}

template<>
inline const char * data_type<controller::msg::Motion>()
{
  return "controller::msg::Motion";
}

template<>
inline const char * name<controller::msg::Motion>()
{
  return "controller/msg/Motion";
}

template<>
struct has_fixed_size<controller::msg::Motion>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<controller::msg::Motion>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<controller::msg::Motion>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CONTROLLER__MSG__DETAIL__MOTION__TRAITS_HPP_
