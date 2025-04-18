#include <stddef.h>

typedef struct FreeBlock {
  struct FreeBlock *next;
} FreeBlock;

typedef struct {
  FreeBlock *free_list;
  void *pool_memory;
  size_t chunk_size;
  size_t pool_size;
} PoolAllocator;

void pool_init(PoolAllocator *allocator, size_t chunk_size, size_t pool_size);
void *pool_alloc(PoolAllocator *allocator);
void pool_free(PoolAllocator *allocator, void *ptr);
void pool_deinit(PoolAllocator *allocator);
