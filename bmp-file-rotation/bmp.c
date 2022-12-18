#include <stdint.h>
#include <stdio.h>

#include <bmp.h>

// Internal struct I only use as reference during dev
struct BmpMetadata {
  // HEADER
  uint16_t bftype; // SIGNATURE 2 bytes 
  uint32_t bfileSize; // FILESIZE
  uint32_t bfReserved; // unused
  uint32_t bOffbits; // offset from the beginning of file to the beginning of the bitmap data
  
  // INFO
  uint32_t biSize; // Size of InfoHeader =40 
  uint32_t biWidth; // Width and height for bitmap are given in pixels
  uint32_t biHeight;
  uint16_t biPlanes; // Numbe of planes
  uint16_t biBitCount; // Used to store pallete entry information
  uint32_t biCompression; // Type of compression, uncompressed = 0
  uint32_t biSizeImage; // Compressed size of Image
  uint32_t biXPelsPerMeter; // Horizontal resolution
  uint32_t biYPelsPerMeter; // Vertical resolution
  uint32_t biClrUsed; // Number of actually used colors for 24 bit images this will be 256
  uint32_t biClrImportant; // Number   of imporatnt colors
};



void print_pixels(struct BmpRelMetadata* hdr, FILE* file) {
  uint32_t offset = hdr->bOffbits + (168*200*3) + 70*3;

  // uint32_t pixel_data_rows = hdr->biHeight;

  // uint32_t cols = 3*hdr->biWidth;
  // uint32_t padded_cols = cols + (4 - (cols%4));
  
  // Each scan line is zero padded to the nearest 4-byte boundary. 
  // If the image has a width that is not divisible by four, say, 21 bytes, 
  // there would be 3 bytes of padding at the end of every scan line.
  // for (int i = 0; i < pixel_data_rows; i++) {
  //   const char[padded_cols];
  //   fseek(file, i*, SEEK_SET);
  // }

  // char row[padded_cols];
  unsigned char blue;
  fseek(file, offset+1, SEEK_SET);
  fread(&blue, 1, 4, file);
  //int blueval = int(blue);

  unsigned char green;
  fseek(file, offset+2, SEEK_SET);
  fread(&green, 1, 1, file);
  int greenval = (int) green;

  unsigned char red;
  fseek(file, offset+3, SEEK_SET);
  fread(&red, 1, 1, file);
  int redval = red - '0';

  printf("BLUE: %d, GREEN: %d, RED: %d\n", (int)blue, green, red);
};

// returns pixel_data array size if successful in loading else -1
uint32_t load_bmp(struct BmpRelMetadata* hdr, struct Pixel* pixel_data, FILE* file) {
  if (fgetc(file) != 'B' || fgetc(file) != 'M') {
    return -1;
  }

  if (fseek (file, 10, SEEK_SET)) {
    fprintf (stderr, "error: fseek SEEK_SET failed\n.");
    return 1;    
  }

  uint32_t dataoffset;
  fread(&dataoffset, sizeof(uint32_t), 1, file);
  printf("Data offset %d \n", dataoffset);
  hdr->bOffbits = dataoffset;

  if (fseek (file, 18, SEEK_SET)) {
    fprintf (stderr, "error: fseek SEEK_SET failed\n.");
    return 1;    
  }

  uint32_t width;
  fread(&width, sizeof(uint32_t), 1, file);
  printf("Width %d \n", width);
  hdr->biWidth = width;
  
  if (fseek (file, 22, SEEK_SET)) {
    fprintf (stderr, "error: fseek SEEK_SET failed\n.");
    return 1;    
  }

  uint32_t height;
  fread(&height, sizeof(uint32_t), 1, file);
  printf("Height %d \n", height);
  hdr->biHeight = height;

  print_pixels(hdr, file);

  return 0;
};


int rotate_pixel_data(int* pixel_data_width, int* pixel_data_height, unsigned char* old_bitmap_bits, unsigned char* new_bitmap_bits) {
  return 0;
};
