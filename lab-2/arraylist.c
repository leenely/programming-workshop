#include "arraylist.h"
#include "linear_alloc.h"
#include <assert.h>
#include <string.h>

static void arraylist_grow(ArrayList *list) {
  size_t new_capacity = list->capacity * 2;
  void **new_data =
      linear_alloc(list->allocator, sizeof(void *) * new_capacity);
  assert(new_data && "Failed to grow array");

  memcpy(new_data, list->data, sizeof(void *) * list->size);
  list->data = new_data;
  list->capacity = new_capacity;
}

void arraylist_init(ArrayList *list, linear_allocator *allocator) {
  list->allocator = allocator;
  list->capacity = 4;
  list->size = 0;

  list->data = linear_alloc(allocator, sizeof(void *) * list->capacity);
  assert(list->data && "Failed to allocate initial array");
}

void arraylist_add(ArrayList *list, void *element, size_t index) {
  assert(index <= list->size && "Index out of bounds");

  if (list->size == list->capacity) {
    arraylist_grow(list);
  }

  memmove(list->data + index + 1, list->data + index,
          sizeof(void *) * (list->size - index));
  list->data[index] = element;
  list->size++;
}

void *arraylist_get(ArrayList *list, size_t index) {
  assert(index < list->size && "Index out of bounds");
  return list->data[index];
}

void arraylist_del(ArrayList *list, size_t index) {
  assert(index < list->size && "Index out of bounds");

  memmove(list->data + index, list->data + index + 1,
          sizeof(void *) * (list->size - index - 1));
  list->size--;
}

void arraylist_free(ArrayList *list) {
  list->data = NULL;
  list->size = 0;
  list->capacity = 0;
  list->allocator = NULL;
}
