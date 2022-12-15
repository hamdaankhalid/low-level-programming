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
  struct LinkedList* dummy_head = malloc(linkedlistsize);
  dummy_head->value = 0;
  dummy_head->next = NULL;
  dummy_head->prev = NULL;
  struct LinkedList* prev = NULL;
  for (size_t i  = 0 ; i < len; i++) {
    int val;
    scanf("%d", &val);
    struct LinkedList* node = malloc(linkedlistsize);
    node->value = val;
    if (prev != NULL) {
      node->next = prev;
    } else {
        prev = malloc(linkedlistsize);
        prev->value = val;
        prev->next = NULL;
    }
    prev->prev = node;
    prev = node;
  }
  dummy_head->next = prev;
  prev->prev = dummy_head;
  struct LinkedList* curr = dummy_head->next;
  curr->prev = NULL;
  free(dummy_head);
  return curr;
}


int main(void) {
  size_t len;
  struct LinkedList* head = build_linked_list(&len);
  
  struct LinkedList* curr = head;
  while (curr != NULL)
  {
    printf("%d ", curr->value);
    struct LinkedList* temp = curr;
    curr = curr->next;
  
    free(temp);
  }

  puts("\n");
  

  return 0;
}