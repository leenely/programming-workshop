#include "arraylist.h"
#include "pool_alloc.c"
#include "pool_alloc.h"
#include <assert.h>
#include <string.h>

void arraylist_init(ArrayList *list, PoolAllocator *allocator) {
  list->allocator = allocator;
  list->size = 0;
  list->capacity = 4;
  list->data = (void **)pool_alloc(allocator);
  if (!list->data) {
    return;
  }
}

void arraylist_add(ArrayList *list, void *data, size_t index) {
  if (index > list->size)
    return;

  if (list->size == list->capacity) {
    size_t new_capacity = list->capacity * 2;
    void *new_data = (void *)pool_alloc(list->allocator);
    if (!new_data)
      return;

    memcpy(new_data, list->data, index * sizeof(void *));
    memcpy(new_data + index + 1, list->data + index,
           (list->size - index) * sizeof(void *));

    pool_free(list->allocator, list->data);

    list->data = new_data;
    list->capacity = new_capacity;
  } else {
    memmove(list->data + index + 1, list->data + index,
            (list->size - index) * sizeof(void *));
  }

  list->data[index] = data;
  list->size++;
}

void *arraylist_get(ArrayList *list, size_t index) {
  if (index >= list->size)
    return NULL;
  return list->data[index];
}

void arraylist_del(ArrayList *list, size_t index) {
  if (index >= list->size)
    return;

  memmove(list->data + index, list->data + index + 1,
          (list->size - index - 1) * sizeof(void *));
  list->size--;
}

void arraylist_free(ArrayList *list) {
  if (list->allocator && list->data) {
    pool_free(list->allocator, list->data);
  }
  list->data = NULL;
  list->size = 0;
  list->capacity = 0;
}
