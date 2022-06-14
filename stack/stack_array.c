#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Stack implementation with fixed-size array
typedef struct {
  int *array;
  int top;
  int size;
} AStack;

AStack *as_init(int capacity);
void as_destroy(AStack *stack);
bool as_get_is_empty(AStack *stack);
void as_push(AStack *stack, int val);
int as_pop(AStack *stack);
int as_peek(AStack *stack);
void check_allocation(void *p);

void run_all_tests();
void test_init();
void test_push();
void test_pop();
void test_peek();

// Main

int main(int argc, char **argv) {
  run_all_tests();
  return 0;
}

// Functions

AStack *as_init(int capacity) {
  AStack *stack = calloc(1, sizeof(AStack));
  check_allocation(stack);
  stack->array = calloc(1, sizeof(int) * capacity);
  check_allocation(stack->array);
  stack->top = -1;
  stack->size = capacity;
  return stack;
}

void as_destroy(AStack *stack) {
  free(stack->array);
  free(stack);
}

bool as_get_is_empty(AStack *stack) { return stack->top == -1; }

void as_push(AStack *stack, int val) {
  if (stack->size == stack->top + 1) {
    printf("Unable to push");
    exit(EXIT_FAILURE);
  }
  ++stack->top;
  stack->array[stack->top] = val;
}

int as_pop(AStack *stack) {
  if (as_get_is_empty(stack)) {
    printf("stack is empty");
    exit(EXIT_FAILURE);
  }

  return stack->array[stack->top--];
}

int as_peek(AStack *stack) {
  if (as_get_is_empty(stack)) {
    printf("stack is empty");
    exit(EXIT_FAILURE);
  }

  return stack->array[stack->top];
}

void check_allocation(void *p) {
  if (p == NULL) {
    fprintf(stderr, "Unable to allocate memory");
    exit(EXIT_FAILURE);
  }
}

// Tests

void run_all_tests() {
  test_init();
  test_push();
  test_pop();
  test_peek();
  printf("OK\n");
}

void test_init() {
  AStack *s = as_init(5);
  assert(as_get_is_empty(s) == true);
  as_destroy(s);
}

void test_push() {
  AStack *s = as_init(5);
  as_push(s, 10);
  assert(as_get_is_empty(s) == false);
  as_destroy(s);
}

void test_peek() {
  AStack *s = as_init(5);
  as_push(s, 10);
  assert(as_peek(s) == 10);
  assert(as_get_is_empty(s) == false);
  as_destroy(s);
}

void test_pop() {
  AStack *s = as_init(5);
  as_push(s, 10);
  as_push(s, 20);
  assert(as_pop(s) == 20);
  assert(as_peek(s) == 10);
  as_destroy(s);
}