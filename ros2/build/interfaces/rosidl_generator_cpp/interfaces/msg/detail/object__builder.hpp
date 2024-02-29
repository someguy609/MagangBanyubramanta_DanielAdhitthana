// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__OBJECT__BUILDER_HPP_
#define INTERFACES__MSG__DETAIL__OBJECT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/msg/detail/object__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace msg
{

namespace builder
{

class Init_Object_angle
{
public:
  explicit Init_Object_angle(::interfaces::msg::Object & msg)
  : msg_(msg)
  {}
  ::interfaces::msg::Object angle(::interfaces::msg::Object::_angle_type arg)
  {
    msg_.angle = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::Object msg_;
};

class Init_Object_y
{
public:
  explicit Init_Object_y(::interfaces::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_angle y(::interfaces::msg::Object::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Object_angle(msg_);
  }

private:
  ::interfaces::msg::Object msg_;
};

class Init_Object_x
{
public:
  explicit Init_Object_x(::interfaces::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_y x(::interfaces::msg::Object::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Object_y(msg_);
  }

private:
  ::interfaces::msg::Object msg_;
};

class Init_Object_color
{
public:
  Init_Object_color()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Object_x color(::interfaces::msg::Object::_color_type arg)
  {
    msg_.color = std::move(arg);
    return Init_Object_x(msg_);
  }

private:
  ::interfaces::msg::Object msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::msg::Object>()
{
  return interfaces::msg::builder::Init_Object_color();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__OBJECT__BUILDER_HPP_
