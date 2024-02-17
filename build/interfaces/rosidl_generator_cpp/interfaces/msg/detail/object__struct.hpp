// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from interfaces:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__OBJECT__STRUCT_HPP_
#define INTERFACES__MSG__DETAIL__OBJECT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__interfaces__msg__Object __attribute__((deprecated))
#else
# define DEPRECATED__interfaces__msg__Object __declspec(deprecated)
#endif

namespace interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Object_
{
  using Type = Object_<ContainerAllocator>;

  explicit Object_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->red = 0l;
      this->yellow = 0l;
      this->blue = 0l;
    }
  }

  explicit Object_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->red = 0l;
      this->yellow = 0l;
      this->blue = 0l;
    }
  }

  // field types and members
  using _red_type =
    int32_t;
  _red_type red;
  using _yellow_type =
    int32_t;
  _yellow_type yellow;
  using _blue_type =
    int32_t;
  _blue_type blue;

  // setters for named parameter idiom
  Type & set__red(
    const int32_t & _arg)
  {
    this->red = _arg;
    return *this;
  }
  Type & set__yellow(
    const int32_t & _arg)
  {
    this->yellow = _arg;
    return *this;
  }
  Type & set__blue(
    const int32_t & _arg)
  {
    this->blue = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    interfaces::msg::Object_<ContainerAllocator> *;
  using ConstRawPtr =
    const interfaces::msg::Object_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<interfaces::msg::Object_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<interfaces::msg::Object_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::Object_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::Object_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      interfaces::msg::Object_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<interfaces::msg::Object_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<interfaces::msg::Object_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<interfaces::msg::Object_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__interfaces__msg__Object
    std::shared_ptr<interfaces::msg::Object_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__interfaces__msg__Object
    std::shared_ptr<interfaces::msg::Object_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Object_ & other) const
  {
    if (this->red != other.red) {
      return false;
    }
    if (this->yellow != other.yellow) {
      return false;
    }
    if (this->blue != other.blue) {
      return false;
    }
    return true;
  }
  bool operator!=(const Object_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Object_

// alias to use template instance with default allocator
using Object =
  interfaces::msg::Object_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__OBJECT__STRUCT_HPP_
