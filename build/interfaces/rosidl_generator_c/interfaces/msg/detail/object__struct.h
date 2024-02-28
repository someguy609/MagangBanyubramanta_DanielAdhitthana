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

/// Constant 'RED'.
enum
{
  interfaces__msg__Object__RED = 0
};

/// Constant 'YELLOW'.
enum
{
  interfaces__msg__Object__YELLOW = 1
};

/// Constant 'BLUE'.
enum
{
  interfaces__msg__Object__BLUE = 2
};

/// Struct defined in msg/Object in the package interfaces.
/**
  * int32 red
  * int32 yellow
  * int32 blue
 */
typedef struct interfaces__msg__Object
{
  uint8_t color;
  int32_t x;
  int32_t y;
  int32_t angle;
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
