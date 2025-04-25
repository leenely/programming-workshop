#include <assert.h>
#include <stdio.h>

#include "../arraylist.h"
#include "../linear_alloc.h"

void run_simple_tests() {
  ArrayList list;
  arraylist_init(&list, linear_init(1024));

  int a = 10, b = 20, c = 30;

  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);
  arraylist_add(&list, &c, 2);

  assert(*(int *)arraylist_get(&list, 0) == 10);
  assert(*(int *)arraylist_get(&list, 1) == 20);
  assert(*(int *)arraylist_get(&list, 2) == 30);
  assert(list.size == 3);

  arraylist_del(&list, 1);
  assert(list.size == 2);
  assert(*(int *)arraylist_get(&list, 0) == 10);
  assert(*(int *)arraylist_get(&list, 1) == 30);

  arraylist_free(&list);
  linear_deinit(linear_init(1024));
}

int main() {
  run_simple_tests();
  return 0;
}
