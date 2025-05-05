#include "pool_alloc.h"

#define SUCCESS_CODE 0
#define NULLPOINTEREXCEPTION_ERRCODE -1
#define MEMORYALLOCATIONEXCEPTION_ERRCODE -2
#define EMPTYLISTEXCEPTION_ERRCODE -3
#define INDEXOUTOFRANGEEXCEPTION_ERRCODE -4

typedef struct {
  void **data;
  size_t size;
  size_t capacity;
  PoolAllocator *allocator;
} ArrayList;

void arraylist_init(ArrayList *list, PoolAllocator *allocator);

void arraylist_add(ArrayList *list, void *data, size_t index);

void *arraylist_get(ArrayList *list, size_t index);

void arraylist_del(ArrayList *list, size_t index);

void arraylist_free(ArrayList *list);
