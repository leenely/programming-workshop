#include <assert.h>
#include <stdio.h>

#include "../arraylist.h"
#include "../linear_alloc.h"

void run_simple_tests() {
  linear_allocator *allocator = linear_init(1024);
  ArrayList list;

  arraylist_init(&list, allocator, sizeof(int));

  int a = 10, b = 20, c = 30;

  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);
  arraylist_add(&list, &c, 2);

  assert(*(int *)arraylist_get(&list, 0) == 10);
  assert(*(int *)arraylist_get(&list, 1) == 20);
  assert(*(int *)arraylist_get(&list, 2) == 30);
  assert(list.length == 3);

  arraylist_del(&list, 1);
  assert(list.length == 2);
  assert(*(int *)arraylist_get(&list, 0) == 10);
  assert(*(int *)arraylist_get(&list, 1) == 30);

  arraylist_free(&list);
  linear_deinit(allocator);
}

void run_stack_data_regression_test() {
  linear_allocator *allocator = linear_init(1024);
  ArrayList list;

  arraylist_init(&list, allocator, sizeof(int));

  int stack_data = 40;
  arraylist_add(&list, &stack_data, 0);

  stack_data = 0;

  int list_data = *(int *)arraylist_get(&list, 0);

  assert(list_data == 40);

  arraylist_free(&list);
  linear_deinit(allocator);
}

int main() {
  run_simple_tests();
  run_stack_data_regression_test();
  return 0;
}
