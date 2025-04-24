#include "../list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_init_single_list() {
  single_list list;
  init_single_list(&list);

  assert(list.head == NULL);
}

void test_add_to_beginning() {
  single_list list;
  init_single_list(&list);

  add_to_beginning(&list, 10);
  assert(list.head->item == 10);

  add_to_beginning(&list, 20);
  assert(list.head->item == 20);
}

void test_add_to_end() {
  single_list list;
  init_single_list(&list);

  add_to_end(&list, 10);
  assert(list.head->item == 10);

  add_to_end(&list, 20);
  assert(list.head->item == 10);
}

void test_add_to_middle() {
  single_list list;
  init_single_list(&list);

  add_to_end(&list, 10);
  add_to_end(&list, 20);
  add_to_end(&list, 30);

  add_to_middle(&list, 1, 15);
  assert(find_element(&list, 1) == 15);
  assert(find_element(&list, 2) == 20);
}

void test_find_element() {
  single_list list;
  init_single_list(&list);

  add_to_end(&list, 10);
  add_to_end(&list, 20);
  add_to_end(&list, 30);

  assert(find_element(&list, 0) == 10);
  assert(find_element(&list, 1) == 20);
  assert(find_element(&list, 2) == 30);
}

void test_delete_last() {
  single_list list;
  init_single_list(&list);

  add_to_end(&list, 10);
  add_to_end(&list, 20);
  add_to_end(&list, 30);

  delete_last(&list);
  delete_last(&list);
  delete_last(&list);
  assert(list.head == NULL);
}

void test_count_elements() {
  single_list list;
  init_single_list(&list);

  assert(count_elements(&list) == 0);

  add_to_end(&list, 10);
  add_to_end(&list, 20);
  add_to_end(&list, 30);

  assert(count_elements(&list) == 3);

  delete_last(&list);
  assert(count_elements(&list) == 2);
}

void test_nullpointerexeption() {
  single_list list;
  init_single_list(&list);
  assert(find_element(&list, 0) == NULLPOINTEREXCEPTION_ERRCODE);
}

void test_emptylistexeption() {
  single_list list;
  assert(add_to_middle(&list, -1, 1) == EMPTYLISTEXCEPTION_ERRCODE);
}

int main() {
  test_init_single_list();
  test_add_to_beginning();
  test_add_to_end();
  test_add_to_middle();
  test_find_element();
  test_delete_last();
  test_count_elements();
  test_nullpointerexeption();
  test_emptylistexeption();
  return 0;
}
