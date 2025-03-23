#include "stack.h"
#include <stdlib.h>

void init(stack *stack, int size) {
  stack->head = -1;
  stack->size = size;
  stack->array = (int *)malloc(sizeof(int) * size);
  stack->is_empty = 1;
}

int is_empty(stack *stack) { return stack->is_empty; }

void push(stack *stack, int value) {
  if (stack->head + 1 >= stack->size) {
    return STACKOVERFLOW_ERRCODE;
  }

  stack->head = stack->head + 1;
  stack->array[stack->head] = value;
  stack->is_empty = 0;
}

void pop(stack *stack) {
  if (is_empty(stack)) {
    return STACKUNDERFLOW_ERRCODE;
  }

  stack->head = stack->head - 1;
  if (stack->head == -1) {
    stack->is_empty = 1;
  }
}

int peek(stack *stack) {
  if (is_empty(stack)) {
    return STACKUNDERFLOW_ERRCODE;
  }

  return stack->array[stack->head];
}
