#include <stdio.h>
#include <string.h>

// In-place merge sort implementation

void merge(int arr[], int lo, int mid, int hi) {
  // arr     { 2 | 3 | 6 | 8 }{ 1 | 4 | 5 | 7 }
  //           k
  //
  // temp    { 2 | 3 | 6 | 8 }{ 1 | 4 | 5 | 7 }
  //          lo          mid               hi
  //          i                j

  int temp[hi + 1];
  int i = lo;
  int j = mid + 1;
  int k;

  // copy array (copy items b/w lo to hi)
  for (int k = lo; k <= hi; ++k) temp[k] = arr[k];

  for (k = lo; k <= hi; ++k) {
    // copy remaining items from right sub-array in temp
    if (i > mid) arr[k] = temp[j++];
    // copy remaining items from left sub-array in temp
    else if (j > hi)
      arr[k] = temp[i++];
    // compare items and copy smaller one to arr
    else if (temp[i] > temp[j])
      arr[k] = temp[j++];
    // if two items are equal, copy item from left sub-array first (stable sort)
    else
      arr[k] = temp[i++];
  }
}

void merge_sort_recursion(int arr[], int lo, int hi) {
  printf("Low:%d High:%d\n", lo, hi);
  if (lo >= hi) return;

  int mid = lo + (hi - lo) / 2;

  merge_sort_recursion(arr, lo, mid);
  merge_sort_recursion(arr, mid + 1, hi);
  merge(arr, lo, mid, hi);
}

void merge_sort(int arr[], int length) {
  merge_sort_recursion(arr, 0, length - 1);
}

// Main

int main() {
  int array[] = {94, 195, 276, 162, 198, 107, 261, 426};
  int length = sizeof(array) / sizeof(int);
  merge_sort(array, length);

  printf("Result:\n");
  for (int i = 0; i < length; ++i) printf("%d ", array[i]);
  printf("\n");

  return 0;
}