#include <stdbool.h>
#define STACKOVERFLOW_ERRCODE -1
#define STACKUNDERFLOW_ERRCODE -2
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
