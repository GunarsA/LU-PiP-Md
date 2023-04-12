#ifndef HEADER
#define HEADER

#include <list>

template <typename T>
class SingleLinkedList
{
    struct node
    {
        T value;
        node *next;
    };

public:
    node *first = NULL;
    node *last = NULL;

    ~SingleLinkedList();

    void push_back(T value);
};

void eraseIndex(std::list<int> &list);

void eraseIndex(SingleLinkedList<int> &customList);

void printList(std::list<int> &list);

void printList(SingleLinkedList<int> &customList);

#endif