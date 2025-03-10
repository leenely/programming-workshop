#include <stdbool.h>

typedef struct {
  int *array;
  int head;
  int size;
  int is_empty;
} stack;

void init(stack *stack, int size);

int is_empty(stack *stack);

void push(stack *stack, int value);

void pop(stack *stack);

int peek(stack *stack);
