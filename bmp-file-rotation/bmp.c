#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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


void get_pixel(struct BmpRelMetadata* hdr, FILE* file, struct Pixel* px, int row, int col) {
  uint32_t init_offset = hdr->bOffbits;

  uint32_t padded_col = 3*hdr->biWidth + ((3*hdr->biWidth)%4);
  uint32_t target_offset = (row*padded_col) + (3*col);
  uint32_t target = init_offset + target_offset;

  fseek(file, target, SEEK_SET);
  fread(&px->b, 1, 1, file);

  fseek(file, target+1, SEEK_SET);
  fread(&px->g, 1, 1, file);

  fseek(file, target+2, SEEK_SET);
  fread(&px->r, 1, 1, file);
}


void set_pixel(struct BmpRelMetadata* hdr, FILE* file, struct Pixel* px, int row, int col) {
  uint32_t init_offset = hdr->bOffbits;

  uint32_t padded_col = 3*hdr->biWidth + ((3*hdr->biWidth)%4);
  uint32_t target = init_offset + row*padded_col + 3*col;

  fseek(file, target, SEEK_SET);
  fwrite(&px->b, 1, 1, file);

  fseek(file, target+1, SEEK_SET);
  fwrite(&px->g, 1, 1, file);

  fseek(file, target+2, SEEK_SET);
  fwrite(&px->r, 1, 1, file);
}


uint32_t load_bmp(struct BmpRelMetadata* hdr, FILE* file) {
  if (fgetc(file) != 'B' || fgetc(file) != 'M') {
    return -1;
  }

  if (fseek (file, 10, SEEK_SET)) {
    return -1;    
  }

  uint32_t dataoffset;
  fread(&dataoffset, sizeof(uint32_t), 1, file);
  printf("Data offset %d \n", dataoffset);
  hdr->bOffbits = dataoffset;

  if (fseek (file, 18, SEEK_SET)) {
    return -1;    
  }

  uint32_t width;
  fread(&width, sizeof(uint32_t), 1, file);
  printf("Width %d \n", width);
  hdr->biWidth = width;
  
  if (fseek (file, 22, SEEK_SET)) {
    return -1;    
  }

  uint32_t height;
  fread(&height, sizeof(uint32_t), 1, file);
  printf("Height %d \n", height);
  hdr->biHeight = height;

  uint32_t padded_cols = 3*width + ((3*width)%4);
  uint32_t data_size = padded_cols * height;
  hdr->data_size = data_size;
  printf("Image Size %d \n", data_size);

  return 0;
};


void swap(struct BmpRelMetadata* hdr, FILE* file, int row1, int col1, int row2, int col2) {
  struct Pixel currpx;
  get_pixel(hdr, file, &currpx, row1, col1);

  struct Pixel swappx;
  get_pixel(hdr, file, &swappx, row2, col2);
  
  set_pixel(hdr, file, &currpx, row2, col2);
  set_pixel(hdr, file, &swappx, row1, col1);
}

/**
 * NOTE: Transpose only works for square images
 * */
void transpose_bmp(struct BmpRelMetadata* hdr, FILE* file) {
  uint32_t offset = 0;
  for (uint32_t row = 0; row < hdr->biHeight; row++) {
    for (uint32_t col = 0; col < offset; col++) {
      int swap_with_col = (hdr->biWidth-1) - col;
      int swap_with_row = (hdr->biHeight-1) - row;
      swap(hdr, file, row, col, swap_with_row, swap_with_col);
    }
    offset++;
  }
};


//      5 4 3 6 -> 6 3 4 5
// idx  0 1 2 3
//
//      3 4 5 6 7
// idx  0 1 2 3 4
//      7 6 5 4 3
void rev_rows_bmp(struct BmpRelMetadata* hdr, FILE* file) {
  for (uint32_t row = 0; row < hdr->biHeight; row++) {
    for (uint32_t col = 0; col < (hdr->biWidth/2); col++) {
      uint32_t swap_with_col = (hdr->biWidth-1) - col;
      swap(hdr, file, row, col, row, swap_with_col);
    }
  }
};


/**
 *                A            B
 *              4 3 5        1 5 4
 *              5 4 2   ->   5 4 3
 *              1 5 9        9 2 5
 * 
 *                A            B'         B
 *              4 3 5        4 5 1      1 5 4
 *              5 4 2   ->   3 4 5  ->  5 4 3
 *              1 5 9        5 2 9      9 2 5
 *              
 *    B = AT -> RevCols in A
 * */

uint32_t rotate_bmp(struct BmpRelMetadata* hdr, FILE* file) {  
  // using get pixel and set pixel as we iterate over the array we can manipulate the image as we want
  transpose_bmp(hdr, file);
  rev_rows_bmp(hdr, file);

  return 0;
};
