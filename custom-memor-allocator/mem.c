#include <stdbool.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <mem.h>
#include <unistd.h>


struct Mem* HEAD = NULL;

/*
 * Given a memory address, this method accounts for the initial metadata block and returns the non-metadata
 * containing part of the memory. This is the region that can be used to store the actual data.
 * */
static void* get_region_start(void* addr) {
  return addr + sizeof(struct Mem);
}

/* Given a size, and a suggested memory starting point it returns a memory pointer, the first few bytes of 
 * this pointer contain the metadata in the form of the struct Mem.
 * */
static struct Mem* map_memory(size_t size, void* start) {
  // int fd = open("./init", O_RDWR);

  if (size < ALLOC_MIN_SIZE) {
    size = ALLOC_MIN_SIZE;
  }

  const int prot = PROT_READ | PROT_WRITE;
  
  struct Mem* memory = mmap(start, size, prot, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if (memory == MAP_FAILED) {
    memory = mmap(NULL, size, prot, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  }

  // close(fd);

  if (memory == MAP_FAILED) {
    return NULL;
  }

  memory->next = NULL;
  memory->capacity = size;
  memory->is_free = true;

  return memory;
}

/*
 *  Given an initial size this method allocates memory and marks it as the memory head.
 *  After allocation it returns the writable address.
 * */
void* heap_init(size_t init_size, void* heap_start) {
  HEAD = map_memory(init_size, heap_start);

  if (HEAD == NULL) {
      return NULL;
  }

  return get_region_start(HEAD);
}

/*
 * Given a request for bytes. This method allocates the requested amount of bytes on memory/heap.
 * */
void* _malloc(size_t req) {
  
  struct Mem* curr = HEAD;
  struct Mem* last = NULL;

  if (req < MIN_BLOCK_SIZE) {
    req = MIN_BLOCK_SIZE;
  }

  // Adjusted request accounts for Mem metadata block, and MIN_BLOCK_SIZE
  size_t adjusted_req = req + sizeof(struct Mem) + MIN_BLOCK_SIZE; // TODO: WHY MIN_BLOCK_SIZE here!?

  // Iterate over memory chunks till we find a block with enough capacity
  while (curr != NULL) {
    if (adjusted_req <= curr->capacity) {
      break;
    }
    last = curr;
    curr = curr->next;
  };

  // If we made it all the way to the end and no mem blocks had enough capacity we create a new block at the end
  // at this point last contains the actual last block, we create a new block as curr and mark it as the next for
  // the official last block
  if (curr == NULL) {
    curr = map_memory(adjusted_req, (void*) last + sizeof(struct Mem) + last->capacity);
    last->next = curr;
  }

  // map_memoy didnt work above in this case, our poor malloc has FAILED
  if (curr == NULL) {
    return NULL;
  }

  // Split in two and return first
  struct Mem* next = curr->next; // next is null here?
  curr->next = get_region_start(curr) + req; 
  curr->next->next = next;
  curr->next->capacity = curr->capacity - req - sizeof(struct Mem);
  curr->next->is_free = true;

  curr->capacity = req;
  curr->is_free =  false;

  return get_region_start(curr);
};


void _free(void* address) {
  // get access to the memory metadata block
  struct Mem* memory = address - sizeof(struct Mem);
  // mark the metadata block as free
  memory->is_free = true;
  // Iterate over the blocks from here on and adjust the capacity of the blocks as you go
  if (memory->next != NULL && 
      memory->next->is_free && 
      memory->next == (void*)memory + sizeof(struct Mem) + memory->capacity) 
  {
      memory->capacity += sizeof(struct Mem) + memory->next->capacity;
      memory->next = memory->next->next;
  }
}

