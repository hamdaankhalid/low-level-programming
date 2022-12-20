#include <stdio.h>
#include <stdlib.h>

#include <linked_list.h>

static const size_t LINKED_LIST_SIZE = sizeof(struct LinkedList);

struct LinkedList* new_node(const int val) {
  struct LinkedList* node = malloc(LINKED_LIST_SIZE);
  node->value = val;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

void link_nodes(struct LinkedList* first, struct LinkedList* second) {
  first->next = second;
  second->prev = first;
};

struct LinkedList* build_linked_list_interactively(size_t* out_len) {
  size_t len;
  puts("Enter the length of your linkedlist: ");
  scanf("%zu", &len);

  // We build linked list from last to first
  struct LinkedList* after = NULL;
  for (size_t i  = 0 ; i < len; i++) {
    int val;
    printf("Enter value for node at index %zu: ", len-i-1);
    scanf("%d", &val);
    struct LinkedList* node = new_node(val);

    if (after == NULL) {
        after = node;
        continue;
    }
    link_nodes(node, after);
    after = node;
  }
  return after;
}


int summation(struct LinkedList* head) {
  int sum = 0;
  struct LinkedList* curr = head;
  while (curr != NULL)
  {
    sum += curr->value;
    curr = curr->next;
  }
  return sum;
}


int query(struct LinkedList* head, const size_t index) {
  struct LinkedList* curr = head;
  for (size_t i = 0; i <= index; i++) {
    if (curr->next == NULL) {
      return -1;
    }
    curr = curr->next;
  }
  return curr->value;
}


void print_linked_list(struct LinkedList* node) {
  struct LinkedList* curr = node;
  while (curr != NULL)
  {
    printf("%d ", curr->value);
    curr = curr->next;
  }
  puts("\n");
}


void destroy_linked_list(struct LinkedList* node) {
  struct LinkedList* curr = node;
  while (curr != NULL)
  {
    struct LinkedList* temp = curr;
    curr = curr->next;
    free(temp);
  }
}


// Higher Order Functions

/**
 * Higher order function that iterates over a linkedlist and applies a transform ptr function to each node
 * */
void foreach(struct LinkedList* node, void (*transorm) (int)) {
  struct LinkedList* curr = node;
  while (curr != NULL)
  {
    transorm(curr->value);
    curr = curr->next;
  }
}


/**
 * Higher order function that mutates the given linkedlist with the transform ptr funtion applied to each node
 * */
void map_mut(struct LinkedList* node, int (*transorm) (int)) {
  struct LinkedList* curr = node;
  while (curr != NULL)
  {
    curr->value = transorm(curr->value);
    curr = curr->next;
  }
}


/**
 * Higher order function that returns a new linkedlist with the transform ptr funtion applied to each node
 * */
struct LinkedList* map(struct LinkedList* node, int (*transform) (int)) {
  struct LinkedList* new_head = NULL;
  struct LinkedList* prev = NULL;

  struct LinkedList* curr = node;
  while (curr != NULL) {
    struct LinkedList* cp = new_node(curr->value);
    cp->value = transform(cp->value);
    if (new_head == NULL && prev == NULL) {
      new_head = cp;
    } else {
      link_nodes(prev, cp);
    }
    prev = cp;      
    curr = curr->next;
  }

  return new_head;
}


/**
 * Higher order function that iterates over linkedlist and keeps accumulating ontop of accumulator using the transform function and returns the accumulated value at the end.
 * */
int foldl(struct LinkedList* node, int accumulator, int (*transform) (int)) {
  struct LinkedList* curr = node;
  while (curr != NULL) {
    accumulator += transform(curr->value);
    curr = curr->next;
  }
  return accumulator;
}


/**
 * Iterate over list and make a function composition based on the transform function
 * */
struct LinkedList* iterate(int initial_val, int (*transform) (int), const size_t count) { 
  struct LinkedList* node = new_node(initial_val);

  struct LinkedList* prev = node;
  for (size_t i = 1; i < count; i++) {
    struct LinkedList* next = new_node(transform(prev->value));
    link_nodes(prev, next);
    prev = next;
  }

  return node;
}


/**
 * Save linked list to file
 * */
int save_linked_list(struct LinkedList* lst, const char* filename, int is_binary) {
  FILE* file = is_binary == 1 ? fopen(filename, "wb") : fopen(filename, "w");
  if (file == NULL) {
    return 0;
  }
  struct LinkedList* curr = lst;
  while (curr != NULL) {
    fprintf(file, "%d\n", curr->value);

    curr = curr->next;
  }

  fclose(file);
  return 1;
}

/**
 * read from a file and populate the passed list
 * */
int load_linked_list(struct LinkedList** lst, const char* filename, int is_binary) {
  FILE* file = is_binary == 1 ? fopen(filename, "rb") : fopen(filename, "r");
  if (file == NULL) {
    return 0;
  }
  
  char line[sizeof(int)];
  struct LinkedList* prev = NULL;
  while (fgets(line, sizeof(line), file)) {
    int value = atoi(line);
    struct LinkedList* curr = new_node(value);
    if (prev == NULL) {
      prev = curr;
    *lst = prev;
      continue;
    }
    link_nodes(prev, curr);
    prev = curr;
  }

  fclose(file);
  return 1;
}


/**
 * Save linked list to a BINARY file
 * */
int save_linked_list_binary(struct LinkedList** lst, const char* filename) {
  return 1;
}


/**
 * read from a BINARY file and populate the passed list
 * */
int load_binary(struct LinkedList** lst, const char* filename) {
  return 1;
}
