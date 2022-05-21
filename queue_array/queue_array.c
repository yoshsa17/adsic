#include "queue_array.h"

AQueue *aqueue_init(int capacity){
  AQueue *q = calloc(1, sizeof(AQueue));
  check_allocation(q);
  q->array = calloc(1, sizeof(int) * capacity);
  check_allocation(q->array);
  q->used = 0;
  q->size = capacity;
  return q;
}

void aqueue_destroy(AQueue *q){
  free(q->array);
  free(q);
}

void aqueue_print(AQueue *q) {
  printf("------\n");
  printf("used: %d\n", q->used);
  printf("size: %d\n", q->size);
  printf("array: \n");

  for (int i = 0; i < q->size; i++){
    printf("%d: %d\n",  i, q->array[i]);
  }
  printf("------\n");
}

bool aqueue_get_is_empty(AQueue *q) {
  return q->used == 0;
}

bool aqueue_get_is_full(AQueue *q){
  return q->size == q->used;
}

void aqueue_enqueue(AQueue *q, int val){
  if(aqueue_get_is_full(q)){
    printf("queue is full");
    exit(EXIT_FAILURE);
  }

  q->array[q->used] = val;
  ++q->used;
}

int aqueue_dequeue(AQueue *q){
  if(aqueue_get_is_empty(q)){
    printf("queue is  empty");
    exit(EXIT_FAILURE);
  }

  memmove(q->array, q->array + 1, (q->used - 1) * sizeof(int));
  --q->used;
}

void check_allocation(void *p) {
  if(p == NULL) {
    fprintf(stderr, "Unable to allocate memory");
    exit(EXIT_FAILURE);
  }
}

// test

void run_all_test(){
  test_init();
  test_enqueue();
  test_dequeue();
  printf("OK");
}

void test_init(){
  AQueue *q = aqueue_init(5);
  assert(aqueue_get_is_empty(q) == true);
  aqueue_destroy(q);
}

void test_enqueue(){
  AQueue *q = aqueue_init(5);
  aqueue_enqueue(q, 100);
  aqueue_enqueue(q, 200);
  // aqueue_print(q);
  assert(aqueue_get_is_empty(q) == false);
  aqueue_enqueue(q, 300);
  aqueue_enqueue(q, 400);
  aqueue_enqueue(q, 500);
  // aqueue_enqueue(q, 600);
  // aqueue_print(q);
  assert(aqueue_get_is_full(q) == true);
  aqueue_destroy(q);
}

void test_dequeue(){
  AQueue *q = aqueue_init(5);
  aqueue_enqueue(q, 100);
  aqueue_enqueue(q, 200);
  aqueue_dequeue(q);
  // aqueue_print(q);
  assert(aqueue_get_is_empty(q) == false);
  aqueue_destroy(q);
}