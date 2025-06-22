#ifndef GARBAGE_COLLECTOR_H
#define GARBAGE_COLLECTOR_H

#include "../memory/pool_alloc.h"

extern PoolAllocator ref_count_allocator;

typedef struct ref_count_t {
  size_t count;
  void *object;
  void (*constructor)(void *);
  void (*destructor)(void *);
} ref_count_t;

void ref_counting_init(size_t max_objects);
ref_count_t *ref_count_create(void *object, void (*constructor)(void *),
                              void (*destructor)(void *));
void ref_count_inc(ref_count_t *rc);
void ref_count_dec(ref_count_t *rc);
void ref_counting_deinit(void);
void collect_ref(ref_count_t *rc, void (*free_object)(void *));
void collect_cycles(void (*free_object)(void *));
void garbage_collect(void (*free_object)(void *));

#endif
