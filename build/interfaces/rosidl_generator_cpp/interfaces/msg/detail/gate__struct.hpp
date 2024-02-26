// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from interfaces:msg/Gate.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__GATE__STRUCT_HPP_
#define INTERFACES__MSG__DETAIL__GATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__interfaces__msg__Gate __attribute__((deprecated))
#else
# define DEPRECATED__interfaces__msg__Gate __declspec(deprecated)
#endif

namespace interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Gate_
{
  using Type = Gate_<ContainerAllocator>;

  explicit Gate_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0l;
      this->y = 0l;
      this->w = 0l;
      this->h = 0l;
    }
  }

  explicit Gate_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0l;
      this->y = 0l;
      this->w = 0l;
      this->h = 0l;
    }
  }

  // field types and members
  using _x_type =
    int32_t;
  _x_type x;
  using _y_type =
    int32_t;
  _y_type y;
  using _w_type =
    int32_t;
  _w_type w;
  using _h_type =
    int32_t;
  _h_type h;

  // setters for named parameter idiom
  Type & set__x(
    const int32_t & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const int32_t & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__w(
    const int32_t & _arg)
  {
    this->w = _arg;
    return *this;
  }
  Type & set__h(
    const int32_t & _arg)
  {
    this->h = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    interfaces::msg::Gate_<ContainerAllocator> *;
  using ConstRawPtr =
    const interfaces::msg::Gate_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<interfaces::msg::Gate_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<interfaces::msg::Gate_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::Gate_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::Gate_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::Gate_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::Gate_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<interfaces::msg::Gate_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<interfaces::msg::Gate_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__interfaces__msg__Gate
    std::shared_ptr<interfaces::msg::Gate_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__interfaces__msg__Gate
    std::shared_ptr<interfaces::msg::Gate_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Gate_ & other) const
  {
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->w != other.w) {
      return false;
    }
    if (this->h != other.h) {
      return false;
    }
    return true;
  }
  bool operator!=(const Gate_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Gate_

// alias to use template instance with default allocator
using Gate =
  interfaces::msg::Gate_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__GATE__STRUCT_HPP_