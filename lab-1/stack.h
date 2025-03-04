#define SIZE 10

typedef struct {
  int array[SIZE];
  int head;
} stack;

void init(stack *stack);

int is_empty(stack *stack);

void push(stack *stack, int value);

void pop(stack *stack);

int peek(stack *stack);
