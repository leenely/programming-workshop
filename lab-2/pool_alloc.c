#include "pool_alloc.h"
#include <assert.h>
#include <stdlib.h>

void pool_init(PoolAllocator *allocator, size_t chunk_size, size_t pool_size) {
  allocator->chunk_size = chunk_size;
  allocator->pool_size = pool_size;
  allocator->pool_memory = calloc(pool_size, chunk_size);
  allocator->free_list = NULL;

  for (size_t i = 0; i < pool_size; ++i) {
    FreeBlock *block =
        (FreeBlock *)((char *)allocator->pool_memory + i * chunk_size);
    block->next = allocator->free_list;
    allocator->free_list = block;
  }
}

void *pool_alloc(PoolAllocator *allocator) {
  if (allocator->free_list == NULL) {
    return NULL;
  }

  FreeBlock *block = allocator->free_list;
  allocator->free_list = block->next;
  return block;
}

void pool_free(PoolAllocator *allocator, void *ptr) {
  if (!allocator || !ptr)
    return;

  FreeBlock *block = (FreeBlock *)ptr;
  block->next = allocator->free_list;
  allocator->free_list = block;
}

void pool_deinit(PoolAllocator *allocator) {
  if (allocator) {
    free(allocator->pool_memory);
    allocator->pool_memory = NULL;
    allocator->free_list = NULL;
    allocator->chunk_size = 0;
    allocator->pool_size = 0;
  }
}
