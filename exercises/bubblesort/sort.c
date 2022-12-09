#include <stdio.h>
#include "mylib.h"

int main() {
  int arr[] = {6, 9, 12, 45, 65, 23, 0, -5, 23, 1, 7}; // size is 5
  puts("Before Sorting");
  for (int i = 0; i < 11; i++) {
    printf("%d ,", arr[i]);
  }
  puts("\n");

  bubblesort(arr, 11);

  puts("After Sorting");

  for (int i = 0; i < 11; i++) {
    printf("%d ,", arr[i]);
  }

  puts("\n");

  puts("Accumulating array sum");

  int sum = sumarr(arr, 11);
  
  printf("Sum of Arr %d", sum);

  puts("\n");
}