#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

// ref: shuffle/fisher_yates_shuffle.c
void fisher_yates_shuffle(int arr[], int size) {
  srand(time(NULL));
  for (int i = size - 1; i > 0; --i) {
    int target = rand() % (i + 1);
    swap(&arr[i], &arr[target]);
  }
}

int partition(int arr[], int lo, int hi) {
  //      0                     7
  //      3 | 5, 7, 4, 1, 8, 6, 2 |
  //     p,i                        j
  //      lo                    hi

  int i = lo;
  int j = hi + 1;

  while (1) {
    // find greater item than pivot
    while (arr[++i] < arr[lo]) {
      if (hi < i) break;
    }
    // find lesser item than pivot
    while (arr[lo] < arr[--j]) {
      if (j < lo) break;
    }

    // if i and j is crossed, keep their order
    if (i >= j) break;
    swap(&arr[i], &arr[j]);
  }

  // swap j and pivot
  swap(&arr[lo], &arr[j]);
  return j;
}

void quick_sort_recursion(int arr[], int lo, int hi) {
  if (hi <= lo) return;
  int j = partition(arr, lo, hi);
  quick_sort_recursion(arr, lo, j - 1);
  quick_sort_recursion(arr, j + 1, hi);
}

void quick_sort(int arr[], int length) {
  fisher_yates_shuffle(arr, length);
  // for (int i = 0; i < length; i++) printf("%d, \n", arr[i]);
  quick_sort_recursion(arr, 0, length - 1);
}

// Main

int main() {
  int array[] = {99, 58, 334, 535, 1234, 41, 3, 534, 2, 74};
  int length = sizeof(array) / sizeof(int);
  quick_sort(array, length);

  printf("Result:\n");
  for (int n = 0; n < length; ++n) printf("%d ", array[n]);
  printf("\n");

  return 0;
}