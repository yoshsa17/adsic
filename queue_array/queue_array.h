
#ifndef ADSIC_QUEUE_ARRAY_H
#define ADSIC_QUEUE_ARRAY_H

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include <string.h>

typedef struct {
  int *array;
  int used;
  int size;
} AQueue;

AQueue *aqueue_init(int capacity);
void aqueue_destroy(AQueue *q);
void aqueue_print(AQueue *q);
bool aqueue_get_is_empty(AQueue *q);
bool aqueue_get_is_full(AQueue *q);
void aqueue_enqueue(AQueue *q, int val);
int aqueue_dequeue(AQueue *q);
void check_allocation(void *p);

// test

void run_all_test();
void test_init();
void test_enqueue();
void test_dequeue();

#endif