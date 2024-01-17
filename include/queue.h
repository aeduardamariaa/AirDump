#ifndef QUEUE_H
#define QUEUE_H

    #include "linked_list.h"

    template <typename T>
    typedef struct
    {
        LinkedList<T>* list;
        unsigned size;
    } Queue;

    template <typename T>
    Queue<T>* createQueue();

    template <typename T>
    void addToQueue(Queue<T>* queue, T data);

    template <typename T>
    void popFromQueue(Queue<T>* queue);

    template <typename T>
    T getFromQueue(Queue<T>* queue);

    template <typename T>
    T getFromQueueByIndex(Queue<T>* queue, unsigned index);

#endif