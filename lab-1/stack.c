#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>

void init(stack *stack, int size) {
  stack->head = -1;
  stack->size = size;
  stack->array = (int *)malloc(sizeof(int) * size);
}

bool is_empty(stack *stack) { return stack->head == -1; }

bool is_full(stack *stack) { return stack->head == stack->size - 1; }

int push(stack *stack, int value) {
  if (is_full(stack)) {
    return STACKOVERFLOW_ERRCODE;
  }

  stack->head = stack->head + 1;
  stack->array[stack->head] = value;
}

int pop(stack *stack) {
  if (is_empty(stack)) {
    return STACKUNDERFLOW_ERRCODE;
  }

  stack->head = stack->head - 1;
  return stack->array[stack->head];
}

int peek(stack *stack) {
  if (is_empty(stack)) {
    return STACKUNDERFLOW_ERRCODE;
  }

  return stack->array[stack->head];
}
