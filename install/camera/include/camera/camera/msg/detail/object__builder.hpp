// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from camera:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef CAMERA__MSG__DETAIL__OBJECT__BUILDER_HPP_
#define CAMERA__MSG__DETAIL__OBJECT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "camera/msg/detail/object__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace camera
{

namespace msg
{

namespace builder
{

class Init_Object_blue
{
public:
  explicit Init_Object_blue(::camera::msg::Object & msg)
  : msg_(msg)
  {}
  ::camera::msg::Object blue(::camera::msg::Object::_blue_type arg)
  {
    msg_.blue = std::move(arg);
    return std::move(msg_);
  }

private:
  ::camera::msg::Object msg_;
};

class Init_Object_yellow
{
public:
  explicit Init_Object_yellow(::camera::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_blue yellow(::camera::msg::Object::_yellow_type arg)
  {
    msg_.yellow = std::move(arg);
    return Init_Object_blue(msg_);
  }

private:
  ::camera::msg::Object msg_;
};

class Init_Object_red
{
public:
  Init_Object_red()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Object_yellow red(::camera::msg::Object::_red_type arg)
  {
    msg_.red = std::move(arg);
    return Init_Object_yellow(msg_);
  }

private:
  ::camera::msg::Object msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::camera::msg::Object>()
{
  return camera::msg::builder::Init_Object_red();
}

}  // namespace camera

#endif  // CAMERA__MSG__DETAIL__OBJECT__BUILDER_HPP_
