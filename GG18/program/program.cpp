#include <iostream>
#include <list>

#include "header.hpp"

using namespace std;

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    for (auto i = first; i; i = first)
    {
        first = first->next;
        delete i;
    }
}

template <typename T>
void SingleLinkedList<T>::push_back(T value)
{
    node *newNode = new node{value, nullptr};

    if (!first)
    {
        first = last = newNode;
    }
    else
    {
        last->next = newNode;
        last = last->next;
    }
}

void eraseIndex(std::list<int> &list)
{
    int pos = 1;
    for (auto i = list.begin(); i != list.end(); ++pos)
        if (*i == pos)
            i = list.erase(i);
        else
            ++i;
}

void eraseIndex(SingleLinkedList<int> &customList)
{
    if (!customList.first)
        throw std::runtime_error("List is empty");
    int pos = 1;
    while (customList.first && customList.first->value == pos)
    {
        auto *p = customList.first;
        customList.first = customList.first->next;
        delete p;

        if (!customList.first)
            customList.last = customList.first;

        ++pos;
    }
    ++pos;
    if (customList.first && customList.first->next)
    {
        for (auto *prev = customList.first, *i = prev->next; i; prev = i, i = i->next, ++pos)
        {
            while (i && i->value == pos)
            {
                prev->next = i->next;
                delete i;
                i = prev->next;

                ++pos;
            }

            if (!i)
            {
                customList.last = prev;
                break;
            }
        }
    }
}

void printList(list<int> &list)
{
    for (auto &i : list)
    {
        cout << i << " ";
    }
    cout << endl;
}

void printList(SingleLinkedList<int> &customList)
{
    for (auto &i = customList.first; i; i = i->next)
    {
        cout << i->value << " ";
    }
    cout << endl;
}