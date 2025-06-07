#include "garbage_collector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

PoolAllocator ref_count_allocator;

void ref_counting_init(size_t max_objects) {
  pool_init(&ref_count_allocator, sizeof(ref_count_t), max_objects);
}

ref_count_t *ref_count_create(void *object) {
  if (object == NULL)
    return NULL;

  ref_count_t *rc = (ref_count_t *)pool_alloc(&ref_count_allocator);
  if (!rc)
    return NULL;

  rc->count = 1;
  rc->object = object;
  return rc;
}

void ref_count_inc(ref_count_t *rc) {
  if (rc) {
    rc->count++;
  }
}

void ref_count_dec(ref_count_t *rc) {
  if (!rc || rc->count == 0)
    return;
  rc->count--;
}

void collect_ref(ref_count_t *rc, void (*free_object)(void *)) {
  if (!rc || rc->count != 0)
    return;

  if (free_object) {
    free_object(rc->object);
  } else {
    free(rc->object);
  }
  pool_free(&ref_count_allocator, rc);
}

void collect_cycles(void (*free_object)(void *)) {
  if (!ref_count_allocator.pool_memory)
    return;

  char *memory = (char *)ref_count_allocator.pool_memory;
  size_t chunk_size = ref_count_allocator.chunk_size;
  size_t pool_size = ref_count_allocator.pool_size;

  for (size_t i = 0; i < pool_size; i++) {
    ref_count_t *rc = (ref_count_t *)(memory + (i * chunk_size));

    int is_allocated = 1;
    FreeBlock *current = ref_count_allocator.free_list;
    while (current) {
      if ((char *)current == (char *)rc) {
        is_allocated = 0;
        break;
      }
      current = current->next;
    }

    if (is_allocated && rc->object && *(ref_count_t **)rc->object == rc) {
      rc->count--;
      if (rc->count == 0) {
        collect_ref(rc, free_object);
      }
    }
  }
}

void garbage_collect(void (*free_object)(void *)) {
  if (!ref_count_allocator.pool_memory)
    return;

  char *memory = (char *)ref_count_allocator.pool_memory;
  size_t chunk_size = ref_count_allocator.chunk_size;
  size_t pool_size = ref_count_allocator.pool_size;

  for (size_t i = 0; i < pool_size; i++) {
    ref_count_t *rc = (ref_count_t *)(memory + (i * chunk_size));

    int is_allocated = 1;
    FreeBlock *current = ref_count_allocator.free_list;
    while (current) {
      if ((char *)current == (char *)rc) {
        is_allocated = 0;
        break;
      }
      current = current->next;
    }

    if (is_allocated && rc->count == 0) {
      collect_ref(rc, free_object);
    }
  }
}

void ref_counting_deinit(void) { pool_deinit(&ref_count_allocator); }
