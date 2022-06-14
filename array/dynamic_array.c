#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dynamic array implementation
typedef struct {
  int *data;
  int used;
  int capacity;
} DArray;

void da_init(DArray *a, int initialCapacity);
void da_destroy(DArray *a);
void da_print(DArray *a);
int da_get_size(DArray *a);
int da_get_capacity(DArray *a);
bool da_get_is_empty(DArray *a);
void da_resize(DArray *a, int newCapacity);
int da_get_item(DArray *a, int index);
void da_push(DArray *a, int item);
int da_pop(DArray *a);
void da_insert(DArray *a, int index, int item);
void da_delete(DArray *a, int index);
void da_prepend(DArray *a, int item);
int da_find(DArray *a, int item);
void da_remove(DArray *a, int item);
void check_memory_allocation(void *p);

void run_all_tests();
void test_init();
void test_push();
void test_get_item();
void test_pop();
void test_resize();
void test_insert();
void test_delete();
void test_prepend();
void test_find();
void test_remove();

// Main

int main(int argc, char **argv) {
  run_all_tests();
  return 0;
}

// Functions

void da_init(DArray *a, int initialCapacity) {
  a->data = malloc(initialCapacity * sizeof(int));
  check_memory_allocation(a->data);
  a->used = 0;
  a->capacity = initialCapacity;
}

void da_destroy(DArray *a) {
  free(a->data);
  a->data = NULL;
  a->used = a->capacity = 0;
}

void da_print(DArray *a) {
  printf("------\n");
  printf("Used: %d\n", a->used);
  printf("Capacity: %d\n", a->capacity);
  printf("Items: \n");

  for (int i = 0; i < a->capacity; i++) {
    printf("%d: %d\n", i, a->data[i]);
  }

  printf("------\n");
}

int da_get_size(DArray *a) { return a->used; }

int da_get_capacity(DArray *a) { return a->capacity; }

bool da_get_is_empty(DArray *a) {
  if (a->used == 0) {
    return true;
  }
  return false;
}

void da_resize(DArray *a, int newCapacity) {
  int *new_data = realloc(a->data, a->capacity * sizeof(int));
  check_memory_allocation(new_data);
  if (new_data == NULL) {
    exit(EXIT_FAILURE);
  } else {
    a->data = new_data;
    a->capacity = newCapacity;
  }
}

int da_get_item(DArray *a, int index) {
  if (index < 0 || index > a->used - 1) {
    exit(EXIT_FAILURE);
  }

  return a->data[index];
}

void da_push(DArray *a, int item) {
  if (a->capacity == a->used) {
    da_resize(a, a->capacity * 2);
  }
  a->data[a->used] = item;
  a->used++;
}

int da_pop(DArray *a) {
  if (a->used == 0) {
    exit(EXIT_FAILURE);
  }

  if (a->capacity / 4 == a->used) {
    da_resize(a, a->capacity / 2);
  }

  int tmp = a->data[a->used - 1];
  a->data[a->used - 1] = 0;
  a->used--;
  return tmp;
}

void da_insert(DArray *a, int index, int item) {
  if (index < 0 || index > a->used - 1) {
    exit(EXIT_FAILURE);
  }

  if (a->capacity == a->used) {
    da_resize(a, a->capacity * 2);
  }

  memmove(a->data + index + 1, a->data + index,
          (a->used - index) * sizeof(int));
  a->data[index] = item;
  a->used++;
}

void da_delete(DArray *a, int index) {
  if (index < 0 || index > a->used - 1) {
    exit(EXIT_FAILURE);
  }

  if (a->capacity / 4 == a->used) {
    da_resize(a, a->capacity / 2);
  }

  memmove(a->data + index, a->data + index + 1,
          (a->used - index) * sizeof(int));
  a->used--;
}

void da_prepend(DArray *a, int item) { da_insert(a, 0, item); }

int da_find(DArray *a, int item) {
  int found_index = -1;

  for (int i = 0; i < a->used; ++i) {
    if (a->data[i] == item) {
      found_index = i;
      break;
    }
  }
  return found_index;
}

void da_remove(DArray *a, int item) {
  int index_of_item = da_find(a, item);
  if (index_of_item == -1) {
    exit(EXIT_FAILURE);
  }

  da_delete(a, index_of_item);
}

void check_memory_allocation(void *p) {
  if (p == NULL) {
    fprintf(stderr, "Unable to allocate memory");
    exit(EXIT_FAILURE);
  }
}

// Tests

void run_all_tests() {
  test_init();
  test_push();
  test_get_item();
  test_pop();
  test_resize();
  test_insert();
  test_delete();
  test_prepend();
  test_find();
  test_remove();
  printf("OK\n");
}

int initial_capacity = 5;

void test_init() {
  DArray a;
  da_init(&a, initial_capacity);
  assert(da_get_size(&a) == 0);
  assert(da_get_capacity(&a) == initial_capacity);
  da_destroy(&a);
}

void test_push() {
  DArray a;
  da_init(&a, initial_capacity);
  da_push(&a, 100);
  assert(da_get_size(&a) == 1);
  da_destroy(&a);
}

void test_get_item() {
  DArray a;
  da_init(&a, initial_capacity);
  da_push(&a, 100);
  assert(da_get_item(&a, 0) == 100);
  da_destroy(&a);
}

void test_pop() {
  DArray a;
  da_init(&a, initial_capacity);
  da_push(&a, 33);
  assert(da_pop(&a) == 33);
  assert(da_get_size(&a) == 0);
  da_destroy(&a);
}

void test_resize() {
  DArray a;
  da_init(&a, initial_capacity);
  int prev_capacity = da_get_capacity(&a);
  for (int i = 0; i < initial_capacity + 1; ++i) {
    da_push(&a, i);
  }
  assert(da_get_size(&a) == initial_capacity + 1);
  assert(da_get_capacity(&a) == prev_capacity * 2);
  for (;;) {
    if (da_get_size(&a) == da_get_capacity(&a) / 4) {
      da_pop(&a);
      break;
    }
    da_pop(&a);
  }

  assert(da_get_capacity(&a) == prev_capacity * 2 / 2);
  da_destroy(&a);
}

void test_insert() {
  DArray a;
  da_init(&a, initial_capacity);
  for (int i = 0; i < initial_capacity; ++i) {
    da_push(&a, i);
  }
  da_insert(&a, 2, 100);
  assert(da_get_item(&a, 2) == 100);
  da_destroy(&a);
}

void test_delete() {
  DArray a;
  da_init(&a, initial_capacity);
  for (int i = 0; i < initial_capacity; ++i) {
    da_push(&a, i);
  }
  int prev_size = da_get_size(&a);
  da_delete(&a, 2);
  assert(da_get_size(&a) == prev_size - 1);
  da_destroy(&a);
}

void test_prepend() {
  DArray a;
  da_init(&a, initial_capacity);
  for (int i = 0; i < initial_capacity; ++i) {
    da_push(&a, i);
  }
  da_prepend(&a, 100);
  assert(da_get_item(&a, 0) == 100);
  da_destroy(&a);
}

void test_find() {
  DArray a;
  da_init(&a, initial_capacity);
  for (int i = 0; i < initial_capacity; ++i) {
    da_push(&a, i);
  }
  assert(da_find(&a, 4) == 4);
  da_destroy(&a);
}

void test_remove() {
  DArray a;
  da_init(&a, initial_capacity);
  for (int i = 0; i < initial_capacity; ++i) {
    da_push(&a, i);
  }
  da_remove(&a, 3);
  assert(da_get_size(&a) == initial_capacity - 1);
  assert(da_find(&a, 3) == -1);
  da_destroy(&a);
}