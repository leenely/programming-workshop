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
  int output;
  init(&stack, 5);

  push(&stack, 1);
  int result = peek(&stack, &output);

  assert(output == 1);
  assert(result == SUCCESS_CODE);
  free(stack.array);
}

void test_empty_pop() {
  stack stack;
  int output;
  init(&stack, 5);

  int result = pop(&stack, &output);

  assert(result == STACKUNDERFLOW_ERRCODE);
  free(stack.array);
}

void test_pop() {
  stack stack;
  int output;
  init(&stack, 5);

  push(&stack, 1);
  push(&stack, 2);
  pop(&stack, &output);
  int result = peek(&stack, &output);

  assert(output == 1);
  assert(result == SUCCESS_CODE);
  free(stack.array);
}

void test_full_stack() {
  stack stack;
  int output;
  init(&stack, 5);

  for (int i = 1; i <= stack.size + 1; i++) {
    push(&stack, i);
  }
  int result = peek(&stack, &output);

  assert(output == 5);
  assert(is_full(&stack) == true);
  free(stack.array);
}

void test_full_stack_error_output() {
  stack stack;
  int output;
  init(&stack, 1);

  push(&stack, 1);
  int result = push(&stack, 2);

  assert(result == STACKOVERFLOW_ERRCODE);
}

void test_empty_peek() {
  stack stack;
  int output;
  init(&stack, 5);

  int result = peek(&stack, &output);

  assert(result == STACKUNDERFLOW_ERRCODE);
  free(stack.array);
}

int main() {
  test_empty_stack();
  test_push();
  test_empty_pop();
  test_pop();
  test_full_stack();
  test_full_stack_error_output();
  test_empty_peek();
  return 0;
}
