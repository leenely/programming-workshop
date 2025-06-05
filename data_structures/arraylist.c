#include "arraylist.h"
#include "../memory/linear_alloc.h"
#include <assert.h>
#include <string.h>

static void arraylist_grow(ArrayList *list) {
  size_t new_capacity = list->capacity * 2;
  char *new_data =
      linear_alloc(list->allocator, list->element_size * new_capacity);
  assert(new_data && "Failed to grow array");

  memcpy(new_data, list->data, list->element_size * list->length);
  list->data = new_data;
  list->capacity = new_capacity;
}

void arraylist_init(ArrayList *list, linear_allocator *allocator,
                    size_t element_size) {
  list->allocator = allocator;
  list->capacity = 4;
  list->length = 0;
  list->element_size = element_size;

  list->data = linear_alloc(allocator, element_size * list->capacity);
  assert(list->data && "Failed to allocate initial array");
}

void arraylist_add(ArrayList *list, void *element, size_t index) {
  assert(index <= list->length && "Index out of bounds");

  if (list->length == list->capacity) {
    arraylist_grow(list);
  }

  memmove(list->data + (index + 1) * list->element_size,
          list->data + index * list->element_size,
          (list->length - index) * list->element_size);

  memcpy(list->data + index * list->element_size, element, list->element_size);
  list->length++;
}

void *arraylist_get(ArrayList *list, size_t index) {
  assert(index < list->length && "Index out of bounds");
  return list->data + index * list->element_size;
}

void arraylist_del(ArrayList *list, size_t index) {
  assert(index < list->length && "Index out of bounds");

  memmove(list->data + index * list->element_size,
          list->data + (index + 1) * list->element_size,
          (list->length - index - 1) * list->element_size);

  list->length--;
}

void arraylist_free(ArrayList *list) {
  list->data = NULL;
  list->length = 0;
  list->capacity = 0;
  list->element_size = 0;
  list->allocator = NULL;
}
