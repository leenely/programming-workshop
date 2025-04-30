#include "../hashtable.h"
#include "../pool_alloc.h"
#include <assert.h>

void test_basic_insert_get() {
  PoolAllocator alloc;
  pool_init(&alloc, sizeof(HashElem), 10);
  HashTable table;
  hashtable_init(&table, 5, &alloc);

  int value1 = 42;
  char value2 = 'a';

  hashtable_insert(&table, "answer", &value1);
  hashtable_insert(&table, "char", &value2);

  assert(*(int *)hashtable_get(&table, "answer") == 42);
  assert(*(char *)hashtable_get(&table, "char") == 'a');

  hashtable_free(&table);
  pool_deinit(&alloc);
}

void test_collision_handling() {
  PoolAllocator alloc;
  pool_init(&alloc, sizeof(HashElem), 10);
  HashTable table;
  hashtable_init(&table, 1, &alloc);

  char *str1 = "first";
  char *str2 = "second";

  hashtable_insert(&table, str1, str1);
  hashtable_insert(&table, str2, str2);

  assert(hashtable_get(&table, str1) == str1);
  assert(hashtable_get(&table, str2) == str2);

  hashtable_free(&table);
  pool_deinit(&alloc);
}

void test_update_value() {
  PoolAllocator alloc;
  pool_init(&alloc, sizeof(HashElem), 5);
  HashTable table;
  hashtable_init(&table, 5, &alloc);

  int value1 = 100;
  int value2 = 200;

  hashtable_insert(&table, "test", &value1);
  hashtable_insert(&table, "test", &value2);

  assert(*(int *)hashtable_get(&table, "test") == 200);

  hashtable_free(&table);
  pool_deinit(&alloc);
}

void test_delete() {
  PoolAllocator alloc;
  pool_init(&alloc, sizeof(HashElem), 5);
  HashTable table;
  hashtable_init(&table, 5, &alloc);

  int value = 123;
  hashtable_insert(&table, "to_delete", &value);

  assert(hashtable_get(&table, "to_delete") != NULL);
  hashtable_del(&table, "to_delete");
  assert(hashtable_get(&table, "to_delete") == NULL);

  hashtable_free(&table);
  pool_deinit(&alloc);
}

int main() {
  test_basic_insert_get();
  test_collision_handling();
  test_update_value();
  test_delete();
  return 0;
}
