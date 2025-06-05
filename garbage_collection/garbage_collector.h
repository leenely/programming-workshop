#include "../memory/pool_alloc.h"

typedef struct ref_count_t {
  size_t count;
  void *object;
  void (*destructor)(void *);
} ref_count_t;

void ref_counting_init(size_t max_objects);
ref_count_t *ref_count_create(void *object, void (*destructor)(void *));
void ref_count_inc(ref_count_t *rc);
void ref_count_dec(ref_count_t *rc);
void ref_counting_deinit(void);
