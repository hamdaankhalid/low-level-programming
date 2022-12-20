# pragma once

#include <stdio.h>

# pragma pack(push, 1)
struct Mem {
  int capacity;
  bool is_free;
  struct Mem* next;
};
# pragma pack(pop)

void* heap_init(size_t init_size);
void* _malloc(size_t req);
void _free(void* address);
