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


int rotate_pixel_data(struct BmpRelMetadata* hdr, FILE* file) {
  // using get pixel and set pixel as we iterate over the array we can manipulate the image as we want
  
  // E.g
  struct Pixel p;
  get_pixel(hdr, file, &p, 158, 36);
  printf("%d, %d, %d \n", p.r, p.g, p.b);

  return 0;
};
