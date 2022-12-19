#include <stdio.h>
#include <stdlib.h>
#include <bmp.h>

int main(void) {
  FILE* file = fopen("./images/test.bmp", "r+b");
  if (file == NULL) {
    puts("Could not open file :( ");
    return -1;
  }

  struct BmpRelMetadata b;
  
  load_bmp(&b, file);
  
  rotate_bmp(&b, file);

  fclose(file);
  return 0;
}
