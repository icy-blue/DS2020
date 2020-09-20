//
// Created by icy on 2020/9/20.
//

#ifndef DS2020_QUEUE_H
#define DS2020_QUEUE_H

#include "LinkedList.h"

template<typename T>
class Queue {
    LinkedList<T> list;
    int _length;
public:
    int length();

    T front();

    void pop();

    void push(T element);

    bool isEmpty();
};


#endif //DS2020_QUEUE_H
