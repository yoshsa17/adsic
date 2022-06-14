#include <assert.h>
#include <stdio.h>

int binary_search(int key, int array[], int size);
int binary_search_recursive(int key, int *array, int min, int max);

void run_all_tests();
void test_binary_search();
void test_binary_search_recursive();

// Main

int main(int argc, char **argv) {
  run_all_tests();
  return 0;
}

// Functions

int binary_search(int key, int *array, int size) {
  int low = 0;
  int mid = 0;
  int high = size - 1;

  while (low <= high) {
    mid = low + (high - low) / 2;
    if (array[mid] < key) {
      low = mid + 1;
    } else if (key < array[mid]) {
      high = mid - 1;
    } else {
      return mid;
    }
  }

  return -1;
}

int binary_search_recursive(int key, int array[], int min, int max) {
  if (max < min) {
    return -1;
  }

  int midpoint = min + (max - min) / 2;

  if (array[midpoint] < key) {
    return binary_search_recursive(key, array, midpoint + 1, max);
  } else if (key < array[midpoint]) {
    return binary_search_recursive(key, array, min, midpoint - 1);
  } else {
    return midpoint;
  }
}

////// Test

void run_all_tests() {
  test_binary_search_recursive();
  test_binary_search();
  printf("OK\n");
}

void test_binary_search() {
  const int size = 10;
  int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  assert(binary_search(2, array, size) == 1);
  assert(binary_search(3, array, size) == 2);
  assert(binary_search(9, array, size) == 8);
  assert(binary_search(12, array, size) == -1);
}

void test_binary_search_recursive() {
  const int size = 10;
  int max = size - 1;
  int array[] = {23, 34, 55, 99, 244, 435, 8534, 8888, 13232, 19939};
  assert(binary_search_recursive(99, array, 0, max) == 3);
  assert(binary_search_recursive(244, array, 0, max) == 4);
  assert(binary_search_recursive(8888, array, 0, max) == 7);
  assert(binary_search_recursive(100, array, 0, max) == -1);
}