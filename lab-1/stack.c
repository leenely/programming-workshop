// Стек на основе массива
#include "stack.h"
#include <stdio.h>
#define SIZE 100

void init(stack *stack) {
  stack->head = -1; // -1 поможет в проверке на пустоту
}

int is_empty(stack *stack) { return stack->head == -1; }

void push(stack *stack, int value) {
  if (stack->head + 1 >= SIZE) {
    printf("Стек переполнен\n");
    return;
  }

  stack->head = stack->head + 1;
  stack->array[stack->head] = value;

  printf("Добавлен новый элемент: %d\n", value);
}

void pop(stack *stack) {
  if (is_empty(stack)) {
    printf("Стек пуст\n");
    return -1;
  }

  stack->head = stack->head - 1;
  printf("Элемент удалён\n");
}

// Требуется для тестов
int peek(stack *stack) {
  if (is_empty(stack)) {
    printf("Стек пуст\n");
    return -1;
  }

  int value = stack->array[stack->head];
  printf("Вершина прямо сейчас: %d\n", value);
  return value;
}

int main() {
  stack stack;
  init(&stack);
  push(&stack, 1);
  peek(&stack);
  pop(&stack);
  return 0;
}