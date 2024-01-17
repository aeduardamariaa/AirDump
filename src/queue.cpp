#include "queue.h"
#include "linked_list.h"

template <typename T>
Queue<T>* createQueue()
{
  Queue<T>* new_queue = malloc(sizeof(Queue<T>));
  new_queue->list = createList();
  new_queue->size = 0;

  return new_queue;
}

template <typename T>
void addToQueue(Queue<T>* queue, T data)
{
  insertAtEnd(queue->list, data);
  queue->size++;
}

template <typename T>
void popFromQueue(Queue<T>* queue)
{
  deleteHead(queue->list);
  queue->size--;
}

template <typename T>
T getFromQueue(Queue<T>* queue)
{
  return getByIndex(queue->list, 0);
}

template <typename T>
T getFromQueueByIndex(Queue<T>* queue, unsigned index)
{
  return getByIndex(queue->list, index);
}