#include <stdio.h>
#include <stdlib.h>

int* array_read(size_t* out_count){
  int* array;
  size_t cnt;
  scanf("%zu", &cnt);
  array = malloc(cnt * sizeof(int));

  for (int i = 0; i < cnt; i++) {
    scanf("%d", &array[i]);
  }
  *out_count = cnt;
  return array;
}

void array_print(int const* array, int cnt) {
  for(int i = 0; i < cnt; i++) {
    printf("%d ", array[i]);
  }
  puts(" ");
}

int array_sum(int const* array, int cnt){
  int sum = 0;
  for(int i = 0; i < cnt; i++) {
    sum += array[i];
  }
  return sum;
}

int main(void) {
  int* array;
  size_t count;

  array = array_read(&count);

  array_print(array, count);

  printf("Sum of array: %d\n", array_sum(array,count));
  
  free(array);
  return 0;
}
