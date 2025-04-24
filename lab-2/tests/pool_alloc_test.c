#include "../pool_alloc.h"
#include <assert.h>

void test_pool_init() {
  PoolAllocator allocator;
  pool_init(&allocator, 32, 10);
  assert(allocator.pool_memory != NULL);
  assert(allocator.free_list != NULL);
  pool_deinit(&allocator);
}

void test_pool_alloc_free() {
  PoolAllocator allocator;
  pool_init(&allocator, 32, 10);

  void *block1 = pool_alloc(&allocator);
  void *block2 = pool_alloc(&allocator);

  assert(block1 != NULL);
  assert(block2 != NULL);

  pool_free(&allocator, block1);
  pool_free(&allocator, block2);

  FreeBlock *free_block = allocator.free_list;
  int free_count = 0;
  while (free_block) {
    free_count++;
    free_block = free_block->next;
  }

  assert(free_count == 10);
  pool_deinit(&allocator);
}

void test_pool_reuse() {
  PoolAllocator allocator;
  pool_init(&allocator, 32, 10);

  void *blocks[10];
  for (int i = 0; i < 10; i++) {
    blocks[i] = pool_alloc(&allocator);
    assert(blocks[i] != NULL);
  }

  void *block11 = pool_alloc(&allocator);
  assert(block11 == NULL);

  pool_free(&allocator, blocks[5]);

  void *block12 = pool_alloc(&allocator);
  assert(block12 == blocks[5]);

  pool_deinit(&allocator);
}

void test_pool_overflow() {
  PoolAllocator allocator;
  pool_init(&allocator, 32, 3);

  void *block1 = pool_alloc(&allocator);
  void *block2 = pool_alloc(&allocator);
  void *block3 = pool_alloc(&allocator);

  assert(block1 != NULL);
  assert(block2 != NULL);
  assert(block3 != NULL);

  void *block4 = pool_alloc(&allocator);
  assert(block4 == NULL);

  pool_deinit(&allocator);
}

int main() {
  test_pool_init();
  test_pool_alloc_free();
  test_pool_reuse();
  test_pool_overflow();
  return 0;
}
