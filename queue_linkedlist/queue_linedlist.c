#include "queue_linkedlist.h"

LQueue *lqueue_init(){
  LQueue *q = calloc(1, sizeof(LQueue));
  check_allocation(q);
  return q;
}

void lqueue_destroy(LQueue *q){

  Node *cur = q->head;
  while(cur) {
    Node *next = cur->next;
    free(cur);
    cur = next;
  }
  free(q);
}

void lqueue_print(LQueue *q){
  Node *cur = q->head;
  printf("HEAD: %p\n", q->head);
  printf("TAIL: %p\n", q->tail);

  while(cur){
    printf("(address): %p\n", cur);
    printf("val: %d\n", cur->val);
    printf("next: %p\n", cur->next);
    printf("------------------\n");
    cur = cur->next; 
  }
}

bool lqueue_get_is_empty(LQueue *q){
  return q->head == NULL; 
}

void lqueue_enqueue(LQueue *q, int val){
  Node *new_node = calloc(1, sizeof(Node));
  check_allocation(new_node);
  new_node->val = val;

  if(lqueue_get_is_empty(q)){
    q->head = q->tail = new_node; 
  } else {
    q->tail->next = new_node;
    q->tail = new_node;
  }
}

void lqueue_dequeue(LQueue *q){
  if(lqueue_get_is_empty(q)){
    printf("queue is empty");
    exit(EXIT_FAILURE);
  }

  Node *temp = q->head;
  q->head = q->head->next;
  
  if(lqueue_get_is_empty(q)){
    q->tail = NULL;
  }

  free(temp);
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
  LQueue *q = lqueue_init();
  assert(lqueue_get_is_empty(q) == true);
  lqueue_destroy(q);
}

void test_enqueue(){
  LQueue *q = lqueue_init();
  lqueue_enqueue(q, 100);
  lqueue_enqueue(q, 200);
  // lqueue_print(q);
  assert(lqueue_get_is_empty(q) == false);
  lqueue_destroy(q);
}

void test_dequeue(){
  LQueue *q = lqueue_init();
  lqueue_enqueue(q, 100);
  lqueue_enqueue(q, 200);
  lqueue_dequeue(q);
  // lqueue_print(q);
  assert(lqueue_get_is_empty(q) == false);
  lqueue_destroy(q);
}

