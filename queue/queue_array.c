#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Queue implementation with fix-sized array
typedef struct {
  int *array;
  int used;
  int size;
} AQueue;

AQueue *aq_init(int capacity);
void aq_destroy(AQueue *q);
void aq_print(AQueue *q);
bool aq_get_is_empty(AQueue *q);
bool aq_get_is_full(AQueue *q);
void aq_enqueue(AQueue *q, int val);
int aq_dequeue(AQueue *q);
void check_allocation(void *p);

void run_all_tests();
void test_init();
void test_enqueue();
void test_dequeue();

// Main

int main(int argc, char **argv) {
  run_all_tests();
  return 0;
}

// Functions

AQueue *aq_init(int capacity) {
  AQueue *q = calloc(1, sizeof(AQueue));
  check_allocation(q);
  q->array = calloc(1, sizeof(int) * capacity);
  check_allocation(q->array);
  q->used = 0;
  q->size = capacity;
  return q;
}

void aq_destroy(AQueue *q) {
  free(q->array);
  free(q);
}

void aq_print(AQueue *q) {
  printf("------\n");
  printf("used: %d\n", q->used);
  printf("size: %d\n", q->size);
  printf("array: \n");

  for (int i = 0; i < q->size; i++) {
    printf("%d: %d\n", i, q->array[i]);
  }
  printf("------\n");
}

bool aq_get_is_empty(AQueue *q) { return q->used == 0; }

bool aq_get_is_full(AQueue *q) { return q->size == q->used; }

void aq_enqueue(AQueue *q, int val) {
  if (aq_get_is_full(q)) {
    printf("queue is full");
    exit(EXIT_FAILURE);
  }

  q->array[q->used] = val;
  ++q->used;
}

int aq_dequeue(AQueue *q) {
  if (aq_get_is_empty(q)) {
    printf("queue is  empty");
    exit(EXIT_FAILURE);
  }

  memmove(q->array, q->array + 1, (q->used - 1) * sizeof(int));
  --q->used;
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
  test_enqueue();
  test_dequeue();
  printf("OK\n");
}

void test_init() {
  AQueue *q = aq_init(5);
  assert(aq_get_is_empty(q) == true);
  aq_destroy(q);
}

void test_enqueue() {
  AQueue *q = aq_init(5);
  aq_enqueue(q, 100);
  aq_enqueue(q, 200);
  // aq_print(q);
  assert(aq_get_is_empty(q) == false);
  aq_enqueue(q, 300);
  aq_enqueue(q, 400);
  aq_enqueue(q, 500);
  // aq_enqueue(q, 600);
  // aq_print(q);
  assert(aq_get_is_full(q) == true);
  aq_destroy(q);
}

void test_dequeue() {
  AQueue *q = aq_init(5);
  aq_enqueue(q, 100);
  aq_enqueue(q, 200);
  aq_dequeue(q);
  // aq_print(q);
  assert(aq_get_is_empty(q) == false);
  aq_destroy(q);
}