# pragma once

#include <stdio.h>

# pragma pack(push, 1)
struct Mem {
  int capacity;
  bool is_free;
  struct Mem* next;
};
# pragma pack(pop)

void* _malloc(size_t bytes);
void _free(void* address);
