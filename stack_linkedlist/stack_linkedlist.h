#ifndef ADSIC_STACK_LINKEDLIST_H
#define ADSIC_STACK_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct Node Node;
struct Node {
  int val;
  Node *next;
};

typedef struct {
  Node *top; 
} LStack;


LStack *stack_linked_list_init();
void stack_linked_list_destroy(LStack *stack);
void stack_linked_list_print(LStack *stack);
bool stack_linked_list_get_is_empty(LStack *stack);
void stack_linked_list_push(LStack *stack, int val);
int stack_linked_list_pop(LStack *stack);
int stack_linked_list_peek(LStack *stack);
void check_allocation(void *p);

void run_all_test();
void test_init();
void test_push();
void test_peek();
void test_pop();

#endif