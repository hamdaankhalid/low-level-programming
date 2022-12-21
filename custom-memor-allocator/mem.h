# pragma once

#include <stdio.h>
#include <stdbool.h>

#define MIN_BLOCK_SIZE 4
#define ALLOC_MIN_SIZE 64

#pragma pack(push, 1)
struct Mem {
  int capacity;
  bool is_free;
  struct Mem* next;
};
#pragma pack(pop)

void* heap_init(size_t init_size, void* heap_start);
void* _malloc(size_t req);
void _free(void* address);
