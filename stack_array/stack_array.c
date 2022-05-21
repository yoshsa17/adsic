
#include "stack_array.h"

AStack *stack_array_init(int capacity) {
  AStack *stack = calloc(1, sizeof(AStack));
  check_allocation(stack);
  stack->array = calloc(1, sizeof(int) * capacity);
  check_allocation(stack->array);
  stack->top = -1;
  stack->size = capacity;
  return stack;
}

void stack_array_destroy(AStack *stack) {
  free(stack->array);
  free(stack);
}

bool stack_array_get_is_empty(AStack *stack) {
  return stack->top == -1; 
}

void stack_array_push(AStack *stack, int val){
  if(stack->size == stack->top + 1){
    printf("Unable to push");
    exit(EXIT_FAILURE);
  }
  ++stack->top;
  stack->array[stack->top] = val;
}

int stack_array_pop(AStack *stack) {
  if(stack_array_get_is_empty(stack)){
    printf("stack is empty");
    exit(EXIT_FAILURE);
  }
  
  return stack->array[stack->top--];
}

int stack_array_peek(AStack *stack) {
  if(stack_array_get_is_empty(stack)){
    printf("stack is empty");
    exit(EXIT_FAILURE);
  }
  
  return stack->array[stack->top];
}

void check_allocation(void *p) {
  if(p == NULL) {
    fprintf(stderr, "Unable to allocate memory");
    exit(EXIT_FAILURE);
  }
}

//// test

void run_all_test(){
  test_init();
  test_push();
  test_pop();
  test_peek();
  printf("OK!");
}

void test_init(){
  AStack *s = stack_array_init(5);
  assert(stack_array_get_is_empty(s) == true);
  stack_array_destroy(s);
}

void test_push(){
  AStack *s = stack_array_init(5);
  stack_array_push(s, 10);
  assert(stack_array_get_is_empty(s) == false);
  stack_array_destroy(s);
}

void test_peek(){
  AStack *s = stack_array_init(5);
  stack_array_push(s, 10);
  assert(stack_array_peek(s) == 10);
  assert(stack_array_get_is_empty(s) == false);
  stack_array_destroy(s);
}

void test_pop(){
  AStack *s = stack_array_init(5);
  stack_array_push(s, 10);
  stack_array_push(s, 20);
  assert(stack_array_pop(s) == 20);
  assert(stack_array_peek(s) == 10);
  stack_array_destroy(s);
}