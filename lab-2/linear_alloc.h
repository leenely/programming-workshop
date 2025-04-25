#ifndef LINEAR_ALLOC_H
#define LINEAR_ALLOC_H


#include <stddef.h>

typedef struct {
  size_t size;
  size_t current_position;
  void *memory;
} linear_allocator;

void *linear_init(size_t size);
void *linear_alloc(linear_allocator *allocator, size_t size);
void *linear_deinit(linear_allocator *allocator);
void *linear_reset(linear_allocator *allocator);

#endif
