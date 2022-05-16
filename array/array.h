#ifndef ADSIC_ARRAY_H
#define ADSIC_ARRAY_H

#include <assert.h>
#include <stdbool.h>

// Dynamic Array
typedef struct {
  int *data;
  int used;
  int capacity;
} DArray;

DArray *darray_init(int initialCapacity); 
void darray_destroy(DArray *a);
void darray_print(DArray *a);
int darray_get_size(DArray *a);
int darray_get_capacity(DArray *a); 
bool darray_get_is_empty(DArray *a); 
void darray_resize(DArray *a, int newCapacity); 
int darray_get_item(DArray *a, int index);
void darray_push(DArray *a, int item); 
int darray_pop(DArray* a);
void darray_insert(DArray *a, int index, int item); 
void darray_delete(DArray *a, int index); 
void darray_prepend(DArray *a, int item);
int darray_find(DArray *a, int item); 
void darray_remove(DArray *a, int item); 

//////// test ////////
void run_all_test();
void test_darray_init();
void test_darray_push();
void test_darray_get_item();
void test_darray_pop();
void test_darray_resize();
void test_darray_insert();
void test_darray_delete();
void test_darray_prepend();
void test_darray_find();
void test_darray_remove();

#endif