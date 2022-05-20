
#ifndef ADSIC_QUEUE_LINKEDLIST_H
#define ADSIC_QUEUE_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct Node Node;
struct Node{
  int val;
  Node *next;
};

typedef struct {
  Node *head;
  Node *tail;
} LQueue;

LQueue *lqueue_init();
void lqueue_destroy(LQueue *q);
bool lqueue_get_is_empty(LQueue *q);
void lqueue_enqueue(LQueue *q, int val);
void lqueue_dequeue(LQueue *q);
void check_allocation(void *p);

// test
void run_all_test();
void test_init();
void test_enqueue();
void test_dequeue();

#endif
