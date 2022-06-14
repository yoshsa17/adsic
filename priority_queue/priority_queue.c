
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define QueueCapacity 20 + 1

// Priority Queue using Binary heap
typedef struct {
  int data[QueueCapacity];
  int size;
  int capacity;
} MaxHeap;

MaxHeap *pq_init();
void pq_insert(MaxHeap *h, int val);
void pq_print_data(MaxHeap *h);
void pq_shift_up(MaxHeap *h, int index);
int pq_get_max(MaxHeap *h);
int pq_extract_max(MaxHeap *h);
void pq_shift_down(MaxHeap *h, int index);
int pq_remove(MaxHeap *h, int index);
void pq_change_priority(MaxHeap *h, int index, int priority);

int pq_get_parent(int index);
int pq_get_lchild(int index);
int pq_get_rchild(int index);

void run_all_tests();
void test_insert();
void test_execute_max();
void test_remove();
void test_change_priority();

// Main

int main() {
  run_all_tests();
  return 0;
}

// Functions

// parent = child / 2
// leftChild = parent * 2
// rightChild = parent * 2 + 1
//
//           1
//         /   \
//       2      3
//     /  \    /  \
//    4    5  6    7

int pq_get_parent(int index) { return index / 2; }
int pq_get_lchild(int index) { return 2 * index; };
int pq_get_rchild(int index) { return 2 * index + 1; };

MaxHeap *pq_init() {
  MaxHeap *h = malloc(sizeof(MaxHeap));
  // printf("%d", h->data[0]);
  h->capacity = QueueCapacity;
  h->size = 0;
  return h;
}

void pq_destroy(MaxHeap *h) { free(h); }
int pq_get_size(MaxHeap *h) { return h->size; }

void pq_swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void pq_insert(MaxHeap *h, int val) {
  if (h->size == h->capacity) {
    printf("Heap is full\n");
    exit(EXIT_FAILURE);
  }
  ++h->size;
  h->data[h->size] = val;
  pq_shift_up(h, h->size);
}

void pq_shift_up(MaxHeap *h, int index) {
  while (index > 1 && h->data[pq_get_parent(index)] < h->data[index]) {
    pq_swap(h->data + pq_get_parent(index), h->data + index);
    index = pq_get_parent(index);
  }
};

void pq_print_data(MaxHeap *h) {
  for (int i = 1; i <= h->size; ++i) {
    // printf("%4d", h->data[i]);
    printf("%d\n", h->data[i]);
  }
  printf("--------------\n");
}

int pq_get_max(MaxHeap *h) { return h->data[1]; };

int pq_execute_max(MaxHeap *h) {
  int max = h->data[1];
  h->data[1] = h->data[h->size];
  --h->size;
  pq_shift_down(h, 1);
  return max;
}

void pq_shift_down(MaxHeap *h, int index) {
  int maxIndex = index;

  int lchild = pq_get_lchild(index);
  if (lchild <= h->size && h->data[lchild] > h->data[maxIndex]) {
    maxIndex = lchild;
  }
  int rchild = pq_get_rchild(index);
  if (rchild <= h->size && h->data[rchild] > h->data[maxIndex]) {
    maxIndex = rchild;
  }

  if (index != maxIndex) {
    pq_swap(h->data + index, h->data + maxIndex);
    pq_shift_down(h, maxIndex);
  }
};

int pq_remove(MaxHeap *h, int index) {
  h->data[index] = h->data[1] + 1;
  pq_shift_up(h, index);
  return pq_execute_max(h);
}

void pq_change_priority(MaxHeap *h, int index, int priority) {
  int prevPriority = h->data[index];
  h->data[index] = priority;
  if (priority > prevPriority) {
    pq_shift_up(h, index);
  } else {
    pq_shift_down(h, index);
  }
}

// Test

void run_all_tests() {
  test_insert();
  test_execute_max();
  test_remove();
  test_change_priority();
  printf("OK\n");
}

void test_insert() {
  MaxHeap *h = pq_init();
  pq_insert(h, 11);
  pq_insert(h, 22);
  pq_insert(h, 33);
  pq_insert(h, 44);
  pq_insert(h, 55);
  // pq_print_data(h);
  assert(pq_get_size(h) == 5);
  assert(pq_get_max(h) == 55);
  pq_destroy(h);
}

void test_execute_max() {
  MaxHeap *h = pq_init();
  pq_insert(h, 11);
  pq_insert(h, 22);
  pq_insert(h, 33);
  pq_insert(h, 44);
  pq_insert(h, 55);
  // pq_print_data(h);
  assert(pq_execute_max(h) == 55);
  assert(pq_get_size(h) == 4);
  // pq_print_data(h);
  pq_destroy(h);
}

void test_remove() {
  MaxHeap *h = pq_init();
  pq_insert(h, 11);
  pq_insert(h, 22);
  pq_insert(h, 33);
  pq_insert(h, 44);
  pq_insert(h, 55);
  // pq_print_data(h);
  assert(pq_remove(h, 3) == 56);
  assert(pq_get_size(h) == 4);
  assert(pq_get_max(h) == 55);
  // pq_print_data(h);
  pq_destroy(h);
}

void test_change_priority() {
  MaxHeap *h = pq_init();
  pq_insert(h, 11);
  pq_insert(h, 22);
  pq_insert(h, 33);
  pq_insert(h, 44);
  pq_insert(h, 55);
  // pq_print_data(h);
  pq_change_priority(h, 3, 100);
  assert(pq_get_max(h) == 100);
  // pq_print_data(h);
  pq_destroy(h);
}