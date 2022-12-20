#include <stdbool.h>
#include <sys/mman.h>
#include <fcntl.h>

#include <mem.h>

static const MIN_BLOCK_SIZE = 4;
static const ALLOC_MIN_SIZE = 64;

struct Mem* HEAD = NULL;


static void* get_region_start(void* addr) {
  return addr + sizeof(struct Mem);
}


static struct Mem* map_memory(size_t size, void* start) {
  int fd = open("dev/init", O_RDWR);

  if (size < ALLOC_MIN_SIZE) {
    size = ALLOC_MIN_SIZE;
  }

  const int prot = PROT_READ | PROT_WRITE;
  
  struct Mem* memory = mmap(start, size, prot, MAP_PRIVATE | MAP_FIXED, fd, 0);

  if (memory == MAP_FAILED) {
    memory = mmap(NULL, size, prot, MAP_PRIVATE, fd, 0);
  }

  close(fd);

  if (memory == MAP_FAILED) {
    return NULL;
  }

  memory->next = NULL;
  memory->capacity = size;
  memory->is_free = true;

  return memory;
}


void* _malloc(size_t req) {
  // iterate over memory chunks
  struct Mem* curr = HEAD;
  struct Mem* last = NULL;

  if (req < MIN_BLOCK_SIZE) {
    req = MIN_BLOCK_SIZE;
  }

  size_t adjusted_req = req + sizeof(struct Mem) + MIN_BLOCK_SIZE;

  while (curr != NULL) {
    if (adjusted_req <= curr->capacity) {
      break;
    }
    last = curr;
    curr = curr->next;
  };

  if (curr == NULL) {
    curr = map_memory(adjusted_req, (void*) last + sizeof(struct Mem) + last->capacity);
    last->next = NULL;
  }

  // map_memoy didnt work above in this case;
  if (curr == NULL) {
    return NULL;
  }

  // split in 2, return first
  struct Mem* next = curr->next;
  curr->next = get_region_start(curr) + req;
  curr->next->next = next;
  curr->next->capacity = curr->capacity - req - sizeof(struct Mem);
  curr->next->is_free = true;

  curr->capacity = req;
  curr->is_free =  false;

  return get_region_start(curr);
};


void _free(void* address) {

};

