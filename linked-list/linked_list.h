# pragma once

#include <stdio.h>

struct LinkedList
{
  int value;
  struct LinkedList* next;
  struct LinkedList* prev;
};

struct LinkedList* new_node(const int val);

void link_nodes(struct LinkedList* first, struct LinkedList* second);

struct LinkedList* build_linked_list_interactively(size_t* out_len);

int summation(struct LinkedList* head);

int query(struct LinkedList* head, const size_t index);

void print_linked_list(struct LinkedList* node);

void destroy_linked_list(struct LinkedList* node);

// Higher Order Functional Utilities

void foreach(struct LinkedList* node, void (*transorm) (int));

void map_mut(struct LinkedList* node, int (*transorm) (int));

struct LinkedList* map(struct LinkedList* node, int (*transform) (int));

int foldl(struct LinkedList* node, int accumulator, int (*transform) (int));

struct LinkedList* iterate(int initial_val, int (*transform) (int), const size_t count);

// Ser-Der Utilities

/**
 * Save linked list to a text file
 * */
int save_linked_list(struct LinkedList* lst, const char* filename, int is_binary);

/**
 * read from a text file and populate the passed list
 * */
int load_linked_list(struct LinkedList** lst, const char* filename, int is_binary);
