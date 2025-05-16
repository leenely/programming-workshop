#include "../hashtable.h"

 feature/lab-2_hashtable
void test_basic_insert_get() {
  PoolAllocator alloc;
  pool_init(&alloc, sizeof(HashElem), 10);
  HashTable table;
  hashtable_init(&table, 5, &alloc, sizeof(int));

  int value1 = 42;
  int value2 = -3;

  hashtable_insert(&table, "answer1", &value1);
  hashtable_insert(&table, "answer2", &value2);

  assert(*(int *)hashtable_get(&table, "answer1") == 42);
  assert(*(int *)hashtable_get(&table, "answer2") == -3);

  hashtable_free(&table);
  pool_deinit(&alloc);
}

void test_collision_handling() {
  PoolAllocator alloc;
  pool_init(&alloc, sizeof(HashElem), 10);
  HashTable table;
  hashtable_init(&table, 1, &alloc, sizeof(char));
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
  hashtable_init(&table, 5, &alloc, sizeof(int));

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
  hashtable_init(&table, 5, &alloc, sizeof(int));

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
=======
int main() { return 0; }
 master
