#include "../arraylist.h"
#include "../pool_alloc.h"
#include <assert.h>
#include <string.h>

void test_arraylist_init() {
  PoolAllocator allocator;
  pool_init(&allocator, sizeof(void *), 8);

  ArrayList list;
  arraylist_init(&list, &allocator);

  assert(list.size == 0);
  assert(list.capacity == 4);
  assert(list.data != NULL);
  assert(list.allocator == &allocator);

  arraylist_free(&list);
  pool_deinit(&allocator);
}

void test_arraylist_add() {
  PoolAllocator allocator;
  pool_init(&allocator, sizeof(void *), 8);

  ArrayList list;
  arraylist_init(&list, &allocator);

  int a = 1, b = 2, c = 3;

  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);
  arraylist_add(&list, &c, 2);

  assert(list.size == 3);
  assert(*(int *)arraylist_get(&list, 0) == 1);
  assert(*(int *)arraylist_get(&list, 1) == 2);
  assert(*(int *)arraylist_get(&list, 2) == 3);

  arraylist_free(&list);
  pool_deinit(&allocator);
}

void test_arraylist_grow_capacity() {
  PoolAllocator allocator;
  pool_init(&allocator, sizeof(void *), 8);

  ArrayList list;
  arraylist_init(&list, &allocator);

  int values[10];
  for (int i = 0; i < 10; ++i) {
    values[i] = i + 1;
    arraylist_add(&list, &values[i], list.size);
  }

  assert(list.size == 10);
  assert(list.capacity >= 10); // Минимум 10
  for (int i = 0; i < 10; ++i) {
    assert(*(int *)arraylist_get(&list, i) == i + 1);
  }

  arraylist_free(&list);
  pool_deinit(&allocator);
}

void test_arraylist_delete() {
  PoolAllocator allocator;
  pool_init(&allocator, sizeof(void *), 8);

  ArrayList list;
  arraylist_init(&list, &allocator);

  int a = 1, b = 2, c = 3;
  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);
  arraylist_add(&list, &c, 2);

  arraylist_del(&list, 1); // Удаляем b
  assert(list.size == 2);
  assert(*(int *)arraylist_get(&list, 0) == 1);
  assert(*(int *)arraylist_get(&list, 1) == 3);

  arraylist_free(&list);
  pool_deinit(&allocator);
}

void test_arraylist_invalid_index() {
  PoolAllocator allocator;
  pool_init(&allocator, sizeof(void *), 8);

  ArrayList list;
  arraylist_init(&list, &allocator);

  int a = 1;
  arraylist_add(&list, &a, 0);

  assert(arraylist_get(&list, 100) == NULL); // Выход за границы
  arraylist_del(&list, 100); // Не должен изменить состояние

  arraylist_free(&list);
  pool_deinit(&allocator);
}

void test_arraylist_free_memory() {
  PoolAllocator allocator;
  pool_init(&allocator, sizeof(void *), 8);

  ArrayList list;
  arraylist_init(&list, &allocator);

  int a = 1;
  arraylist_add(&list, &a, 0);

  arraylist_free(&list);
  assert(list.data == NULL);
  assert(list.size == 0);
  assert(list.capacity == 0);

  pool_deinit(&allocator);
}

int main() {
  test_arraylist_init();
  test_arraylist_add();
  test_arraylist_grow_capacity();
  test_arraylist_delete();
  test_arraylist_invalid_index();
  test_arraylist_free_memory();
  return 0;
}