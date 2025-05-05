#include "arraylist.h"

void arraylist_init(ArrayList *list, PoolAllocator *allocator) {
  if (!list || !allocator)
    return NULLPOINTEREXCEPTION_ERRCODE;

  list->data = NULL;
  list->size = 0;
  list->capacity = 0;
  list->allocator = allocator;
  return SUCCESS_CODE;
}

void arraylist_add(ArrayList *list, void *data, size_t index) {
  if (!list || !list->allocator)
    return NULLPOINTEREXCEPTION_ERRCODE;
  if (index > list->size)
    return INDEXOUTOFRANGEEXCEPTION_ERRCODE;

  if (list->size >= list->capacity) {
    size_t new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
    void **new_data = pool_allocator_reallocate(list->allocator, list->data,
                                                list->capacity * sizeof(void *),
                                                new_capacity * sizeof(void *));

    if (!new_data)
      return MEMORYALLOCATIONEXCEPTION_ERRCODE;

    list->data = new_data;
    list->capacity = new_capacity;
  }

  if (index < list->size) {
    memmove(&list->data[index + 1], &list->data[index],
            (list->size - index) * sizeof(void *));
  }

  list->data[index] = data;
  list->size++;
  return SUCCESS_CODE;
}

void *arraylist_get(ArrayList *list, size_t index) {
  if (!list)
    return NULLPOINTEREXCEPTION_ERRCODE;
  if (list->size == 0)
    return EMPTYLISTEXCEPTION_ERRCODE;
  if (index >= list->size)
    return INDEXOUTOFRANGEEXCEPTION_ERRCODE;
  return list->data[index];
}

void arraylist_del(ArrayList *list, size_t index) {
  if (!list)
    return NULLPOINTEREXCEPTION_ERRCODE;
  if (list->size == 0)
    return EMPTYLISTEXCEPTION_ERRCODE;
  if (index >= list->size)
    return INDEXOUTOFRANGEEXCEPTION_ERRCODE;

  if (index < list->size - 1) {
    memmove(&list->data[index], &list->data[index + 1],
            (list->size - index - 1) * sizeof(void *));
  }

  list->size--;

  if (list->size < list->capacity / 4 && list->capacity > 4) {
    size_t new_capacity = list->capacity / 2;
    void **new_data = pool_allocator_reallocate(list->allocator, list->data,
                                                list->capacity * sizeof(void *),
                                                new_capacity * sizeof(void *));

    if (new_data) {
      list->data = new_data;
      list->capacity = new_capacity;
    }
  }
  return SUCCESS_CODE;
}

void arraylist_free(ArrayList *list) {
  if (!list)
    return NULLPOINTEREXCEPTION_ERRCODE;

  if (list->data) {
    pool_allocator_deallocate(list->allocator, list->data,
                              list->capacity * sizeof(void *));

    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
  }
  return SUCCESS_CODE;
}
