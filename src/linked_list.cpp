#include <assert.h>
#include <stdlib.h>
#include "linked_list.h"

template <typename T>
struct Node<T>* createNode(T data)
{
  struct Node<T>* new_node = malloc(sizeof(struct Node<T>));
  new_node->data = &data;
  new_node->next = NULL;

  return new_node;
}

template <typename T>
LinkedList<T>* createList()
{
  LinkedList<T>* new_list = malloc(sizeof(struct Node<T>));
  new_list->head = NULL;
  new_list->tail = NULL;
  new_list->size = 0;

  return new_list;
}

template <typename T>
void insertAtBeginning(LinkedList<T>* list, T new_data)
{
  struct Node<T>* new_node = createNode(new_data);

  if (list->head != NULL)
    new_node->next = list->head;

  list->head = new_node;
  list->size++;
}

template <typename T>
void insertAtEnd(LinkedList<T>* list, T new_data)
{
  struct Node<T>* new_node = createNode(new_data);

  if (list->tail != NULL)
    list->tail->next = new_node;

  list->tail = new_node;
  list->size++;
}

template <typename T>
T getByIndex(LinkedList<T>* list, unsigned index)
{
  assert(index <= list->size);

  unsigned current_index = 0;
  struct Node<T>* current_node = list->head;

  while (current_index < index) current_node = current_node->next;

  return *(current_node->data);
}

template <typename T>
struct Node<T>* getNodeByIndex(LinkedList<T>* list, unsigned index)
{
  assert(index <= list->size);

  unsigned current_index = 0;
  struct Node<T>* current_node = list->head;

  while (current_index < index) current_node = current_node->next;

  return current_node->data;
}

template <typename T>
void deleteHead(LinkedList<T>* list)
{
  if (list->head == NULL)
    return;

  struct Node<T>* new_head_ref = list->head;
  list->head = new_head_ref->next;

  free(new_head_ref->data);
  free(new_head_ref);

  list->size--;
}

template <typename T>
void deleteTail(LinkedList<T>* list)
{
  if (list->tail == NULL)
    return;

  struct Node<T>* new_tail_ref = list->tail;
  list->tail = getNodeByIndex(list, list->size - 2);

  free(new_tail_ref->data);
  free(new_tail_ref);

  list->size--;
}