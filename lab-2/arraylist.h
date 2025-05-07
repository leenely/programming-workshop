#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "linear_alloc.h"

typedef struct {
  void **data;
  size_t size;
  size_t capacity;
  linear_allocator *allocator;
} ArrayList;

void arraylist_init(ArrayList *list, linear_allocator *allocator);
void arraylist_add(ArrayList *list, void *element, size_t index);
void *arraylist_get(ArrayList *list, size_t index);
void arraylist_del(ArrayList *list, size_t index);
void arraylist_free(ArrayList *list);

#endif
