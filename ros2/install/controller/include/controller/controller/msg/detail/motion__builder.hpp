// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from controller:msg/Motion.idl
// generated code does not contain a copyright notice

#ifndef CONTROLLER__MSG__DETAIL__MOTION__BUILDER_HPP_
#define CONTROLLER__MSG__DETAIL__MOTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "controller/msg/detail/motion__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace controller
{

namespace msg
{

namespace builder
{

class Init_Motion_depth
{
public:
  explicit Init_Motion_depth(::controller::msg::Motion & msg)
  : msg_(msg)
  {}
  ::controller::msg::Motion depth(::controller::msg::Motion::_depth_type arg)
  {
    msg_.depth = std::move(arg);
    return std::move(msg_);
  }

private:
  ::controller::msg::Motion msg_;
};

class Init_Motion_yaw
{
public:
  explicit Init_Motion_yaw(::controller::msg::Motion & msg)
  : msg_(msg)
  {}
  Init_Motion_depth yaw(::controller::msg::Motion::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_Motion_depth(msg_);
  }

private:
  ::controller::msg::Motion msg_;
};

class Init_Motion_y_cmd
{
public:
  explicit Init_Motion_y_cmd(::controller::msg::Motion & msg)
  : msg_(msg)
  {}
  Init_Motion_yaw y_cmd(::controller::msg::Motion::_y_cmd_type arg)
  {
    msg_.y_cmd = std::move(arg);
    return Init_Motion_yaw(msg_);
  }

private:
  ::controller::msg::Motion msg_;
};

class Init_Motion_x_cmd
{
public:
  Init_Motion_x_cmd()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Motion_y_cmd x_cmd(::controller::msg::Motion::_x_cmd_type arg)
  {
    msg_.x_cmd = std::move(arg);
    return Init_Motion_y_cmd(msg_);
  }

private:
  ::controller::msg::Motion msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::controller::msg::Motion>()
{
  return controller::msg::builder::Init_Motion_x_cmd();
}

}  // namespace controller

#endif  // CONTROLLER__MSG__DETAIL__MOTION__BUILDER_HPP_
