// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from camera:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef CAMERA__MSG__DETAIL__OBJECT__TRAITS_HPP_
#define CAMERA__MSG__DETAIL__OBJECT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "camera/msg/detail/object__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace camera
{

namespace msg
{

inline void to_flow_style_yaml(
  const Object & msg,
  std::ostream & out)
{
  out << "{";
  // member: red
  {
    out << "red: ";
    rosidl_generator_traits::value_to_yaml(msg.red, out);
    out << ", ";
  }

  // member: yellow
  {
    out << "yellow: ";
    rosidl_generator_traits::value_to_yaml(msg.yellow, out);
    out << ", ";
  }

  // member: blue
  {
    out << "blue: ";
    rosidl_generator_traits::value_to_yaml(msg.blue, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Object & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: red
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "red: ";
    rosidl_generator_traits::value_to_yaml(msg.red, out);
    out << "\n";
  }

  // member: yellow
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yellow: ";
    rosidl_generator_traits::value_to_yaml(msg.yellow, out);
    out << "\n";
  }

  // member: blue
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "blue: ";
    rosidl_generator_traits::value_to_yaml(msg.blue, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Object & msg, bool use_flow_style = false)
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

}  // namespace camera

namespace rosidl_generator_traits
{

[[deprecated("use camera::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const camera::msg::Object & msg,
  std::ostream & out, size_t indentation = 0)
{
  camera::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use camera::msg::to_yaml() instead")]]
inline std::string to_yaml(const camera::msg::Object & msg)
{
  return camera::msg::to_yaml(msg);
}

template<>
inline const char * data_type<camera::msg::Object>()
{
  return "camera::msg::Object";
}

template<>
inline const char * name<camera::msg::Object>()
{
  return "camera/msg/Object";
}

template<>
struct has_fixed_size<camera::msg::Object>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<camera::msg::Object>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<camera::msg::Object>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CAMERA__MSG__DETAIL__OBJECT__TRAITS_HPP_
