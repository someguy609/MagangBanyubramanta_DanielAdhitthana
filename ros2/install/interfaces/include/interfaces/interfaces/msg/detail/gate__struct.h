// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:msg/Gate.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__GATE__STRUCT_H_
#define INTERFACES__MSG__DETAIL__GATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Gate in the package interfaces.
typedef struct interfaces__msg__Gate
{
  int32_t x;
  int32_t y;
  int32_t w;
  int32_t h;
  float conf;
} interfaces__msg__Gate;

// Struct for a sequence of interfaces__msg__Gate.
typedef struct interfaces__msg__Gate__Sequence
{
  interfaces__msg__Gate * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__msg__Gate__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__MSG__DETAIL__GATE__STRUCT_H_
