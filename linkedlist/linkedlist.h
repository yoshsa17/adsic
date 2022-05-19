#ifndef ADSIC_ARRAY_H
#define ADSIC_ARRAY_H

#include <assert.h>
#include <stdbool.h>

typedef struct Node Node;
struct Node{
  int num;
  Node *next;
};

// Singly-linked list
typedef struct {
  Node *head;
  Node *tail;
} SLinkedList;

SLinkedList *slinked_list_init();
void slinked_list_destroy(SLinkedList *list); 
void slinked_list_print(SLinkedList *list); 
int slinked_list_get_value(SLinkedList *list, int index);
int slinked_list_get_size(SLinkedList *list);
int slinked_list_front(SLinkedList *list);
int slinked_list_back(SLinkedList *list);
void slinked_list_push_front(SLinkedList *list, int val);
void slinked_list_pop_front(SLinkedList *list);
void slinked_list_push_back(SLinkedList *list, int val);
void slinked_list_pop_back(SLinkedList *list);
void slinked_list_insert(SLinkedList *list, int index, int val);
void slinked_list_erase(SLinkedList *list, int index);
void slinked_list_reverse(SLinkedList *list);
void slinked_list_remove(SLinkedList *list, int val);
void check_allocation(void *p);

//// test

void run_all_test();
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

#endif