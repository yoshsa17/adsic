#include "stack_linkedlist.h"


LStack *stack_linked_list_init(){
  LStack *stack = calloc(1, sizeof(LStack));
  check_allocation(stack);
  return stack;
}

void stack_linked_list_destroy(LStack *stack) {
  Node *cur = stack->top;

  while(cur){
    Node *temp = cur->next;
    free(cur);
    cur =  temp;
  }
  free(stack);
}

void stack_linked_list_print(LStack *stack){
  if(stack_linked_list_get_is_empty(stack)){
    printf("stack is empty");
    return;
  }

  Node *cur = stack->top;
  printf("top: %p\n", stack->top);
  printf("---------------\n");
  while(cur){
    printf("(address): %p\n", cur);
    printf("val: %d\n", cur->val);
    printf("next: %p\n", cur->next);
    printf("---------------\n");
    cur = cur->next;
  }
}

bool stack_linked_list_get_is_empty(LStack *stack) {
  return stack->top == NULL;
}

void stack_linked_list_push(LStack *stack, int val) {
  Node *new_node = calloc(1, sizeof(Node));
  check_allocation(new_node);
  new_node->val = val;

  if(!stack_linked_list_get_is_empty(stack)) {
    new_node->next = stack->top;
  }
  stack->top = new_node;
}

int stack_linked_list_pop(LStack *stack) {
  if(stack_linked_list_get_is_empty(stack)){
    printf("Stack is empty");
    exit(EXIT_FAILURE);
  }
  Node *temp = stack->top;
  int val = stack->top->val;
  stack->top = stack->top->next;
  free(temp);
  return val;
}

int stack_linked_list_peek(LStack *stack) {
  if(stack_linked_list_get_is_empty(stack)){
    printf("Stack is empty");
    exit(EXIT_FAILURE);
  }

  return stack->top->val;
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
  test_peek();
  test_pop();
  printf("OK!");
}

void test_init(){
  LStack *s = stack_linked_list_init();
  assert(stack_linked_list_get_is_empty(s) == true);
  stack_linked_list_destroy(s);
}

void test_push(){
  LStack *s = stack_linked_list_init();
  stack_linked_list_push(s, 10);
  // stack_linked_list_print(s);
  stack_linked_list_push(s, 20);
  // stack_linked_list_print(s);
  assert(stack_linked_list_get_is_empty(s) == false);
  stack_linked_list_destroy(s);
}

void test_peek(){
  LStack *s = stack_linked_list_init();
  stack_linked_list_push(s, 10);
  assert(stack_linked_list_peek(s) == 10);
  stack_linked_list_push(s, 20);
  // stack_linked_list_print(s);
  assert(stack_linked_list_peek(s) == 20);
  stack_linked_list_destroy(s);
}

void test_pop(){
  LStack *s = stack_linked_list_init();
  stack_linked_list_push(s, 10);
  stack_linked_list_push(s, 20);
  assert(stack_linked_list_pop(s) == 20);
  // stack_linked_list_print(s);
  assert(stack_linked_list_peek(s) == 10);
  // stack_linked_list_print(s);
  stack_linked_list_destroy(s);
}