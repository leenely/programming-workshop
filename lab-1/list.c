#include "list.h"
#include <assert.h>
#include <stdlib.h>

int init_single_list(single_list *list) {
  if (list == NULL)
    return -1;
  list->head = list->tail = NULL;
  return 0;
}

int add_to_beginning(single_list *list, int number) {
  if (list == NULL)
    return -1;

  node *new_node = (node *)malloc(sizeof(node));
  if (new_node == NULL)
    return -2;

  new_node->item = number;
  new_node->link = list->head;
  list->head = new_node;

  if (list->tail == NULL)
    list->tail = new_node;
  return 0;
}

int add_to_end(single_list *list, int number) {
  if (list == NULL)
    return -1;

  node *new_node = (node *)malloc(sizeof(node));
  if (new_node == NULL)
    return -2;

  new_node->item = number;
  new_node->link = NULL;
  if (list->tail == NULL) {
    list->head = new_node;
  } else {
    list->tail->link = new_node;
  }
  list->tail = new_node;
  return 0;
}

int add_to_middle(single_list *list, int position, int number) {
  if (list == NULL)
    return -1;

  node *new_node = (node *)malloc(sizeof(node));
  if (new_node == NULL)
    return -2;

  node *current = list->head;
  int count = 0;
  while (count < position - 1) {
    current = current->link;
    count++;
  }
  if (current == NULL)
    return -3;

  new_node->link = current->link;
  current->link = new_node;
  new_node->item = number;
  return 0;
}

int count_elements(single_list *list) {
  int count_elements = 0;
  node *current = list->head;
  while (current != NULL) {
    count_elements++;
    current = current->link;
  }
  return count_elements;
}

int delete_last(single_list *list) {
  if (list == NULL || list->head == NULL)
    return -1;

  if (list->head == list->tail) {
    free(list->head);
    list->head = list->tail = NULL;
    return 0;
  }

  node *current = list->head;
  while (current->link != list->tail) {
    current = current->link;
  }

  free(list->tail);
  list->tail = current;
  current->link = NULL;
  return 0;
}

int find_element(single_list *list, int position) {
  if (list == NULL || list->head == NULL)
    return -1;

  node *current = list->head;
  int count = 0;
  while (count < position) {
    current = current->link;
    count++;
  }
  if (current == NULL)
    return -1;
  return current->item;
}
