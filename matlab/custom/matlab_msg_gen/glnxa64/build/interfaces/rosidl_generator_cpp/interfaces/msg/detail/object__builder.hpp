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

class Init_Object_h
{
public:
  explicit Init_Object_h(::interfaces::msg::Object & msg)
  : msg_(msg)
  {}
  ::interfaces::msg::Object h(::interfaces::msg::Object::_h_type arg)
  {
    msg_.h = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::Object msg_;
};

class Init_Object_w
{
public:
  explicit Init_Object_w(::interfaces::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_h w(::interfaces::msg::Object::_w_type arg)
  {
    msg_.w = std::move(arg);
    return Init_Object_h(msg_);
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
  Init_Object_w y(::interfaces::msg::Object::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Object_w(msg_);
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

class Init_Object_type
{
public:
  Init_Object_type()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Object_x type(::interfaces::msg::Object::_type_type arg)
  {
    msg_.type = std::move(arg);
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
  return interfaces::msg::builder::Init_Object_type();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__OBJECT__BUILDER_HPP_
