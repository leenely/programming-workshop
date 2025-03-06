#include "../stack.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void test_empty_stack() {
  stack stack;
  init(&stack, 10);

  bool result = is_empty(&stack);

  assert(result == true);
  free(stack.array);
}

void test_push() {
  stack stack;
  init(&stack, 10);

  push(&stack, 1);

  assert(peek(&stack) == 1);
  free(stack.array);
}

void test_pop() {
  stack stack;
  init(&stack, 10);

  push(&stack, 1);
  push(&stack, 2);
  pop(&stack);

  assert(peek(&stack) == 1);
  free(stack.array);
}

void test_multiple_push_and_pop() {
  stack stack;
  init(&stack, 10);

  push(&stack, 1);
  push(&stack, 2);
  push(&stack, 3);
  assert(peek(&stack) == 3);

  pop(&stack);
  assert(peek(&stack) == 2);

  push(&stack, 4);
  pop(&stack);
  pop(&stack);
  assert(peek(&stack) == 1);
  free(stack.array);
}

void test_full_stack() {
  stack stack;
  init(&stack, 10);

  // Переполняем стек на один элемент
  for (int i = 1; i <= stack.size + 1; i++) {
    push(&stack, i);
  }

  assert(peek(&stack) == 10);
  free(stack.array);
}

int main() {
  test_empty_stack();
  test_push();
  test_pop();
  test_multiple_push_and_pop();
  test_full_stack();
  return 0;
}
