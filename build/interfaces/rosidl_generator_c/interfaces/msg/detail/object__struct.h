// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__OBJECT__STRUCT_H_
#define INTERFACES__MSG__DETAIL__OBJECT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Object in the package interfaces.
typedef struct interfaces__msg__Object
{
  int32_t red;
  int32_t yellow;
  int32_t blue;
} interfaces__msg__Object;

// Struct for a sequence of interfaces__msg__Object.
typedef struct interfaces__msg__Object__Sequence
{
  interfaces__msg__Object * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__msg__Object__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__MSG__DETAIL__OBJECT__STRUCT_H_
