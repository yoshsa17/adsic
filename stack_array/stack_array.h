
#ifndef ADSIC_STACK_ARRAY_H
#define ADSIC_STACK_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct {
  int *array;
  int top;
  int size;
} AStack;

AStack *stack_array_init(int capacity);
void stack_array_destroy(AStack *stack);
bool stack_array_get_is_empty(AStack *stack);
void stack_array_push(AStack *stack, int val);
int stack_array_pop(AStack *stack);
int stack_array_peek(AStack *stack);
void check_allocation(void *p);

//// test

void run_all_test();
void test_init();
void test_push();
void test_pop();
void test_peek();

#endif