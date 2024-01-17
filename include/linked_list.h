#ifndef LINKED_LIST_H
#define LINKED_LIST_H

    template <typename T>
    struct Node
    {
        T* data;
        struct Node<T>* next;
    };

    template <typename T>
    typedef struct
    {
        struct Node<T>* head;
        struct Node<T>* tail;
        unsigned size;
    } LinkedList;

    template <typename T>
    struct Node<T>* createNode(T data);

    template <typename T>
    LinkedList<T>* createList();

    template <typename T>
    void insertAtBeginning(LinkedList<T>* list, T new_data);

    template <typename T>
    void insertAtEnd(LinkedList<T>* list, T new_data);

    template <typename T>
    T getByIndex(LinkedList<T>* list, unsigned index);

    template <typename T>
    struct Node<T>* getNodeByIndex(LinkedList<T>* list, unsigned index);

    template <typename T>
    void deleteHead(LinkedList<T>* list);

    template <typename T>
    void deleteTail(LinkedList<T>* list);

#endif