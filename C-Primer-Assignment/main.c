#include <stdio.h>

#include "list.h"

int main() {
  printf("Tests for linked list implementation\n");
  
  // Create the head of the list
  list_t *list = list_alloc();
  
  // Add value 1
  list_add_to_back(list, 1);
  list_print(list);
  
  // Add value 5
  list_add_to_back(list, 5);
  list_print(list);
  
  // Add value 8
  list_add_to_back(list, 8);
  list_print(list);
  
  // Add value 10
  list_add_to_back(list, 10);
  list_print(list);
  
  // Add value 0
  list_add_to_back(list, 0);
  list_print(list);
  
  // Add value 5
  list_add_to_back(list, 5);
  list_print(list);

  // Print list length
  printf("%d", list_length(list));
  printf("\n");

  // Add value 70 in the front
  list_add_to_front(list, 70);
  list_print(list);

  // Print list length
  printf("%d", list_length(list));
  printf("\n");

  // Add 2 at index 5
  list_add_at_index(list, 2, 5);
  list_print(list);

  // Remove last element in the list
  elem value = list_remove_from_back(list);
  printf("%d", value);
  printf("\n");

  // Remove first element in the list
  value = list_remove_from_front(list);
  printf("%d", value);
  printf("\n");

  // Remove element at index 3
  value = list_remove_at_index(list, 2);
  printf("%d", value);
  printf("\n");

  // Check if 5 is in the list
  bool elem_in_list = list_is_in(list, 5);
  printf("%s\n", elem_in_list?"true":"false");

  // Print list
  list_print(list);

  // Get item at index 2
  printf("%d\n", list_get_elem_at(list, 2));

  // Get index of elem 2 in the list
  printf("%d\n", list_get_index_of(list, 2));
  
  return 0;
}