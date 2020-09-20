//
// Created by icy on 2020/9/20.
//

#include "Queue.h"

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
