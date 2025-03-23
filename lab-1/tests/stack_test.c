#include "../stack.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

void test_empty_stack() {
  stack stack;
  init(&stack, 5);

  bool result = is_empty(&stack);

  assert(result == true);
  free(stack.array);
}

void test_push() {
  stack stack;
  init(&stack, 5);

  push(&stack, 1);
  int result = peek(&stack);

  assert(result == 1);
  free(stack.array);
}

void test_empty_pop() {
  stack stack;
  init(&stack, 5);

  int result = pop(&stack);

  assert(result == STACKUNDERFLOW_ERRCODE);
  free(stack.array);
}

void test_pop() {
  stack stack;
  init(&stack, 5);

  push(&stack, 1);
  push(&stack, 2);
  pop(&stack);
  int result = peek(&stack);

  assert(result == 1);
  free(stack.array);
}

void test_full_stack() {
  stack stack;
  init(&stack, 5);

  for (int i = 1; i <= stack.size + 1; i++) {
    push(&stack, i);
  }
  int result = peek(&stack);

  assert(result == 5);
  assert(is_full(&stack) == true);
  free(stack.array);
}

void test_empty_peek() {
  stack stack;
  init(&stack, 5);

  int result = peek(&stack);

  assert(result == STACKUNDERFLOW_ERRCODE);
  free(stack.array);
}

int main() {
  test_empty_stack();
  test_push();
  test_empty_pop();
  test_pop();
  test_full_stack();
  test_empty_peek();
  return 0;
}
