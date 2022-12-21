#include <mem.h>
#include <unistd.h>

int main(void) {
  void* HEAP_START = sbrk(0);

  if (heap_init(20, HEAP_START) == NULL) {
    printf("Heap init failed \n");
    return 1;
  }

  char* test_str = _malloc(11);
  for(int i = 0; i < 10; i++) {
    test_str[i] = 'a';
  }
  test_str[10] = '\0';

  char* test_str_2 = _malloc(11);
  for(int i = 0; i < 10; i++) {
    test_str_2[i] = 'b';
  }
  test_str_2[10] = '\0';

  char* test_str_3 = _malloc(11);
  for(int i = 0; i < 10; i++) {
    test_str_3[i] = 'c';
  }
  test_str_3[10] = '\0';


  printf("TEST STR 1 %s \n", test_str);
  printf("TEST STR 2 %s \n", test_str_2);
  printf("TEST STR 3 %s \n", test_str_3);

  _free(test_str);
  _free(test_str_2);
  _free(test_str_3);

  return 0;
}
