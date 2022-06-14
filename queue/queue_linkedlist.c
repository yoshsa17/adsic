#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Queue implementation with linked list
typedef struct Node Node;
struct Node {
  int val;
  Node *next;
};

typedef struct {
  Node *head;
  Node *tail;
} LQueue;

LQueue *lq_init();
void lq_destroy(LQueue *q);
bool lq_get_is_empty(LQueue *q);
void lq_enqueue(LQueue *q, int val);
void lq_dequeue(LQueue *q);
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

LQueue *lq_init() {
  LQueue *q = calloc(1, sizeof(LQueue));
  check_allocation(q);
  return q;
}

void lq_destroy(LQueue *q) {
  Node *cur = q->head;
  while (cur) {
    Node *next = cur->next;
    free(cur);
    cur = next;
  }
  free(q);
}

void lq_print(LQueue *q) {
  Node *cur = q->head;
  printf("HEAD: %p\n", q->head);
  printf("TAIL: %p\n", q->tail);

  while (cur) {
    printf("(address): %p\n", cur);
    printf("val: %d\n", cur->val);
    printf("next: %p\n", cur->next);
    printf("------------------\n");
    cur = cur->next;
  }
}

bool lq_get_is_empty(LQueue *q) { return q->head == NULL; }

void lq_enqueue(LQueue *q, int val) {
  Node *new_node = calloc(1, sizeof(Node));
  check_allocation(new_node);
  new_node->val = val;

  if (lq_get_is_empty(q)) {
    q->head = q->tail = new_node;
  } else {
    q->tail->next = new_node;
    q->tail = new_node;
  }
}

void lq_dequeue(LQueue *q) {
  if (lq_get_is_empty(q)) {
    printf("queue is empty");
    exit(EXIT_FAILURE);
  }

  Node *temp = q->head;
  q->head = q->head->next;

  if (lq_get_is_empty(q)) {
    q->tail = NULL;
  }

  free(temp);
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
  LQueue *q = lq_init();
  assert(lq_get_is_empty(q) == true);
  lq_destroy(q);
}

void test_enqueue() {
  LQueue *q = lq_init();
  lq_enqueue(q, 100);
  lq_enqueue(q, 200);
  // lq_print(q);
  assert(lq_get_is_empty(q) == false);
  lq_destroy(q);
}

void test_dequeue() {
  LQueue *q = lq_init();
  lq_enqueue(q, 100);
  lq_enqueue(q, 200);
  lq_dequeue(q);
  // lq_print(q);
  assert(lq_get_is_empty(q) == false);
  lq_destroy(q);
}
