#include <stdbool.h>
#define SUCCESS_CODE 0
#define STACKOVERFLOW_ERRCODE -1
#define STACKUNDERFLOW_ERRCODE -2

typedef struct {
  int *array;
  int head;
  int size;
  int is_empty;
} stack;

void init(stack *stack, int size);

bool is_empty(stack *stack);

bool is_full(stack *stack);

int push(stack *stack, int value);

int pop(stack *stack, int *output);

int peek(stack *stack, int *output);
