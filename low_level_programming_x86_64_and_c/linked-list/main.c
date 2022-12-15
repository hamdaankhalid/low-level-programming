#include <stdio.h>
#include <stdlib.h>

struct LinkedList
{
  int value;
  struct LinkedList* next;
  struct LinkedList* prev;
};


struct LinkedList* build_linked_list(size_t* out_len) {
  size_t len;
  scanf("%zu", &len);
  
  size_t linkedlistsize = sizeof(struct LinkedList);
  
  struct LinkedList* dummy = malloc(linkedlistsize);
  dummy->value = 0;
  dummy->next = NULL;
  dummy->prev = NULL;

  struct LinkedList* prev = dummy;

  for (size_t i  = 0 ; i < len; i++) {
    int val;
    scanf("%d", &val);
    
    struct LinkedList* node = malloc(linkedlistsize);
    node->value = val;
    node->prev = prev;
    
    prev->next = node;
    prev = node;
  }

  return dummy;
}

int main(void) {
  size_t len;
  struct LinkedList* head = build_linked_list(&len);

  struct LinkedList* curr = head;
  while (curr != NULL)
  {
    printf("%d ", curr->value);
    struct LinkedList* temp = curr->prev;
    curr = curr->next;
    
    free(temp);
  }
  puts("\n");
  
  free(curr);

  return 0;
}