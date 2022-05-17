#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "array.h"

DArray *darray_init(int initialCapacity) {
  // allocate a dynamicArray's size memory
  DArray *a = calloc(1, sizeof(DArray));
  check_memory_allocation(a);
  a->data = calloc(initialCapacity, sizeof(int));
  check_memory_allocation(a->data);
  a->used = 0;
  a->capacity = initialCapacity;
  return a;
}

void darray_destroy(DArray *a) {
  free(a->data);
  free(a);
}

void darray_print(DArray *a) {
  printf("------\n");
  printf("Used: %d\n", a->used);
  printf("Capacity: %d\n", a->capacity);
  printf("Items: \n");

  for (int i = 0; i < a->capacity; i++){
    printf("%d: %d\n",  i, a->data[i]);
  }

  printf("------\n");
}

int darray_get_size(DArray *a) { return a->used; }

int darray_get_capacity(DArray *a) { return a->capacity; }

bool darray_get_is_empty(DArray *a) { 
  if(a->used == 0) {
    return true;
  }
  return false;
}

void darray_resize(DArray *a, int newCapacity) {
  int *new_data = realloc(a->data, a->capacity * sizeof(int));
  check_memory_allocation(new_data);
  if(new_data == NULL) {
    exit(EXIT_FAILURE);
  } else {
    a->data = new_data;
    a->capacity = newCapacity;
  }
}

int darray_get_item(DArray *a, int index) {
  if(index < 0 || index > a->used - 1) {
    exit(EXIT_FAILURE);
  }
  
  return a->data[index];
}

void darray_push(DArray *a, int item) {
  if(a->capacity == a->used){
    darray_resize(a, a->capacity * 2);
  }
  a->data[a->used] = item;
  a->used++;
}

int darray_pop(DArray* a) {
  if(a->used == 0){
    exit(EXIT_FAILURE);
  }

  if(a->capacity/4 == a->used){
    darray_resize(a, a->capacity / 2);
  }
  
  int tmp = a->data[a->used - 1];
  a->data[a->used - 1] = 0;
  a->used--;
  return tmp;
}

void darray_insert(DArray *a, int index, int item) {
  if(index < 0 || index > a->used - 1) {
    exit(EXIT_FAILURE);
  }

  if(a->capacity == a->used){
    darray_resize(a, a->capacity * 2);
  }
  
  memmove(a->data + index + 1, a->data + index, (a->used - index) * sizeof(int));
  a->data[index] = item;
  a->used++;
}

void darray_delete(DArray *a, int index) {
  if(index < 0 || index > a->used - 1) {
    exit(EXIT_FAILURE);
  }

  if(a->capacity/4 == a->used){
    darray_resize(a, a->capacity / 2);
  }

  memmove(a->data + index, a->data + index + 1, (a->used - index) * sizeof(int));
  a->used--;
}

void darray_prepend(DArray *a, int item) {
  darray_insert(a, 0, item);
}

int darray_find(DArray *a, int item) {
  int found_index = -1;

  for (int i = 0; i < a->used; ++i) {
    if(a->data[i] == item) {
      found_index = i;
      break;
    }
  }
  return found_index;
}

void darray_remove(DArray *a, int item) {
  int index_of_item = darray_find(a, item);
  if(index_of_item == -1) {
    exit(EXIT_FAILURE);
  }

  darray_delete(a, index_of_item);
}

void check_memory_allocation(void *p) {
  if(p == NULL) {
    fprintf(stderr, "Unable to allocate memory");
    exit(EXIT_FAILURE);
  }
}

//////////////// test ////////////////  

int initial_capacity = 5;

void run_all_test() {
  test_darray_init();
  test_darray_push();
  test_darray_get_item();
  test_darray_pop();
  test_darray_resize();
  test_darray_insert();
  test_darray_delete();
  test_darray_prepend();
  test_darray_find(); 
  test_darray_remove();
  printf("OK!\n");
}

void test_darray_init() {
  DArray *a = darray_init(initial_capacity);
  assert(darray_get_size(a) == 0);
  assert(darray_get_capacity(a) == initial_capacity);
  darray_destroy(a);
}

void test_darray_push() {
  DArray *a = darray_init(5);
  darray_push(a, 100);
  assert(darray_get_size(a) == 1);
  darray_destroy(a);
}

void test_darray_get_item() {
  DArray *a = darray_init(initial_capacity);
  darray_push(a, 100);
  assert(darray_get_item(a, 0) == 100);
  darray_destroy(a);
}

void test_darray_pop() {
  DArray *a = darray_init(initial_capacity);
  darray_push(a, 33);
  int item = darray_pop(a);
  assert(darray_get_size(a) == 0);
  assert(item == 33);
  darray_destroy(a);
}

void test_darray_resize() {
  DArray *a = darray_init(initial_capacity);
  int prev_capacity = darray_get_capacity(a);
  for(int i = 0; i < initial_capacity + 1; ++i) {
    darray_push(a, i);
  }
  assert(darray_get_size(a) == initial_capacity + 1);
  assert(darray_get_capacity(a) == prev_capacity * 2);
  for(;;) {
    darray_pop(a);
    if(darray_get_size(a) == darray_get_capacity(a) / 4) {
      darray_pop(a);
      break;
    }
  }

  assert(darray_get_capacity(a) == prev_capacity * 2 / 2);
  darray_destroy(a);
}

void test_darray_insert() {
  DArray *a = darray_init(initial_capacity);
  for(int i = 0; i < initial_capacity; ++i) {
    darray_push(a, i);
  }
  darray_insert(a, 2, 100);
  assert(darray_get_item(a, 2) == 100);
  darray_destroy(a);
}

void test_darray_delete() {
  DArray *a = darray_init(initial_capacity);
  for(int i = 0; i < initial_capacity; ++i) {
    darray_push(a, i);
  }
  int prev_size = darray_get_size(a);
  darray_delete(a, 2);
  assert(darray_get_size(a) == prev_size - 1 );
  darray_destroy(a);
}

void test_darray_prepend() {
  DArray *a = darray_init(initial_capacity);
  for(int i = 0; i < initial_capacity; ++i) {
    darray_push(a, i);
  }
  darray_prepend(a, 100);
  assert(darray_get_item(a, 0) == 100);
  darray_destroy(a);
}

void test_darray_find() {
  DArray *a = darray_init(initial_capacity);
  for(int i = 0; i < initial_capacity; ++i) {
    darray_push(a, i);
  }
  assert(darray_find(a, 4) == 4);
  darray_destroy(a);
}

void test_darray_remove() {
  DArray *a = darray_init(initial_capacity);
  for(int i = 0; i < initial_capacity; ++i) {
    darray_push(a, i);
  }
  darray_remove(a, 3);
  assert(darray_get_size(a) == initial_capacity - 1);
  assert(darray_find(a, 3) == -1);
  darray_destroy(a);
}