#include "../garbage_collector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_ref_counting_init() {
  ref_counting_init(10);
  void *obj = malloc(1);
  ref_count_t *rc = ref_count_create(obj, NULL, NULL);
  assert(rc != NULL);
  ref_count_dec(rc);
}

void test_ref_count_create() {
  int *obj = malloc(sizeof(int));
  *obj = 42;

  ref_count_t *rc = ref_count_create(obj, NULL, NULL);
  assert(rc != NULL);
  assert(rc->count == 1);
  assert(rc->object == obj);

  ref_count_dec(rc);
}

void test_ref_count_inc() {
  int *obj = malloc(sizeof(int));
  *obj = 42;

  ref_count_t *rc = ref_count_create(obj, NULL, NULL);
  ref_count_inc(rc);
  assert(rc->count == 2);

  ref_count_dec(rc);
  ref_count_dec(rc);
}

void test_ref_count_dec() {
  int *obj = malloc(sizeof(int));
  *obj = 42;

  ref_count_t *rc = ref_count_create(obj, NULL, NULL);
  ref_count_dec(rc);
}

void test_ref_count_create_null_object() {
  ref_count_t *rc = ref_count_create(NULL, NULL, NULL);
  assert(rc == NULL);
}

void test_ref_counting_deinit() {
  ref_counting_init(10);
  ref_counting_deinit();
}

void test_no_memory_leak() {
  ref_counting_init(10);
  int *obj = malloc(sizeof(int));
  *obj = 42;

  ref_count_t *rc = ref_count_create(obj, NULL, NULL);
  ref_count_dec(rc);
  ref_counting_deinit();
}

int main() {
  test_ref_counting_init();
  test_ref_count_create();
  test_ref_count_inc();
  test_ref_count_dec();
  test_ref_count_create_null_object();
  test_ref_counting_deinit();
  test_no_memory_leak();

  return 0;
}
