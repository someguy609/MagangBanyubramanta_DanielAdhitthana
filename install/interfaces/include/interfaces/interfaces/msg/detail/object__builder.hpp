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

class Init_Object_blue
{
public:
  explicit Init_Object_blue(::interfaces::msg::Object & msg)
  : msg_(msg)
  {}
  ::interfaces::msg::Object blue(::interfaces::msg::Object::_blue_type arg)
  {
    msg_.blue = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::Object msg_;
};

class Init_Object_yellow
{
public:
  explicit Init_Object_yellow(::interfaces::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_blue yellow(::interfaces::msg::Object::_yellow_type arg)
  {
    msg_.yellow = std::move(arg);
    return Init_Object_blue(msg_);
  }

private:
  ::interfaces::msg::Object msg_;
};

class Init_Object_red
{
public:
  Init_Object_red()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Object_yellow red(::interfaces::msg::Object::_red_type arg)
  {
    msg_.red = std::move(arg);
    return Init_Object_yellow(msg_);
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
  return interfaces::msg::builder::Init_Object_red();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__OBJECT__BUILDER_HPP_
