#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "linkedlist.h"

SLinkedList *slinked_list_init() {
  SLinkedList *list = calloc(1, sizeof(SLinkedList));
  check_allocation(list);
  return list;
}

void slinked_list_destroy(SLinkedList *list) {
  Node *cur = list->head;
  Node *next;
  while(cur) {
    next = cur->next; 
    free(cur);
    cur = next;
  }
  free(list);
}

void slinked_list_print(SLinkedList *list) {
  Node *cur = list->head;
  printf("HEAD: %p\n", list->head);
  printf("TAIL: %p\n", list->tail);

  while(cur) {
    printf("(address): %p\n", cur);
    printf("num: %d\n", cur->num);
    printf("next node : %p\n", cur->next);
    printf("-----------------\n");
    cur = cur->next; 
  }
}

int slinked_list_get_value(SLinkedList *list, int index) {
  int i = 0;
  Node *cur = list->head;
  while(index >= i && cur) {
    if(index == i) {
      return cur->num;
    }
    ++i;
    cur = cur->next;
  }
  printf("Invalid index");
  exit(EXIT_FAILURE);
}

int slinked_list_get_size(SLinkedList *list) {
  int cnt = 0;
  Node *cur = list->head;
  while(cur){
    ++cnt;
    cur = cur->next;
  }
  return cnt;
}

int slinked_list_front(SLinkedList *list) {
  if(!list->head){
    printf("empty list");
    exit(EXIT_FAILURE);
  }
  return list->head->num;
}

int slinked_list_back(SLinkedList *list) {
  if(!list->tail){
    printf("empty list");
    exit(EXIT_FAILURE);
  }
  return list->tail->num;
}

void slinked_list_push_front(SLinkedList *list, int val) {
  Node *node = calloc(1, sizeof(Node));
  check_allocation(node);
  node->num = val;
  node->next = list->head;
  list->head = node;
  
  if(list->tail == NULL) {
    list->tail = list->head;
  }
}

void slinked_list_pop_front(SLinkedList *list) {
  if(list->head == NULL){
    exit(EXIT_FAILURE);
  }
  Node *tmp = list->head;
  list->head = list->head->next;
  if(list->head == NULL) {
    list->tail = NULL;
  }

  free(tmp);
}

void slinked_list_push_back(SLinkedList *list, int val) {
  Node *node = calloc(1, sizeof(Node));
  check_allocation(node);
  node->num = val;
  if(list->tail == NULL) {
    list->head = list->tail = node;
  } else {
    list->tail->next = node; 
    list->tail = node;
  }
}

void slinked_list_pop_back(SLinkedList *list) {
  if(list->head == NULL) {
    exit(EXIT_FAILURE);
  }

  Node *tmp = list->tail;
  if(list->head == list->tail) {
    list->head = list->tail = NULL;
  } else {
    Node *cur = list->head;
    while(cur->next != list->tail){
      cur = cur->next;
    }
    cur->next = NULL;
    list->tail = cur;
  }

  free(tmp);
}

void slinked_list_insert(SLinkedList *list, int index, int val) {

  Node *node = calloc(1, sizeof(Node));
  check_allocation(node);
  node->num = val;

  if(index == 0 && list->head == NULL) {
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

  while(cur){
    if(cnt == index) {
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

void slinked_list_erase(SLinkedList *list, int index) {
  if(index == 0 && list->head == NULL){
    printf("Unable to erase");
    exit(EXIT_FAILURE);
  } else if(index == 0) {
    Node *tmp = list->head;
    list->head = list->head->next;
    free(tmp);
    return;
  }

  Node *cur = list->head;
  Node *prev = NULL;
  int cnt = 0;

  while(cur){
    if(cnt == index) {
      prev->next = cur->next;
      if(cur == list->tail) {
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

void slinked_list_reverse(SLinkedList *list){

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

void slinked_list_remove(SLinkedList *list, int val) {
  Node *cur = list->head;
  Node *prev = NULL;

  while(cur) {
    if(cur->num == val) {
      if(list->head == list->tail) {
        list->head = list->tail = NULL;
      } else if(list->head == cur) {
        list->head = cur->next;
      } else if(list->tail == cur) {
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
  if(p == NULL) {
    fprintf(stderr, "Unable to allocate memory");
    exit(EXIT_FAILURE);
  }
}

////////////////// test /////////////////////

void run_all_test() {
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
  printf("OK!\n");
}

void test_init() {
  SLinkedList *list = slinked_list_init();
  assert(slinked_list_get_size(list) == 0);
  slinked_list_destroy(list);
}

void test_push_front() {
  SLinkedList *list = slinked_list_init();
  slinked_list_push_front(list, 10);
  slinked_list_push_front(list, 20);
  assert(slinked_list_get_size(list) == 2);
  slinked_list_destroy(list);
}

void test_pop_front() {
  SLinkedList *list = slinked_list_init();
  slinked_list_push_front(list, 10);
  slinked_list_push_front(list, 20);
  slinked_list_pop_front(list);
  assert(slinked_list_get_size(list) == 1);
  slinked_list_destroy(list);
}

void test_front() {
  SLinkedList *list = slinked_list_init();
  slinked_list_push_front(list, 10);
  slinked_list_push_front(list, 20);
  assert(slinked_list_front(list) == 20);
  slinked_list_destroy(list);
}

void test_back() {
  SLinkedList *list = slinked_list_init();
  slinked_list_push_front(list, 10);
  slinked_list_push_front(list, 20);
  assert(slinked_list_back(list) == 10);
  slinked_list_destroy(list);
}

void test_get_value() {
  SLinkedList *list = slinked_list_init();
  slinked_list_push_front(list, 10);
  slinked_list_push_front(list, 20);
  slinked_list_push_front(list, 30);
  assert(slinked_list_get_value(list, 0) ==  30);
  assert(slinked_list_get_value(list, 1) ==  20);
  assert(slinked_list_get_value(list, 2) ==  10);
  slinked_list_destroy(list);
}

void test_push_back() {
  SLinkedList *list = slinked_list_init();
  slinked_list_push_front(list, 10);
  slinked_list_push_front(list, 20);
  slinked_list_push_back(list, 30);
  assert(slinked_list_get_size(list) == 3);
  assert(slinked_list_back(list) == 30);
  slinked_list_destroy(list);
}

void test_pop_back() {
  SLinkedList *list = slinked_list_init();
  slinked_list_push_front(list, 10);
  slinked_list_push_front(list, 20);
  slinked_list_push_front(list, 30);
  slinked_list_pop_back(list);
  assert(slinked_list_get_size(list) == 2);
  assert(slinked_list_back(list) == 20);
  slinked_list_destroy(list);
}

void test_insert() {
  SLinkedList *list = slinked_list_init();
  slinked_list_push_front(list, 10);
  slinked_list_push_front(list, 20);
  slinked_list_push_front(list, 30);
  slinked_list_push_front(list, 40);
  slinked_list_insert(list, 2, 100);
  assert(slinked_list_get_size(list) == 5);
  assert(slinked_list_get_value(list, 2) == 100);
  slinked_list_insert(list, 0, 200);
  assert(slinked_list_front(list) == 200);
  assert(slinked_list_get_value(list, 0) == 200);
  slinked_list_destroy(list);
}

void test_erase() {
  SLinkedList *list = slinked_list_init();
  slinked_list_push_front(list, 10);
  slinked_list_push_front(list, 20);
  slinked_list_push_front(list, 30);
  slinked_list_push_front(list, 40);
  slinked_list_erase(list, 2);
  assert(slinked_list_get_size(list) == 3);
  assert(slinked_list_get_value(list, 0) == 40);
  assert(slinked_list_get_value(list, 1) == 30);
  assert(slinked_list_get_value(list, 2) == 10);
  slinked_list_destroy(list);
}

void test_reverse() {
  SLinkedList *list = slinked_list_init();
  slinked_list_push_front(list, 10);
  slinked_list_push_front(list, 20);
  slinked_list_push_front(list, 30);
  slinked_list_push_front(list, 40);
  slinked_list_reverse(list);
  assert(slinked_list_get_value(list, 0) == 10);
  assert(slinked_list_get_value(list, 1) == 20);
  assert(slinked_list_get_value(list, 2) == 30);
  assert(slinked_list_get_value(list, 3) == 40);
  slinked_list_destroy(list);
}

void test_remove() {
  SLinkedList *list = slinked_list_init();
  slinked_list_push_front(list, 10);
  slinked_list_push_front(list, 20);
  slinked_list_push_front(list, 30);
  slinked_list_push_front(list, 40);
  slinked_list_remove(list, 30);
  assert(slinked_list_get_size(list) == 3);
  assert(slinked_list_get_value(list, 0) == 40);
  assert(slinked_list_get_value(list, 1) == 20);
  assert(slinked_list_get_value(list, 2) == 10);
  slinked_list_destroy(list);
}
