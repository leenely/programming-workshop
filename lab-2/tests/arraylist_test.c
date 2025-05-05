#include "../arraylist.h"
#include "pool_alloc.h"
#include <assert.h>

void test_arraylist_init() {
  PoolAllocator allocator;
  pool_init(&allocator, 32, 1024);

  ArrayList list;

  arraylist_init(&list, &allocator);

  assert(list.size == 0);
  assert(list.capacity == 0);
  assert(list.data == NULL);
  assert(list.allocator == &allocator);

  arraylist_free(&list);
  pool_deinit(&allocator);
}

void test_arraylist_add() {
  PoolAllocator allocator;
  pool_init(&allocator, 32, 1024);

  ArrayList list;
  arraylist_init(&list, &allocator);

  int values[] = {10, 20, 30};

  arraylist_add(&list, &values[0], 0);
  assert(list.size == 1);
  assert(*(int *)arraylist_get(&list, 0) == 10);

  arraylist_add(&list, &values[1], 1);
  assert(list.size == 2);
  assert(*(int *)arraylist_get(&list, 1) == 20);

  arraylist_add(&list, &values[2], 1);
  assert(list.size == 3);
  assert(*(int *)arraylist_get(&list, 1) == 30);

  arraylist_free(&list);
  pool_deinit(&allocator);
}

void test_arraylist_get() {
  PoolAllocator allocator;
  pool_init(&allocator, 32, 1024);

  ArrayList list;
  arraylist_init(&list, &allocator);

  char *str = "test";
  arraylist_add(&list, str, 0);

  char *result = arraylist_get(&list, 0);

  assert(result != NULL);
  assert(strcmp(result, "test") == 0);

  arraylist_free(&list);
  pool_deinit(&allocator);
}

void test_arraylist_del() {
  PoolAllocator allocator;
  pool_init(&allocator, 32, 1024);

  ArrayList list;
  arraylist_init(&list, &allocator);

  int values[] = {1, 2, 3, 4};
  for (int i = 0; i < 4; i++) {
    arraylist_add(&list, &values[i], i);
  }
  arraylist_del(&list, 1);
  assert(list.size == 3);
  assert(*(int *)arraylist_get(&list, 0) == 1);
  assert(*(int *)arraylist_get(&list, 1) == 3);

  arraylist_del(&list, 0);
  assert(list.size == 2);
  assert(*(int *)arraylist_get(&list, 0) == 3);

  arraylist_free(&list);
  pool_deinit(&allocator);
}

void test_arraylist_free() {
  PoolAllocator allocator;
  pool_init(&allocator, 32, 1024);

  ArrayList list;
  arraylist_init(&list, &allocator);

  float f = 3.14f;
  arraylist_add(&list, &f, 0);

  arraylist_free(&list);

  assert(list.size == 0);
  assert(list.capacity == 0);
  assert(list.data == NULL);

  pool_deinit(&allocator);
}

int main() {
  test_arraylist_init();
  test_arraylist_add();
  test_arraylist_get();
  test_arraylist_del();
  test_arraylist_free();
  return 0;
}
