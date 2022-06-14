#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void fisher_yates_shuffle(int arr[], int size) {
  // index:    0                                    9
  // arr[]:  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
  //                   t                        <-- i

  srand(time(NULL));  // init with time (unix time)
  for (int i = size - 1; i > 0; --i) {
    int target = rand() % (i + 1);  // get a random index
    swap(&arr[i], &arr[target]);    // swap i and target items
  }
}

// Main

int main() {
  int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int len = sizeof(array) / sizeof(int);
  fisher_yates_shuffle(array, len);

  for (int i = 0; i < len; ++i) printf("%d ", array[i]);
  printf("\n");
  return 0;
}