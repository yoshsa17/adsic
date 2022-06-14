#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Stack implementation with linked list
typedef struct Node Node;
struct Node {
  int val;
  Node *next;
};

typedef struct {
  Node *top;
} LStack;

LStack *ls_init();
void ls_destroy(LStack *stack);
void ls_print(LStack *stack);
bool ls_get_is_empty(LStack *stack);
void ls_push(LStack *stack, int val);
int ls_pop(LStack *stack);
int ls_peek(LStack *stack);
void check_allocation(void *p);

void run_all_tests();
void test_init();
void test_push();
void test_peek();
void test_pop();

// Main

int main(int argc, char **argv) {
  run_all_tests();
  return 0;
}

// Functions

LStack *ls_init() {
  LStack *stack = calloc(1, sizeof(LStack));
  check_allocation(stack);
  return stack;
}

void ls_destroy(LStack *stack) {
  Node *cur = stack->top;

  while (cur) {
    Node *temp = cur->next;
    free(cur);
    cur = temp;
  }
  free(stack);
}

void ls_print(LStack *stack) {
  if (ls_get_is_empty(stack)) {
    printf("stack is empty");
    return;
  }

  Node *cur = stack->top;
  printf("top: %p\n", stack->top);
  printf("---------------\n");
  while (cur) {
    printf("(address): %p\n", cur);
    printf("val: %d\n", cur->val);
    printf("next: %p\n", cur->next);
    printf("---------------\n");
    cur = cur->next;
  }
}

bool ls_get_is_empty(LStack *stack) { return stack->top == NULL; }

void ls_push(LStack *stack, int val) {
  Node *new_node = calloc(1, sizeof(Node));
  check_allocation(new_node);
  new_node->val = val;

  if (!ls_get_is_empty(stack)) {
    new_node->next = stack->top;
  }
  stack->top = new_node;
}

int ls_pop(LStack *stack) {
  if (ls_get_is_empty(stack)) {
    printf("Stack is empty");
    exit(EXIT_FAILURE);
  }
  Node *temp = stack->top;
  int val = stack->top->val;
  stack->top = stack->top->next;
  free(temp);
  return val;
}

int ls_peek(LStack *stack) {
  if (ls_get_is_empty(stack)) {
    printf("Stack is empty");
    exit(EXIT_FAILURE);
  }

  return stack->top->val;
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
  test_peek();
  test_pop();
  printf("OK!\n");
}

void test_init() {
  LStack *s = ls_init();
  assert(ls_get_is_empty(s) == true);
  ls_destroy(s);
}

void test_push() {
  LStack *s = ls_init();
  ls_push(s, 10);
  // ls_print(s);
  ls_push(s, 20);
  // ls_print(s);
  assert(ls_get_is_empty(s) == false);
  ls_destroy(s);
}

void test_peek() {
  LStack *s = ls_init();
  ls_push(s, 10);
  assert(ls_peek(s) == 10);
  ls_push(s, 20);
  // ls_print(s);
  assert(ls_peek(s) == 20);
  ls_destroy(s);
}

void test_pop() {
  LStack *s = ls_init();
  ls_push(s, 10);
  ls_push(s, 20);
  assert(ls_pop(s) == 20);
  // ls_print(s);
  assert(ls_peek(s) == 10);
  // ls_print(s);
  ls_destroy(s);
}