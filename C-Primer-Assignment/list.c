// list/list.c
// 
// Implementation for linked list.
//
// Prabin Sapkota (@02840859)

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

list_t *list_alloc() { 
	list_t *list_head = malloc(sizeof(list_t));
	return list_head;
}

void list_free(list_t *l) {
	if (!l) {
		return;
	}	
	node_t *current = l->head;
  node_t *next_node = NULL;
	while (current != NULL) { 
		next_node = current->next;
		free(current);
    current = next_node;
	}
}

void list_print(list_t *l) {
  node_t *current = l->head;
  while (current != NULL) {
    printf("%d ", current->value);
    current = current->next;
  }
  printf("\n");
}

int list_length(list_t *l) {
  node_t *current = l->head;
  int length = 0;
  while (current != NULL) {
    length++;
    current = current->next;
  }
  return length;
}

void list_add_to_back(list_t *l, elem value) {
  if (l->head == NULL) {
    node_t *node = malloc(sizeof(node_t));
    node->value = value;
    node->next = NULL;
    l->head = node;
  } else {
      node_t *current = l->head;
      node_t *previous = l->head;
  
  while (current != NULL) {
    previous = current;
    current = current->next;
  }
  node_t *node = malloc(sizeof(node_t));
  node->value = value;
  node->next = NULL;
  previous->next = node;
  }
}

void list_add_to_front(list_t *l, elem value) {
  node_t *node = malloc(sizeof(node_t));
  node->value = value;
  node_t *head = l->head;
  node->next = head;
  l->head = node;
}

void list_add_at_index(list_t *l, elem value, int index) {
  if (index == 0){
    list_add_to_front(l, value);
    return;
  }
  node_t *current = l->head;
  node_t *previous = l->head;
  int count = 0;
  while (current != NULL) {
    previous = current;
    current = current->next;
    count++;
    if (count == index) {
      break;
    }
  }
  node_t *node = malloc(sizeof(node_t));
  node->value = value;
  node->next = current;
  previous->next = node;
}

elem list_remove_from_back(list_t *l) { 
  node_t *current = l->head;
  node_t *previous = l->head;
  node_t *prev_of_prev;
  while (current != NULL) {
    prev_of_prev = previous;
    previous = current;
    current = current->next;
  }
  elem value = previous->value;
  prev_of_prev->next = NULL;
  free(previous);
  return value;
}

elem list_remove_from_front(list_t *l) {
  if (l) {
    elem value = l->head->value;
    node_t *prev_head = l->head;
    l->head = l->head->next;
    free(prev_head);
    return value;
  }
  return -1; 
}

elem list_remove_at_index(list_t *l, int index) { 
  if (index == 0){
    list_remove_from_front(l);
  }
  node_t *current = l->head;
  node_t *previous = l->head;
  int count = 0;
  elem value = -1;
  while (current != NULL) {
    previous = current;
    current = current->next;
    count++;
    if (count == index) {
      break;
    }
  }
  if (current) {
    value = current->value;
  previous->next = current->next;
  free(current);
  }
  return value; 
}

bool list_is_in(list_t *l, elem value) {
  node_t *current = l->head;
  while (current != NULL) {
    if (value == current->value) {
      return true;
    }
    current = current->next;
  }
  return false; 
}

elem list_get_elem_at(list_t *l, int index) { 
  if (index == 0){
    return l->head->value;
  }
  node_t *current = l->head;
  node_t *previous = l->head;
  int count = 0;
  elem value = -1;
  while (current != NULL) {
    previous = current;
    current = current->next;
    count++;
    if (count == index) {
      break;
    }
  }
  if (current) {
    value = current->value;
  }
  return value; 
}

int list_get_index_of(list_t *l, elem value) {
  int count = 0;
  node_t *current = l->head;
  while (current != NULL) {
    if (value == current->value) {
      break;
    }
    current = current->next;
    count++;
  }
  if (current) {
    return count;
  }
  return -1; 
}