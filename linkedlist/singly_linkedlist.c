#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

typedef struct Node Node;
struct Node {
  int num;
  Node *next;
};

// Singly-linked list implementation
typedef struct {
  Node *head;
  Node *tail;
} SLinkedList;

SLinkedList *sl_init();
void sl_destroy(SLinkedList *list);
void sl_print(SLinkedList *list);
int sl_get_value(SLinkedList *list, int index);
int sl_get_size(SLinkedList *list);
int sl_front(SLinkedList *list);
int sl_back(SLinkedList *list);
void sl_push_front(SLinkedList *list, int val);
void sl_pop_front(SLinkedList *list);
void sl_push_back(SLinkedList *list, int val);
void sl_pop_back(SLinkedList *list);
void sl_insert(SLinkedList *list, int index, int val);
void sl_erase(SLinkedList *list, int index);
void sl_reverse(SLinkedList *list);
void sl_remove(SLinkedList *list, int val);
void check_allocation(void *p);

void run_all_tests();
void test_init();
void test_push_front();
void test_pop_front();
void test_front();
void test_back();
void test_get_value();
void test_push_back();
void test_pop_back();
void test_insert();
void test_erase();
void test_reverse();
void test_remove();

// Main

int main(int argc, char **argv) {
  run_all_tests();
  return 0;
}

// Functions

SLinkedList *sl_init() {
  SLinkedList *list = calloc(1, sizeof(SLinkedList));
  check_allocation(list);
  return list;
}

void sl_destroy(SLinkedList *list) {
  Node *cur = list->head;
  Node *next;
  while (cur) {
    next = cur->next;
    free(cur);
    cur = next;
  }
  free(list);
}

void sl_print(SLinkedList *list) {
  Node *cur = list->head;
  printf("HEAD: %p\n", list->head);
  printf("TAIL: %p\n", list->tail);

  while (cur) {
    printf("(address): %p\n", cur);
    printf("num: %d\n", cur->num);
    printf("next node : %p\n", cur->next);
    printf("-----------------\n");
    cur = cur->next;
  }
}

int sl_get_value(SLinkedList *list, int index) {
  int i = 0;
  Node *cur = list->head;
  while (index >= i && cur) {
    if (index == i) {
      return cur->num;
    }
    ++i;
    cur = cur->next;
  }
  printf("Invalid index");
  exit(EXIT_FAILURE);
}

int sl_get_size(SLinkedList *list) {
  int cnt = 0;
  Node *cur = list->head;
  while (cur) {
    ++cnt;
    cur = cur->next;
  }
  return cnt;
}

int sl_front(SLinkedList *list) {
  if (!list->head) {
    printf("empty list");
    exit(EXIT_FAILURE);
  }
  return list->head->num;
}

int sl_back(SLinkedList *list) {
  if (!list->tail) {
    printf("empty list");
    exit(EXIT_FAILURE);
  }
  return list->tail->num;
}

void sl_push_front(SLinkedList *list, int val) {
  Node *node = calloc(1, sizeof(Node));
  check_allocation(node);
  node->num = val;
  node->next = list->head;
  list->head = node;

  if (list->tail == NULL) {
    list->tail = list->head;
  }
}

void sl_pop_front(SLinkedList *list) {
  if (list->head == NULL) {
    exit(EXIT_FAILURE);
  }
  Node *tmp = list->head;
  list->head = list->head->next;
  if (list->head == NULL) {
    list->tail = NULL;
  }

  free(tmp);
}

void sl_push_back(SLinkedList *list, int val) {
  Node *node = calloc(1, sizeof(Node));
  check_allocation(node);
  node->num = val;
  if (list->tail == NULL) {
    list->head = list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
}

void sl_pop_back(SLinkedList *list) {
  if (list->head == NULL) {
    exit(EXIT_FAILURE);
  }

  Node *tmp = list->tail;
  if (list->head == list->tail) {
    list->head = list->tail = NULL;
  } else {
    Node *cur = list->head;
    while (cur->next != list->tail) {
      cur = cur->next;
    }
    cur->next = NULL;
    list->tail = cur;
  }

  free(tmp);
}

void sl_insert(SLinkedList *list, int index, int val) {
  Node *node = calloc(1, sizeof(Node));
  check_allocation(node);
  node->num = val;

  if (index == 0 && list->head == NULL) {
    list->head = list->tail = node;
    return;
  } else if (index == 0) {
    node->next = list->head;
    list->head = node;
    return;
  }

  Node *cur = list->head;
  Node *prev = NULL;
  int cnt = 0;

  while (cur) {
    if (cnt == index) {
      node->next = cur;
      prev->next = node;
      return;
    }
    ++cnt;
    prev = cur;
    cur = cur->next;
  }
  printf("Unable to insert");
  exit(EXIT_FAILURE);
}

void sl_erase(SLinkedList *list, int index) {
  if (index == 0 && list->head == NULL) {
    printf("Unable to erase");
    exit(EXIT_FAILURE);
  } else if (index == 0) {
    Node *tmp = list->head;
    list->head = list->head->next;
    free(tmp);
    return;
  }

  Node *cur = list->head;
  Node *prev = NULL;
  int cnt = 0;

  while (cur) {
    if (cnt == index) {
      prev->next = cur->next;
      if (cur == list->tail) {
        list->tail = prev;
      }
      free(cur);
      return;
    }
    ++cnt;
    prev = cur;
    cur = cur->next;
  }
  printf("Unable to erase");
  exit(EXIT_FAILURE);
}

void sl_reverse(SLinkedList *list) {
  Node *prev = NULL;
  Node *cur = list->head;
  Node *next;

  while (cur) {
    next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }

  list->tail = list->head;
  list->head = prev;
}

void sl_remove(SLinkedList *list, int val) {
  Node *cur = list->head;
  Node *prev = NULL;

  while (cur) {
    if (cur->num == val) {
      if (list->head == list->tail) {
        list->head = list->tail = NULL;
      } else if (list->head == cur) {
        list->head = cur->next;
      } else if (list->tail == cur) {
        list->tail = prev;
      } else {
        prev->next = cur->next;
      }

      free(cur);
      return;
    }
    prev = cur;
    cur = cur->next;
  }
  printf("Unable to remove");
  exit(EXIT_FAILURE);
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
  test_push_front();
  test_pop_front();
  test_front();
  test_back();
  test_get_value();
  test_push_back();
  test_pop_back();
  test_insert();
  test_erase();
  test_reverse();
  test_remove();
  printf("OK\n");
}

void test_init() {
  SLinkedList *list = sl_init();
  assert(sl_get_size(list) == 0);
  sl_destroy(list);
}

void test_push_front() {
  SLinkedList *list = sl_init();
  sl_push_front(list, 10);
  sl_push_front(list, 20);
  assert(sl_get_size(list) == 2);
  sl_destroy(list);
}

void test_pop_front() {
  SLinkedList *list = sl_init();
  sl_push_front(list, 10);
  sl_push_front(list, 20);
  sl_pop_front(list);
  assert(sl_get_size(list) == 1);
  sl_destroy(list);
}

void test_front() {
  SLinkedList *list = sl_init();
  sl_push_front(list, 10);
  sl_push_front(list, 20);
  assert(sl_front(list) == 20);
  sl_destroy(list);
}

void test_back() {
  SLinkedList *list = sl_init();
  sl_push_front(list, 10);
  sl_push_front(list, 20);
  assert(sl_back(list) == 10);
  sl_destroy(list);
}

void test_get_value() {
  SLinkedList *list = sl_init();
  sl_push_front(list, 10);
  sl_push_front(list, 20);
  sl_push_front(list, 30);
  assert(sl_get_value(list, 0) == 30);
  assert(sl_get_value(list, 1) == 20);
  assert(sl_get_value(list, 2) == 10);
  sl_destroy(list);
}

void test_push_back() {
  SLinkedList *list = sl_init();
  sl_push_front(list, 10);
  sl_push_front(list, 20);
  sl_push_back(list, 30);
  assert(sl_get_size(list) == 3);
  assert(sl_back(list) == 30);
  sl_destroy(list);
}

void test_pop_back() {
  SLinkedList *list = sl_init();
  sl_push_front(list, 10);
  sl_push_front(list, 20);
  sl_push_front(list, 30);
  sl_pop_back(list);
  assert(sl_get_size(list) == 2);
  assert(sl_back(list) == 20);
  sl_destroy(list);
}

void test_insert() {
  SLinkedList *list = sl_init();
  sl_push_front(list, 10);
  sl_push_front(list, 20);
  sl_push_front(list, 30);
  sl_push_front(list, 40);
  sl_insert(list, 2, 100);
  assert(sl_get_size(list) == 5);
  assert(sl_get_value(list, 2) == 100);
  sl_insert(list, 0, 200);
  assert(sl_front(list) == 200);
  assert(sl_get_value(list, 0) == 200);
  sl_destroy(list);
}

void test_erase() {
  SLinkedList *list = sl_init();
  sl_push_front(list, 10);
  sl_push_front(list, 20);
  sl_push_front(list, 30);
  sl_push_front(list, 40);
  sl_erase(list, 2);
  assert(sl_get_size(list) == 3);
  assert(sl_get_value(list, 0) == 40);
  assert(sl_get_value(list, 1) == 30);
  assert(sl_get_value(list, 2) == 10);
  sl_destroy(list);
}

void test_reverse() {
  SLinkedList *list = sl_init();
  sl_push_front(list, 10);
  sl_push_front(list, 20);
  sl_push_front(list, 30);
  sl_push_front(list, 40);
  sl_reverse(list);
  assert(sl_get_value(list, 0) == 10);
  assert(sl_get_value(list, 1) == 20);
  assert(sl_get_value(list, 2) == 30);
  assert(sl_get_value(list, 3) == 40);
  sl_destroy(list);
}

void test_remove() {
  SLinkedList *list = sl_init();
  sl_push_front(list, 10);
  sl_push_front(list, 20);
  sl_push_front(list, 30);
  sl_push_front(list, 40);
  sl_remove(list, 30);
  assert(sl_get_size(list) == 3);
  assert(sl_get_value(list, 0) == 40);
  assert(sl_get_value(list, 1) == 20);
  assert(sl_get_value(list, 2) == 10);
  sl_destroy(list);
}
