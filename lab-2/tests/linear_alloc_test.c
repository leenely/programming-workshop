#include "../linear_alloc.h"
#include "assert.h"

void test_linaer_alloc_init() {
  size_t size = 1024 * 8;
  linear_allocator *allocator = linear_init(size);

  assert(allocator->size == size);
  assert(allocator->current_position == 0);
  assert(allocator->memory != NULL);
  linear_deinit(allocator);
}

void test_linear_alloc_allocation() {
  size_t size = 1024 * 5;
  linear_allocator *allocator = linear_init(size);

  void *pointer_1 = linear_alloc(allocator, 512);
  assert(allocator->current_position == 512);

  void *pointer_2 = linear_alloc(allocator, 1024 * 4);
  assert(allocator->current_position == 512 + 1024 * 4);

  linear_deinit(allocator);
}

void test_linear_alloc_zero() {
  size_t size = 1024 * 1;
  linear_allocator *allocator = linear_init(size);

  void *pointer = linear_alloc(allocator, 0);
  assert(allocator->current_position == 0);
  assert(pointer == NULL);

  linear_deinit(allocator);
}

void test_linear_alloc_out_of_memory() {
  size_t size = 1024 * 2;
  linear_allocator *allocator = linear_init(size);

  void *pointer = linear_alloc(allocator, size + 1);
  assert(allocator->current_position == 0);
  assert(pointer == NULL);

  linear_deinit(allocator);
}

void test_linear_alloc_reset() {
  size_t size = 1024 * 2;
  linear_allocator *allocator = linear_init(size);

  void *pointer = linear_alloc(allocator, 1024);
  assert(allocator->current_position == 1024);

  linear_reset(allocator);
  assert(allocator->current_position == 0);

  linear_deinit(allocator);
}

int main() {
  test_linaer_alloc_init();
  test_linear_alloc_allocation();
  test_linear_alloc_zero();
  test_linear_alloc_out_of_memory();
  test_linear_alloc_reset();
  return 0;
}