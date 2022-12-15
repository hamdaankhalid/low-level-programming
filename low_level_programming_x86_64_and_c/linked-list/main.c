#include <stdio.h>
#include <stdlib.h>

struct LinkedList
{
  int value;
  struct LinkedList* next;
  struct LinkedList* prev;
};

void link_nodes(struct LinkedList* first, struct LinkedList* second) {
  first->next = second;
  second->prev = first;
};


struct LinkedList* build_linked_list(size_t* out_len) {
  size_t len;
  puts("Enter the length of your linkedlist: ");
  scanf("%zu", &len);
  size_t linkedlistsize = sizeof(struct LinkedList);

  // We build linked list from last to first
  struct LinkedList* after = NULL;
  for (size_t i  = 0 ; i < len; i++) {
    int val;
    printf("Enter value for node at index %d: ", len-i-1);
    scanf("%d", &val);

    struct LinkedList* node = malloc(linkedlistsize);
    node->value = val;

    if (after == NULL) {
        after = node;
        continue;
    }
    link_nodes(node, after);
    after = node;
  }

  return after;
}

const int summation(struct LinkedList* head) {
  int sum = 0;
  struct LinkedList* curr = head;
  while (curr != NULL)
  {
    sum += curr->value;
    curr = curr->next;
  }
  return sum;
}

const void query(struct LinkedList* head, int index) {
  int idx = 0;
  struct LinkedList* curr = head;
  while (curr != NULL)
  {
    if (idx == index) {
      printf("Index %d has value: %d\n", index, curr->value);
      return;
    }
    curr = curr->next;
    idx++;
  }
  printf("Index %d is out of range.\n", index);
}

int main(void) {
  size_t len;
  struct LinkedList* head = build_linked_list(&len);
  
  puts("\n");
  
  printf("Sum of linked list: %d \n", summation(head));

  query(head, 0);
  query(head, 3);
  query(head, 2);

  puts("\n");
  puts("Destroying....\n");
  struct LinkedList* curr = head;
  while (curr != NULL)
  {
    printf("%d ", curr->value);
    struct LinkedList* temp = curr;
    curr = curr->next;
  
    free(temp);
  }
  puts("\n");

  puts("Completed :)");

  return 0;
}
