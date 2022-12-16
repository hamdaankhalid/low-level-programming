#include <stdio.h>
#include <linked_list.h>

// The functions below are used by the higher order functions
int squarer(int x) {
  return x*x;
}


int increment(int x) {
 return x + 1;
}


void sideffect(int x) {
  printf("a biatch %d \n", x);
}


int main(void) {
  size_t len;
  struct LinkedList* head = build_linked_list_interactively(&len);
  
  printf("Sum of linked list: %d \n", summation(head));
  
  printf("Test query %d at idx 3 \n", query(head, 3));
  
  puts("Functional Foreach being applied....");
  foreach(head, &sideffect);

  puts("Functional Map Mutable being applied....");
  map_mut(head, &squarer);
  
  puts("Functional Map being applied....");
  struct LinkedList* new = map(head, &increment);
  
  puts("Functional Iterate Being applied");
  struct LinkedList* iter_made = iterate(9, &increment, 5);

  printf("Functional Foldl on Iterate returned array %d \n", foldl(iter_made, 9, &increment));

  puts("Functional Map Mutable Array....");
  print_linked_list(head);
  
  puts("Functional Map Array....");
  print_linked_list(new);

  puts("Functional Iterate Array....");
  print_linked_list(iter_made);

  puts("Destroying All LinkedLists....");
  destroy_linked_list(head);
  destroy_linked_list(iter_made);
  destroy_linked_list(new);
  return 0;
}
