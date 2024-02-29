// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:msg/Motion.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__MOTION__STRUCT_H_
#define INTERFACES__MSG__DETAIL__MOTION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Motion in the package interfaces.
typedef struct interfaces__msg__Motion
{
  /// [-500, 500]
  int32_t x_cmd;
  /// [-500, 500]
  int32_t y_cmd;
  /// [-500, 500]
  int32_t yaw;
  /// [-500, 500]
  int32_t depth;
} interfaces__msg__Motion;

// Struct for a sequence of interfaces__msg__Motion.
typedef struct interfaces__msg__Motion__Sequence
{
  interfaces__msg__Motion * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__msg__Motion__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__MSG__DETAIL__MOTION__STRUCT_H_
