# pragma once
#include <stdio.h>
#include <stdint.h>


struct BmpRelMetadata {
  uint32_t bOffbits; // offset from the beginning of file to the beginning of the bitmap data
  uint32_t biWidth; // Width and height for bitmap are given in pixels
  uint32_t biHeight;

  uint32_t data_size;
};


// Pixel Data is	a variable array of bytes that defines the bitmap bits. These are the actual image data, represented by consecutive rows, or "scan lines," of the bitmap. Each scan line consists of consecutive bytes representing the pixels in the scan line, in left-to-right order. The system maps pixels beginning with the bottom scan line of the rectangular region and ending with the top scan line.
struct Pixel {
  unsigned char b, g, r; // 
};


uint32_t load_bmp(struct BmpRelMetadata* hdr, FILE* file);
