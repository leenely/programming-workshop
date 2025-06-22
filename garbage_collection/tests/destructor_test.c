#include "../garbage_collector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_ref_count_create_without_destructor() {
  ref_counting_init(10);
  int *obj = malloc(sizeof(int));
  *obj = 10;

  ref_count_t *rc = ref_count_create(obj, NULL, NULL);
  assert(rc != NULL);
  assert(rc->count == 1);
  assert(rc->object == obj);
  assert(rc->destructor == NULL);

  ref_count_dec(rc);
  ref_counting_deinit();
}

void custom_destructor(void *ptr) {
  printf("Кастомный деструктор отработал\n");
  free(ptr);
}

void test_ref_count_create_with_custom_destructor() {
  ref_counting_init(10);
  int *obj = malloc(sizeof(int));
  *obj = 10;

  ref_count_t *rc = ref_count_create(obj, NULL, custom_destructor);
  assert(rc != NULL);
  assert(rc->count == 1);
  assert(rc->object == obj);
  assert(rc->destructor != NULL);

  ref_count_dec(rc);
  ref_counting_deinit();
}

void test_ref_count_create_with_custom_destructor_and_null_object() {
  ref_counting_init(10);
  ref_count_t *rc = ref_count_create(NULL, NULL, custom_destructor);

  assert(rc == NULL);

  ref_count_dec(rc);
  ref_counting_deinit();
}

void custom_constructor(void *object) {
  printf("Кастомный конструктор отработал\n");
  *(int *)object = 10;
}

void test_ref_count_create_with_custom_constructor() {
  ref_counting_init(10);
  int *obj = malloc(sizeof(int));

  ref_count_t *rc = ref_count_create(obj, custom_constructor, NULL);
  assert(rc != NULL);
  assert(*(int *)rc->object == 10);

  ref_count_dec(rc);
  ref_counting_deinit();
}

int main() {
  test_ref_count_create_without_destructor();
  test_ref_count_create_with_custom_destructor();
  test_ref_count_create_with_custom_destructor_and_null_object();
  test_ref_count_create_with_custom_constructor();

  return 0;
}