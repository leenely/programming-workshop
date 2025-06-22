#include "garbage_collector.h"
#include <assert.h>
#include <stdlib.h>

PoolAllocator ref_count_allocator;

void ref_counting_init(size_t max_objects) {
  pool_init(&ref_count_allocator, sizeof(ref_count_t), max_objects);
}

ref_count_t *ref_count_create(void *object, void (*constructor)(void *),
                              void (*destructor)(void *)) {
  if (object == NULL)
    return NULL;

  ref_count_t *rc = (ref_count_t *)pool_alloc(&ref_count_allocator);
  if (!rc)
    return NULL;

  rc->count = 1;
  rc->object = object;
  rc->constructor = constructor;
  rc->destructor = destructor;

  if (constructor) {
    constructor(object);
  }

  return rc;
}

void ref_count_inc(ref_count_t *rc) {
  if (rc) {
    rc->count++;
  }
}

void ref_count_dec(ref_count_t *rc) {
  if (!rc)
    return;

  rc->count--;
  if (rc->count == 0) {
    if (rc->object && rc->destructor) {
      rc->destructor(rc->object);
    } else if (rc->object) {
      free(rc->object);
    }

    pool_free(&ref_count_allocator, rc);
  }
}

void ref_counting_deinit(void) { pool_deinit(&ref_count_allocator); }
