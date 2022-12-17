#include <stdio.h>
#include <stdlib.h>
#include <bmp.h>

int main(void) {
  FILE* file = fopen("./images/blackbuck.bmp", "rb");
  if (file == NULL) {
    puts("Could not open file :( ");
    return -1;
  }

  struct BmpRelMetadata b;
  struct Pixel p;
  
  load_bmp(&b, &p, file);

  fclose(file);
  return 0;
}
