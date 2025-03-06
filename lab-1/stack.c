// Стек на основе массива
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void init(stack *stack, int size) {
  stack->head = -1;
  stack->size = size;
  stack->array = (int *)malloc(sizeof(int) * size);
}

int is_empty(stack *stack) { return stack->head == -1; }

void push(stack *stack, int value) {
  if (stack->head + 1 >= stack->size) {
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
