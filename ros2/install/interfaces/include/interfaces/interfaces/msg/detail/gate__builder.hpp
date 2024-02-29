// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:msg/Gate.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__GATE__BUILDER_HPP_
#define INTERFACES__MSG__DETAIL__GATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/msg/detail/gate__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace msg
{

namespace builder
{

class Init_Gate_conf
{
public:
  explicit Init_Gate_conf(::interfaces::msg::Gate & msg)
  : msg_(msg)
  {}
  ::interfaces::msg::Gate conf(::interfaces::msg::Gate::_conf_type arg)
  {
    msg_.conf = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::Gate msg_;
};

class Init_Gate_h
{
public:
  explicit Init_Gate_h(::interfaces::msg::Gate & msg)
  : msg_(msg)
  {}
  Init_Gate_conf h(::interfaces::msg::Gate::_h_type arg)
  {
    msg_.h = std::move(arg);
    return Init_Gate_conf(msg_);
  }

private:
  ::interfaces::msg::Gate msg_;
};

class Init_Gate_w
{
public:
  explicit Init_Gate_w(::interfaces::msg::Gate & msg)
  : msg_(msg)
  {}
  Init_Gate_h w(::interfaces::msg::Gate::_w_type arg)
  {
    msg_.w = std::move(arg);
    return Init_Gate_h(msg_);
  }

private:
  ::interfaces::msg::Gate msg_;
};

class Init_Gate_y
{
public:
  explicit Init_Gate_y(::interfaces::msg::Gate & msg)
  : msg_(msg)
  {}
  Init_Gate_w y(::interfaces::msg::Gate::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Gate_w(msg_);
  }

private:
  ::interfaces::msg::Gate msg_;
};

class Init_Gate_x
{
public:
  Init_Gate_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Gate_y x(::interfaces::msg::Gate::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Gate_y(msg_);
  }

private:
  ::interfaces::msg::Gate msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::msg::Gate>()
{
  return interfaces::msg::builder::Init_Gate_x();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__GATE__BUILDER_HPP_
