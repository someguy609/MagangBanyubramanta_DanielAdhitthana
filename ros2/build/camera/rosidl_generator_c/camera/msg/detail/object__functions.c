// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from camera:msg/Object.idl
// generated code does not contain a copyright notice
#include "camera/msg/detail/object__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
camera__msg__Object__init(camera__msg__Object * msg)
{
  if (!msg) {
    return false;
  }
  // red
  // yellow
  // blue
  return true;
}

void
camera__msg__Object__fini(camera__msg__Object * msg)
{
  if (!msg) {
    return;
  }
  // red
  // yellow
  // blue
}

bool
camera__msg__Object__are_equal(const camera__msg__Object * lhs, const camera__msg__Object * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // red
  if (lhs->red != rhs->red) {
    return false;
  }
  // yellow
  if (lhs->yellow != rhs->yellow) {
    return false;
  }
  // blue
  if (lhs->blue != rhs->blue) {
    return false;
  }
  return true;
}

bool
camera__msg__Object__copy(
  const camera__msg__Object * input,
  camera__msg__Object * output)
{
  if (!input || !output) {
    return false;
  }
  // red
  output->red = input->red;
  // yellow
  output->yellow = input->yellow;
  // blue
  output->blue = input->blue;
  return true;
}

camera__msg__Object *
camera__msg__Object__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  camera__msg__Object * msg = (camera__msg__Object *)allocator.allocate(sizeof(camera__msg__Object), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(camera__msg__Object));
  bool success = camera__msg__Object__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
camera__msg__Object__destroy(camera__msg__Object * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    camera__msg__Object__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
camera__msg__Object__Sequence__init(camera__msg__Object__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  camera__msg__Object * data = NULL;

  if (size) {
    data = (camera__msg__Object *)allocator.zero_allocate(size, sizeof(camera__msg__Object), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = camera__msg__Object__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        camera__msg__Object__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
camera__msg__Object__Sequence__fini(camera__msg__Object__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      camera__msg__Object__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

camera__msg__Object__Sequence *
camera__msg__Object__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  camera__msg__Object__Sequence * array = (camera__msg__Object__Sequence *)allocator.allocate(sizeof(camera__msg__Object__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = camera__msg__Object__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
camera__msg__Object__Sequence__destroy(camera__msg__Object__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    camera__msg__Object__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
camera__msg__Object__Sequence__are_equal(const camera__msg__Object__Sequence * lhs, const camera__msg__Object__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!camera__msg__Object__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
camera__msg__Object__Sequence__copy(
  const camera__msg__Object__Sequence * input,
  camera__msg__Object__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(camera__msg__Object);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    camera__msg__Object * data =
      (camera__msg__Object *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!camera__msg__Object__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          camera__msg__Object__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!camera__msg__Object__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
