#include "list.h"
#include <assert.h>
#include <stdlib.h>

int init_single_list(single_list *list) {
  if (list == NULL)
    return NULLPOINTEREXCEPTION_ERRCODE;
  list->head = NULL;
  return SUCCESS_CODE;
}

int add_to_beginning(single_list *list, int number) {
  if (list == NULL)
    return NULLPOINTEREXCEPTION_ERRCODE;

  node *new_node = (node *)malloc(sizeof(node));
  if (new_node == NULL)
    return MEMORYALLOCATIONEXCEPTION_ERRCODE;

  new_node->item = number;
  new_node->link = list->head;
  list->head = new_node;
  return SUCCESS_CODE;
}

int add_to_end(single_list *list, int number) {
  if (list == NULL)
    return NULLPOINTEREXCEPTION_ERRCODE;

  node *new_node = (node *)malloc(sizeof(node));
  if (new_node == NULL)
    return MEMORYALLOCATIONEXCEPTION_ERRCODE;

  new_node->item = number;
  new_node->link = NULL;

  if (list->head == NULL) {
    list->head = new_node;
  } else {
    node *current = list->head;
    while (current->link != NULL) {
      current = current->link;
    }
    current->link = new_node;
  }
  return SUCCESS_CODE;
}

int add_to_middle(single_list *list, int position, int number) {
  if (list == NULL)
    return NULLPOINTEREXCEPTION_ERRCODE;

  node *new_node = (node *)malloc(sizeof(node));
  if (new_node == NULL)
    return MEMORYALLOCATIONEXCEPTION_ERRCODE;

  if (position == 0) {
    new_node->link = list->head;
    list->head = new_node;
    new_node->item = number;
    return SUCCESS_CODE;
  }

  node *current = list->head;
  int count = 0;
  while (current != NULL && count < position - 1) {
    current = current->link;
    count++;
  }
  if (current == NULL) {
    free(new_node);
    return EMPTYLISTEXCEPTION_ERRCODE;
  }

  new_node->link = current->link;
  current->link = new_node;
  new_node->item = number;
  return SUCCESS_CODE;
}

int count_elements(single_list *list) {
  if (list == NULL)
    return NULLPOINTEREXCEPTION_ERRCODE;

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
    return NULLPOINTEREXCEPTION_ERRCODE;

  if (list->head->link == NULL) {
    free(list->head);
    list->head = NULL;
    return SUCCESS_CODE;
  }

  node *prev = NULL;
  node *current = list->head;
  while (current->link != NULL) {
    prev = current;
    current = current->link;
  }

  free(current);
  prev->link = NULL;
  return SUCCESS_CODE;
}

int find_element(single_list *list, int position) {
  if (list == NULL || list->head == NULL)
    return NULLPOINTEREXCEPTION_ERRCODE;

  node *current = list->head;
  int count = 0;
  while (current != NULL && count < position) {
    current = current->link;
    count++;
  }
  if (current == NULL)
    return EMPTYLISTEXCEPTION_ERRCODE;
  return current->item;
}
