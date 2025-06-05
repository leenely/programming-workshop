#include "linear_alloc.h"
#include <stdlib.h>

void *linear_init(size_t size) {
  linear_allocator *allocator = malloc(sizeof(linear_allocator));

  if (allocator == NULL) {
    return NULL;
  }

  allocator->size = size;
  allocator->current_position = 0;
  allocator->memory = malloc(size);

  return allocator;
}

void *linear_alloc(linear_allocator *allocator, size_t size) {
  if (!allocator) {
    return NULL;
  }

  if (size <= 0) {
    return NULL;
  }

  if (allocator->current_position + size > allocator->size) {
    return NULL;
  }

  void *memory_pointer =
      (char *)allocator->memory + allocator->current_position;
  allocator->current_position += size;

  return memory_pointer;
}

void *linear_deinit(linear_allocator *allocator) {
  if (!allocator) {
    return NULL;
  }

  free(allocator->memory);
  free(allocator);
}

void *linear_reset(linear_allocator *allocator) {
  if (!allocator) {
    return NULL;
  }

  allocator->current_position = 0;
}
