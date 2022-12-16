#include <stdio.h>
#include "mylib.h"

int main() {
  int arr[] = {9, 6, 6, 3, 4, 2}; // size is 6
  
  puts("Before Sorting");
  for (int i = 0; i < 6; i++) {
    printf("%d ,", arr[i]);
  }
  puts("\n");

  bubblesort(arr, 6);

  puts("After Sorting");

  for (int i = 0; i < 6; i++) {
    printf("%d ,", arr[i]);
  }
  puts("\n");

  puts("Accumulating array sum");
  int sum = sumarr(arr, 2);
  printf("Sum of Arr %d\n", sum);
  
  printf("Swap two elements cutely!\n");
  
  swaptwo(arr, 2, 4);

  for (int i = 0; i < 6; i++) {
    printf("%d ,", arr[i]);
  }
  puts("\n");
}