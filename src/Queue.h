/**
 * Created by Clion.
 * User: icy
 * Date: 2020/9/21
 * i@icys.top
 */

#ifndef DS2020_QUEUE_H
#define DS2020_QUEUE_H

#include "DoubleLinkedList.h"

template<typename T>
class Queue {
    DoubleLinkedList<T> list;
    int _length;
public:
    int length();

    T front();

    void pop();

    void push(T element);

    bool isEmpty();
};


template<typename T>
int Queue<T>::length() {
    return _length;
}

template<typename T>
T Queue<T>::front() {
    return list.get(0);
}

template<typename T>
void Queue<T>::pop() {
    list.popFront();
}

template<typename T>
void Queue<T>::push(T element) {
    list.pushBack(element);
}

template<typename T>
bool Queue<T>::isEmpty() {
    return _length != 0;
}

#endif //DS2020_QUEUE_H
