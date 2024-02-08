// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from camera:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef CAMERA__MSG__DETAIL__OBJECT__STRUCT_H_
#define CAMERA__MSG__DETAIL__OBJECT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Object in the package camera.
typedef struct camera__msg__Object
{
  int32_t red;
  int32_t yellow;
  int32_t blue;
} camera__msg__Object;

// Struct for a sequence of camera__msg__Object.
typedef struct camera__msg__Object__Sequence
{
  camera__msg__Object * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} camera__msg__Object__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CAMERA__MSG__DETAIL__OBJECT__STRUCT_H_
