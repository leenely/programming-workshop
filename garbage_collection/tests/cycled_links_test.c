#include "../garbage_collector.h"
#include <assert.h>
#include <stdlib.h>

static void test_cyclic_pair() {
  ref_counting_init(2);

  int *obj1 = malloc(sizeof(int));
  int *obj2 = malloc(sizeof(int));

  ref_count_t *rc1 = ref_count_create(obj1, NULL, NULL);
  ref_count_t *rc2 = ref_count_create(obj2, NULL, NULL);

  rc1->object = rc2;
  rc2->object = rc1;

  assert(rc1->count == 1);
  assert(rc2->count == 1);

  garbage_collect(free);

  assert(rc1->count == 1);
  assert(rc2->count == 1);

  collect_cycles(free);

  ref_counting_deinit();
}

int main() {
  test_cyclic_pair();
  return 0;
}
