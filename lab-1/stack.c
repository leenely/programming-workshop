// Стек на основе массива
#include "stack.h"
#include <stdio.h>
#define SIZE 10

void init(stack *stack) { stack->head = -1; }

int is_empty(stack *stack) { return stack->head == -1; }

void push(stack *stack, int value) {
  if (stack->head + 1 >= SIZE) {
    printf("Стек переполнен\n");
    return;
  }

  stack->head = stack->head + 1;
  stack->array[stack->head] = value;
}

void pop(stack *stack) {
  if (is_empty(stack)) {
    printf("Стек пуст\n");
    return;
  }
  stack->head = stack->head - 1;
}

int peek(stack *stack) {
  if (is_empty(stack)) {
    printf("Стек пуст\n");
    return -1;
  }

  return stack->array[stack->head];
}
